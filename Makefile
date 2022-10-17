SRC := $(wildcard ./src/*.cpp ./src/core/*.cpp ./src/helpers/*.cpp)
CFLAGS = -I ./src -I ./src/core -I ./src/helpers -Wall 

all: cutSphereMove

cutSphereMove: $(SRC)
	g++ -o $@ $^ $(CFLAGS)

clean:
	rm cutSphereMove
