SRC=src
BUILD=build
AVR_DIR=$(BUILD)/avr
DESKTOP_DIR=$(BUILD)/desktop

TETRACAST=$(patsubst %.cpp, %.o, $(notdir $(wildcard src/tc/*.cpp)))
TETRACAST_DESKTOP=$(addprefix $(DESKTOP_DIR)/, $(TETRACAST))
TETRACAST_AVR=$(addprefix $(AVR_DIR)/, $(TETRACAST))

DCXX=clang++
DCFLAGS=--std=c++11 -Wpedantic -Os
SFMLFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

ACXX=avr-g++
AFLAGS=--std=c++11 -Wpedantic -Os

.PHONY: clean desktop arduino avrdude

all: desktop

run: desktop
	$(BUILD)/tc_desktop

dude: avr
	for target in driver display; do \
	    echo -n "Connect $$target chip and press enter... "; \
	    read; \
	    echo avrdude flash:w:$(BUILD)/tc_avr_$$target; \
	done


desktop: CXX=$(DCXX)
desktop: CFLAGS=$(DCFLAGS)
desktop: $(BUILD)/tc_desktop

build/tc_desktop: $(TETRACAST_DESKTOP) $(SRC)/sfml_frontend.cpp $(SRC)/sfml_aux.hpp
	$(CXX) $(SRC)/sfml_frontend.cpp $(TETRACAST_DESKTOP) -o $(BUILD)/tc_desktop $(CFLAGS) $(SFMLFLAGS)


avr: CXX=$(ACXX)
avr: CFLAGS=$(ACFLAGS)
avr: $(BUILD)/tc_avr_driver $(BUILD)/tc_avr_display

$(BUILD)/tc_avr_driver: $(TETRACAST_AVR)
	$(CXX) $(SRC)/avr_driver.cpp $(TETRACAST_AVR) -o $(BUILD)/tc_avr_driver $(CFLAGS)

$(BUILD)/tc_avr_display: $(AVR_DIR)/block.o $(AVR_DIR)/blockvector.o
	$(CXX) $(SRC)/avr_display.cpp $(AVR_DIR)/block.o $(AVR_DIR)/blockvector.o -o $(BUILD)/tc_avr_display $(CFLAGS)


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
	rm -f $(BUILD)/tc_desktop $(BUILD)/tc_avr_display $(BUILD)/tc_avr_driver
