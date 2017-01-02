SRC=src
BUILD=build
AVR_DIR=$(BUILD)/avr
DESKTOP_DIR=$(BUILD)/desktop

TETRACAST=$(patsubst %.cpp, %.o, $(notdir $(wildcard src/tc/*.cpp)))
TETRACAST_DESKTOP=$(addprefix $(DESKTOP_DIR)/, $(TETRACAST))
TETRACAST_AVR=$(addprefix $(AVR_DIR)/, $(TETRACAST))

DCXX=clang++
DCFLAGS=--std=c++11 -Weverything -g
SFMLFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
WNO_DESKTOP=-Wno-conversion -Wno-switch-enum

#AVR compilation settings
ACXX=avr-g++
CPUFREQ=16000000
MCU=atmega328p
ACFLAGS=--std=c++11 -Os -DF_CPU=$(CPUFREQ)UL -mmcu=$(MCU) -lm -DAVR
OBJ2HEX=avr-objcopy
AVRDUDEMCU=m328p
AVRPORT=/dev/ttyACM0
AVRBAUD=115200
DUDEFLAGS=-p $(AVRDUDEMCU) -c arduino -P $(AVRPORT) -b $(AVRBAUD)
AVRDUDE=avrdude

.PHONY: clean desktop arduino avrdude


all: desktop

run: desktop
	$(BUILD)/tc_desktop

dude: avr
	for target in driver display; do \
	    echo -n "Connect $$target chip and press enter... "; read; \
	    echo avrdude -p $(AVRDUDEMCU) $(DUDEFLAGS) -U flash:w:$(BUILD)/tc_avr_$${target}.hex; \
	done


desktop: CXX=$(DCXX)
desktop: CFLAGS=$(DCFLAGS)
desktop: $(BUILD)/tc_desktop

$(BUILD)/tc_desktop: $(TETRACAST_DESKTOP) $(SRC)/sfml_frontend.cpp $(SRC)/sfml_aux.hpp
	$(CXX) $(SRC)/sfml_frontend.cpp $(TETRACAST_DESKTOP) -o $(BUILD)/tc_desktop $(CFLAGS) $(SFMLFLAGS) $(WNO_DESKTOP)


avr: CXX=$(ACXX)
avr: CFLAGS=$(ACFLAGS)
avr: $(BUILD)/tc_avr_driver.hex $(BUILD)/tc_avr_display.hex

$(BUILD)/tc_avr_driver.hex: $(TETRACAST_AVR)
	$(CXX) $(SRC)/avr_driver.cpp $(TETRACAST_AVR) -o $(AVR_DIR)/tc_avr_driver.out $(CFLAGS)
	$(OBJ2HEX) -R .eeprom -O ihex $(AVR_DIR)/tc_avr_driver.out $(BUILD)/tc_avr_driver.hex

$(BUILD)/tc_avr_display.hex: $(AVR_DIR)/block.o $(AVR_DIR)/blockvector.o
	$(CXX) $(SRC)/avr_display.cpp $(AVR_DIR)/block.o $(AVR_DIR)/blockvector.o -o $(AVR_DIR)/tc_avr_display.out $(CFLAGS)
	$(OBJ2HEX) -R .eeprom -O ihex $(AVR_DIR)/tc_avr_display.out $(BUILD)/tc_avr_display.hex


$(DESKTOP_DIR)/%.o: $(addprefix $(SRC)/tc/, %.cpp %.hpp gamedefs.h) | $(DESKTOP_DIR)
	$(CXX) -c $< -o $@ $(CFLAGS)

$(AVR_DIR)/%.o:     $(addprefix $(SRC)/tc/, %.cpp %.hpp gamedefs.h) | $(AVR_DIR)
	$(CXX) -c $< -o $@ $(CFLAGS)

$(DESKTOP_DIR):
	mkdir $(DESKTOP_DIR)

$(AVR_DIR):
	mkdir $(AVR_DIR)


clean:
	rm -rf $(AVR_DIR) $(DESKTOP_DIR)
	rm -f $(BUILD)/tc_desktop $(BUILD)/tc_avr_display.hex $(BUILD)/tc_avr_driver.hex
