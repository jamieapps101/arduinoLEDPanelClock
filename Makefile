PORT = "/dev/ttyUSB0"
VERBOSE=true

# to list all below:
# $ ./arduino-cli board listall

# BOARD_FQBN="esp8266:esp8266:gen4iod"          #- 4D Systems gen4 IoD Range       
BOARD_FQBN="esp8266:esp8266:huzzah"           #- Adafruit Feather HUZZAH ESP8266 
# BOARD_FQBN="esp8266:esp8266:wifi_slot"        #- Amperka WiFi Slot               
# BOARD_FQBN="esp8266:esp8266:arduino"-esp8266  #- Arduino                         
# BOARD_FQBN="esp8266:esp8266:espmxdevkit"      #- DOIT ESP-Mx DevKit (ESP8285)    
# BOARD_FQBN="esp8266:esp8266:oak"              #- Digistump Oak                   
# BOARD_FQBN="esp8266:esp8266:espduino"         #- ESPDuino (ESP-13 Module)        
# BOARD_FQBN="esp8266:esp8266:espectro"         #- ESPectro Core                   
# BOARD_FQBN="esp8266:esp8266:espino"           #- ESPino (ESP-12 Module)          
# BOARD_FQBN="esp8266:esp8266:espresso_lite_v1" #- ESPresso Lite 1.0               
# BOARD_FQBN="esp8266:esp8266:espresso_lite_v2" #- ESPresso Lite 2.0               
# BOARD_FQBN="esp8266:esp8266:generic"          #- Generic ESP8266 Module          
# BOARD_FQBN="esp8266:esp8266:esp8285"          #- Generic ESP8285 Module          
# BOARD_FQBN="esp8266:esp8266:sonoff"           #- ITEAD Sonoff                    
# BOARD_FQBN="esp8266:esp8266:inventone"        #- Invent One                      
# BOARD_FQBN="esp8266:esp8266:d1_mini"          #- LOLIN(WEMOS) D1 R2 & mini       
# BOARD_FQBN="esp8266:esp8266:d1_mini_lite"     #- LOLIN(WEMOS) D1 mini Lite       
# BOARD_FQBN="esp8266:esp8266:d1_mini_pro"      #- LOLIN(WEMOS) D1 mini Pro        
# BOARD_FQBN="esp8266:esp8266:nodemcu"          #- NodeMCU 0.9 (ESP-12 Module)     
# BOARD_FQBN="esp8266:esp8266:nodemcuv2"        #- NodeMCU 1.0 (ESP-12E Module)    
# BOARD_FQBN="esp8266:esp8266:modwifi"          #- Olimex MOD-WIFI-ESP8266(-DEV)   
# BOARD_FQBN="esp8266:esp8266:phoenix_v1"       #- Phoenix 1.0                     
# BOARD_FQBN="esp8266:esp8266:phoenix_v2"       #- Phoenix 2.0                     
# BOARD_FQBN="esp8266:esp8266:eduinowifi"       #- Schirmilabs Eduino WiFi         
# BOARD_FQBN="esp8266:esp8266:wiolink"          #- Seeed Wio Link                  
# BOARD_FQBN="esp8266:esp8266:blynk"            #- SparkFun Blynk Board            
# BOARD_FQBN="esp8266:esp8266:thing"            #- SparkFun ESP8266 Thing          
# BOARD_FQBN="esp8266:esp8266:thingdev"         #- SparkFun ESP8266 Thing Dev      
# BOARD_FQBN="esp8266:esp8266:esp210"           #- SweetPea ESP-210                
# BOARD_FQBN="esp8266:esp8266:espinotee"        #- ThaiEasyElec's ESPino           
# BOARD_FQBN="esp8266:esp8266:d1"               #- WeMos D1 R1                     
# BOARD_FQBN="esp8266:esp8266:wifiduino"        #- WiFiduino                       
# BOARD_FQBN="esp8266:esp8266:wifinfo"          #- WifInfo                         
# BOARD_FQBN="esp8266:esp8266:cw01"             #- XinaBox CW01                    



.PHONY: all compile verify setup

default:
	@echo "Options are:"
	@echo "-  verify"
	@echo "-  compile"



arduino-cli:
	wget https://downloads.arduino.cc/arduino-cli/arduino-cli_latest_Linux_64bit.tar.gz
	tar -xf arduino-cli_latest_Linux_64bit.tar.gz
	rm -rf arduino-cli_latest_Linux_64bit.tar.gz

arduino-cli.yaml: arduino-cli
	./arduino-cli config init \
		--additional-urls \
			https://dl.espressif.com/dl/package_esp32_index.json \
		--additional-urls \
			http://arduino.esp8266.com/stable/package_esp8266com_index.json \
		--dest-dir .
	./arduino-cli core update-index
	./arduino-cli core install esp8266:esp8266
	./arduino-cli board listall

setup: arduino-cli.yaml

clean:
	-rm -rf clock/build

compile: setup clean
	./arduino-cli compile --fqbn $(BOARD_FQBN) clock

upload: compile
	./arduino-cli upload \
		-p $(PORT) \
		--fqbn $(BOARD_FQBN) \
		clock

serial:
	minicom -b 115200 -D /dev/ttyUSB0