CXX := g++

SOURCE_FOLDER := src
OUTPUT_FOLDER := bin
INCLUDE_FOLDERS := lib lib/states lib/entities lib/entities/combos

CFLAGS := -std=c++17 -ggdb
CINCLUDES = $(INCLUDE_FOLDERS:%=-I$(SOURCE_FOLDER)/%)

DIRS := apps/acts apps/entities apps/managers apps/states
FILES := $(foreach DIR,$(DIRS),$(wildcard $(SOURCE_FOLDER)/$(DIR)/*.cpp))
MAIN := $(SOURCE_FOLDER)/main.cpp

.PHONY: all

all: build

build: $(FILES)
	@mkdir -p bin
	@$(CXX) $(CFLAGS) $(CINCLUDES) $(MAIN) $^ -o $(OUTPUT_FOLDER)/main

clean:
	@rm -rf bin/*
