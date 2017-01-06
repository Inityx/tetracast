ifeq ($(AVR_PLATFORM), UNO)
    CPUFREQ=16000000
    MCU=atmega328p
    AVRDUDEMCU=m328p
    AVRPORT=/dev/ttyACM0
    AVRBAUD=115200
    DUDEFLAGS=-p $(AVRDUDEMCU) -c arduino -P $(AVRPORT) -b $(AVRBAUD)
endif
ifndef AVR_PLATFORM
    $(error No AVR_PLATFORM specified. Not sure what device you want to program.)
endif


AVRDUDE=avrdude
ACFLAGS=--std=c++11 -Os -DF_CPU=$(CPUFREQ)UL -mmcu=$(MCU) -lm -DAVR -DPLATFORM_$(AVR_PLATFORM)
OBJ2HEX=avr-objcopy
