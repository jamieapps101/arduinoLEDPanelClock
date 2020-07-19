// LED matrix driver for max7219
// Jamie apps
// NTP shamelessly ripped from https://tttapa.github.io/ESP8266/Chap15%20-%20NTP.html
#include <SPI.h>
#include "LEDPanel.h"
#include "wifi_info.h"
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiUdp.h>
#include "time_util.h"
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
//   wifiMulti.addAP("ASK4 Wireless", "");   // add Wi-Fi networks
  wifiMulti.addAP(SSID_DEF, PASSWORD_DEF);   // add Wi-Fi networks
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

//   uint32_t unixTime = getTime();
//   if( unixTime != 0)
//   {
//     Serial.println("Got response!");
//     rejectCount=0;
// //    int seconds = getSeconds(unixTime);
//     char tempBuffer[2];
//     sprintf(tempBuffer, "%02d",getMinutes(unixTime));
//     String minutes = String(tempBuffer);
//     String hours = String(getHours(unixTime));
//     String output = "";
//     output.concat(hours);
//     output.concat(":");
//     output.concat(minutes);
//     panel.writeString(output,true);
//     delay(1000*30); // delay 30 seconds
//     sendNTPpacket(timeServerIP);  
//   }
//   else
//   {
//     Serial.println("Got nothing");
//     rejectCount++;
//     if(rejectCount > 3600) // if cannot talk to server for 1 hour, esp reboots
//     {
//       ESP.reset();
//     }
//     // send another request after 1 second
//     sendNTPpacket(timeServerIP);  
//     delay(1000);
//   }

    uint32_t unixTime = getTime();
    while (unixTime == 0) {
        delay(1000*10);
        unixTime = getTime();
    }
    // utin32_t seconds = getSeconds(unixTime);
    // utin32_t mins    = getMinutes(unixTime);
    // utin32_t hours   = getHours(unixTime);
    struct time Time = get_time_struct(unixTime);
    uint32_t increment = 0;
    int inc_hours   = Time.hours;
    if (Time.daylight_saving) {
        inc_hours++;
    }
    int inc_mins    = Time.minutes;
    int inc_seconds = Time.seconds;
    while(true) {
        inc_seconds++;
        if (inc_seconds == 60) {
            inc_mins++;
            inc_seconds-=60;
        }
        if (inc_mins == 60) {
            inc_hours++;
            inc_mins-=60;
        }
        // inc_seconds = increment % (60);
        // update display
        char min_tempBuffer[2];
        char hour_tempBuffer[2];
        sprintf(min_tempBuffer, "%02d",inc_mins);
        sprintf(hour_tempBuffer, "%02d",inc_hours);
        String minutes = String(min_tempBuffer);
        String hours = String(hour_tempBuffer);
        String output = "";
        output.concat(hours);
        if ((inc_seconds % 2) == 0) {
            output.concat(":");
        } else {
            output.concat(" ");
        }
        output.concat(minutes);
        panel.writeString(output,true);
        // wait a min
        delay(1000);
        // if its been longer than an hour since last check
        if (increment > 3600) {
            // attempt to read
            uint32_t temp = getTime();
            // ie the time has been aquired and its updated!
            if (temp != 0 && temp != unixTime) {
                Serial.println("Time Update Received");
                unixTime = temp;
                Time = get_time_struct(unixTime);
                uint32_t increment = 0;
                int inc_hours   = Time.hours;
                if (Time.daylight_saving) {
                    inc_hours++;
                }
                int inc_mins    = Time.minutes;
                int inc_seconds = Time.seconds;
                increment = 0;
            } else {
                // else try again to get the time
                Serial.println("Requesting Time Update");
                sendNTPpacket(timeServerIP);  
            }
        }

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


inline int getDays(uint32_t UNIXTime) {
  return (UNIXTime / (3600*24))%356;
}

inline int getMonth(int days) {

}






