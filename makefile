TETRACAST=$(addprefix build/, $(patsubst %.cpp, %.o, $(notdir $(wildcard src/tc/*.cpp))))

DCXX=clang++
DCFLAGS=--std=c++14
SFMLFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

ACXX=
AFLAGS=


all: desktop

run: desktop
	build/tc_desktop

desktop: CXX=$(DCXX)
desktop: CFLAGS=$(DCFLAGS)
desktop: build/tc_desktop

build/tc_desktop: $(TETRACAST) src/sfml_frontend.cpp
	$(CXX) src/sfml_frontend.cpp  $(TETRACAST) -o build/tc_desktop $(CFLAGS) $(SFMLFLAGS)


arduino: CXX=$(ACXX)
arduino: CFLAGS=$(ACFLAGS)
arduino: build/arduino_driver build/arduino_display

build/arduino_driver: $(TETRACAST)
	
build/arduino_display: build/block.o build/blockvector.o


$(TETRACAST): build/%.o: $(addprefix src/tc/, %.cpp %.hpp gamedefs.h)
	$(CXX) -c $< -o $@ $(CFLAGS)


.PHONY: clean

clean:
	rm -f build/*.o
	rm -f build/tc_desktop
