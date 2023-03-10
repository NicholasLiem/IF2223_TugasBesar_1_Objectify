CXX := g++
CFLAGS := -std=c++17 -ggdb
SOURCE_FOLDER := src
OUTPUT_FOLDER := bin

.PHONY: all

all: build

build:
	@mkdir -p bin
	@$(CXX) $(CFLAGS) $(SOURCE_FOLDER)/*.cpp -o $(OUTPUT_FOLDER)/main

clean:
	@rm -rf bin/*
