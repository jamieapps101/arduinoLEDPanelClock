.PHONY: all compile verify

default:
	@echo "Options are:"
	@echo "-  verify"
	@echo "-  compile"


# ARDUINO_BOARD ?= arduino:avr:uno
ARDUINO_BOARD ?= esp8266:esp8266:nodemcu
FILE ?= clock/clock.ino
PREFERENCES ?= preferences.txt
EXTRA ?= 

compile: 

verify:
	#-mv \
	#~/containedPrograms/arduino-1.8.10/hardware/arduino/avr/libraries/SPI/src/SPI.h \
	#~/containedPrograms/arduino-1.8.10/hardware/arduino/avr/libraries/SPI/src/inactive_SPI.h

	arduino                  \
	--verify                 \
	--board ${ARDUINO_BOARD} \
	${EXTRA}                 \
	${FILE}

	#-mv \
	#~/containedPrograms/arduino-1.8.10/hardware/arduino/avr/libraries/SPI/src/inactive_SPI.h \
	#ar~/containedPrograms/arduino-1.8.10/hardware/arduino/avr/libraries/SPI/src/SPI.h 
	

rectify:
	-mv \
	~/containedPrograms/arduino-1.8.10/hardware/arduino/avr/libraries/SPI/src/inactive_SPI.h \
	~/containedPrograms/arduino-1.8.10/hardware/arduino/avr/libraries/SPI/src/SPI.h 