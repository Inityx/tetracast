TETRACAST=$(addprefix build/, $(patsubst %.cpp, %.o, $(notdir $(wildcard src/tc/*.cpp))))

DCXX=clang++
DCFLAGS=
SFMLFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

ACXX=
AFLAGS=


all: desktop

desktop: CXX=$(DCXX)
desktop: CFLAGS=$(DCFLAGS)
desktop: build/tc_desktop

build/tc_desktop: $(TETRACAST) src/sfml_frontend.cpp
	$(CXX) src/sfml_frontend.cpp  $(TETRACAST) -o build/tc_desktop $(CFLAGS) $(SFMLFLAGS)

arduino: CXX=$(ACXX)
arduino: CFLAGS=$(ACFLAGS)
arduino: $(TETRACAST)

$(TETRACAST): build/%.o: src/tc/%.cpp src/tc/%.hpp src/tc/gamedefs.h
	$(CXX) -c $< -o $@ $(CFLAGS) 


.PHONY: clean

clean:
	rm -f build/*.o
	rm -f build/tc_desktop
