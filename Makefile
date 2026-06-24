.PHONY: all clean run

COMPILER = g++
COMPILER_FLAG = -std=c++23 -fmodules-ts

default: all

run: all
	./saffron

all: saffron

saffron: main.o
	${COMPILER} $^ -o App

%.o: %.cpp
	${COMPILER} -c  ${COMPILER_FLAG} $<

clean:
	@-rm saffron
	@-rm func.o
	@-rm main.o
	@-rm -r gcm.cache
