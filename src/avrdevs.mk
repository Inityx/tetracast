ifeq ($(AVR_PLATFORM), UNO)
    CPUFREQ=16000000
    MCU=atmega328p
    AVRDUDEMCU=m328p
    AVRPORT=/dev/ttyACM0
    AVRBAUD=115200
    DUDEFLAGS=-p $(AVRDUDEMCU) -c arduino -P $(AVRPORT) -b $(AVRBAUD)
endif
ifndef AVR_PLATFORM
    echo "AVR_PLATFORM undefined. I don't know what device to build this for."
    echo "terminating ungracefully."
endif


AVRDUDE=avrdude
ACFLAGS=--std=c++11 -Os -DF_CPU=$(CPUFREQ)UL -mmcu=$(MCU) -lm -DAVR -DPLATFORM_$(AVR_PLATFORM)
OBJ2HEX=avr-objcopy
