// LED matrix driver for max7219

// NTP shamelessly ripped from https://tttapa.github.io/ESP8266/Chap15%20-%20NTP.html
#include "LEDPanel.h"
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiUdp.h>
#include <Ticker.h>
Ticker renderTicker;



// clk  D5
// CS   D3
// MOSI D7


LEDPanel panel = LEDPanel(11, 13, 0, 4);
int renderCount = 0;
void renderPanel()
{
  if(renderCount == 0)
  {
    panel.scrollRender(0);
  }
  else if(renderCount > 15)
  {
    panel.scrollRender(-1);
  }
  if((++renderCount)>= panel.getScrollWindowSize())
  {
    renderCount = 0;
  }
}



ESP8266WiFiMulti wifiMulti;      // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'
WiFiUDP UDP;                     // Create an instance of the WiFiUDP class to send and receive
IPAddress timeServerIP;          // time.nist.gov NTP server address
const char* NTPServerName = "time.nist.gov";
const int NTP_PACKET_SIZE = 48;  // NTP time stamp is in the first 48 bytes of the message
byte NTPBuffer[NTP_PACKET_SIZE]; // buffer to hold incoming and outgoing packets
int rejectCount = 0;

void setup()
{
  panel.disable();
  panel.setLEDIntensity(0);
  Serial.begin(115200);
  panel.enable();
  panel.writeString("ABC",true);
  renderTicker.attach(0.1, renderPanel);
  Serial.println("Connecting...");
  wifiMulti.addAP("ASK4 Wireless", "");   // add Wi-Fi networks
  Serial.println("Connected!");
  while (wifiMulti.run() != WL_CONNECTED) {  // Wait for the Wi-Fi to connect
    delay(250);
    Serial.print('.');
  }
  Serial.println("\r\n");
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());             // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.print(WiFi.localIP());            // Send the IP address of the ESP8266 to the computer
  Serial.println("Starting UDP");
  UDP.begin(123);                          // Start listening for UDP messages on port 123
  Serial.print("Local port:\t");
  Serial.println(UDP.localPort());
  if(!WiFi.hostByName(NTPServerName, timeServerIP)) { // Get the IP address of the NTP server
    Serial.println("DNS lookup failed. Rebooting.");
    Serial.flush();
    ESP.reset();
  }
  Serial.print("Time server IP:\t");
  Serial.println(timeServerIP);
  
  Serial.println("\r\nSending NTP request ...");
  sendNTPpacket(timeServerIP);  
}

void loop() 
{
  uint32_t unixTime = getTime();
  if( unixTime != 0)
  {
    Serial.println("Got response!");
    rejectCount=0;
//    int seconds = getSeconds(unixTime);
    char tempBuffer[2];
    sprintf(tempBuffer, %02d,getMinutes(unixTime));
    String minutes = String(tempBuffer);
    String hours = String(getHours(unixTime));
    String output = "";
    output.concat(hours);
    output.concat(":");
    output.concat(minutes);
    panel.writeString(output,true);
    delay(1000*30); // delay 30 seconds
    sendNTPpacket(timeServerIP);  
  }
  else
  {
    Serial.println("Got nothing");
    rejectCount++;
    if(rejectCount > 60) // if cannot talk to server for 1 min, esp reboots
    {
      ESP.reset();
    }
    // send another request after 1 second
    sendNTPpacket(timeServerIP);  
    delay(1000);
  }
}


uint32_t getTime() {
  if (UDP.parsePacket() == 0) { // If there's no response (yet)
    return 0;
  }
  UDP.read(NTPBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
  // Combine the 4 timestamp bytes into one 32-bit number
  uint32_t NTPTime = (NTPBuffer[40] << 24) | (NTPBuffer[41] << 16) | (NTPBuffer[42] << 8) | NTPBuffer[43];
  // Convert NTP time to a UNIX timestamp:
  // Unix time starts on Jan 1 1970. That's 2208988800 seconds in NTP time:
  const uint32_t seventyYears = 2208988800UL;
  // subtract seventy years:
  uint32_t UNIXTime = NTPTime - seventyYears;
  return UNIXTime;
}

void sendNTPpacket(IPAddress& address) {
  memset(NTPBuffer, 0, NTP_PACKET_SIZE);  // set all bytes in the buffer to 0
  // Initialize values needed to form NTP request
  NTPBuffer[0] = 0b11100011;   // LI, Version, Mode
  // send a packet requesting a timestamp:
  UDP.beginPacket(address, 123); // NTP requests are to port 123
  UDP.write(NTPBuffer, NTP_PACKET_SIZE);
  UDP.endPacket();
}

inline int getSeconds(uint32_t UNIXTime) {
  return UNIXTime % 60;
}

inline int getMinutes(uint32_t UNIXTime) {
  return UNIXTime / 60 % 60;
}

inline int getHours(uint32_t UNIXTime) {
  return UNIXTime / 3600 % 24;
}
