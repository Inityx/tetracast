# Directories
SRC=src
BUILD=build
AVR_DIR=$(BUILD)/avr
DESKTOP_DIR=$(BUILD)/desktop

# Library targets
TETRACAST=$(patsubst %.cpp, %.o, $(notdir $(wildcard src/tc/*.cpp)))
TETRACAST_DESKTOP=$(addprefix $(DESKTOP_DIR)/, $(TETRACAST))
TETRACAST_AVR=$(addprefix $(AVR_DIR)/, $(TETRACAST))

# Desktop compilation settings
DCXX=clang++
DCFLAGS=--std=c++11 -Weverything -g
SFMLFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
WNO_DESKTOP=-Wno-conversion -Wno-switch-enum

# AVR compilation settings
ACXX=avr-g++
AVR_PLATFORM=UNO
DUDETARGETS=driver display


# Orchestration
.PHONY: clean desktop arduino avrdude

all: desktop

run: desktop
	$(BUILD)/tc_desktop

dude: avr
	for target in $(DUDETARGETS); do \
	    echo -n "Connect $$target chip and press enter... "; read; \
	    sudo avrdude -p $(AVRDUDEMCU) $(DUDEFLAGS) -U flash:w:$(BUILD)/tc_avr_$${target}.hex; \
	done

spec: avr
	for target in $(DUDETARGETS); do \
		echo -e "\033[1;33m  Compiled $$target is $$(cat $(BUILD)/tc_avr_$${target}.hex | wc -c) bytes\033[0m"; \
	done

clean:
	rm -rf $(AVR_DIR) $(DESKTOP_DIR)
	rm -f $(BUILD)/tc_desktop $(BUILD)/tc_avr_display.hex $(BUILD)/tc_avr_driver.hex


# Desktop
desktop: CXX=$(DCXX)
desktop: CFLAGS=$(DCFLAGS)
desktop: $(BUILD)/tc_desktop

$(BUILD)/tc_desktop: $(TETRACAST_DESKTOP) $(SRC)/sfml_frontend.cpp $(SRC)/sfml_aux.hpp
	$(CXX) $(SRC)/sfml_frontend.cpp $(TETRACAST_DESKTOP) -o $(BUILD)/tc_desktop $(CFLAGS) $(SFMLFLAGS) $(WNO_DESKTOP)


# AVR
avr: 
include src/avrdevs.mk
avr: CXX=$(ACXX)
avr: CFLAGS=$(ACFLAGS)
avr: $(BUILD)/tc_avr_driver.hex $(BUILD)/tc_avr_display.hex

$(BUILD)/tc_avr_driver.hex: $(TETRACAST_AVR)
	$(CXX) $(SRC)/avr_driver.cpp $(TETRACAST_AVR) -o $(AVR_DIR)/tc_avr_driver.out $(CFLAGS)
	$(OBJ2HEX) -R .eeprom -O ihex $(AVR_DIR)/tc_avr_driver.out $(BUILD)/tc_avr_driver.hex

$(BUILD)/tc_avr_display.hex: $(AVR_DIR)/block.o $(AVR_DIR)/blockvector.o
	$(CXX) $(SRC)/avr_display.cpp $(AVR_DIR)/block.o $(AVR_DIR)/blockvector.o -o $(AVR_DIR)/tc_avr_display.out $(CFLAGS)
	$(OBJ2HEX) -R .eeprom -O ihex $(AVR_DIR)/tc_avr_display.out $(BUILD)/tc_avr_display.hex


# Library
$(DESKTOP_DIR)/%.o: $(addprefix $(SRC)/tc/, %.cpp %.hpp gamedefs.h) | $(DESKTOP_DIR)
	$(CXX) -c $< -o $@ $(CFLAGS)

$(AVR_DIR)/%.o:     $(addprefix $(SRC)/tc/, %.cpp %.hpp gamedefs.h) | $(AVR_DIR)
	$(CXX) -c $< -o $@ $(CFLAGS)

$(DESKTOP_DIR):
	mkdir $(DESKTOP_DIR)

$(AVR_DIR):
	mkdir $(AVR_DIR)
