flags = -g -Wall

.PHONY: all build test

all: build test

build:
	rm -rf ./bin/*
	gcc -I ./include ./src/example.c $(flags) -o ./bin/example

test:
	./bin/example