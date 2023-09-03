CC=g++
INCLUDES=-I./inc
CFLAGS:=$(INCLUDES) -lstdc++
DEBUG_CFLAGS:=-DDEBUG -g3

TARGET=programm

SRC_DIR=src
HEADER_DIR=./inc
TARGET_DIR=build
TEST_DIR=test

SOURCES  = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp)
HEADERS  = $(wildcard $(HEADER_DIR)/*.h) $(wildcard $(HEADER_DIR)/*/*.h)

debug: CFLAGS += $(DEBUG_CFLAGS)
debug: $(TARGET)

test: $(TEST) build
	mkdir -p $(TARGET_DIR)/$(TEST_DIR)
	python src/test/test_generator.py 50 ./$(TARGET_DIR)/$(TEST_DIR)
	bash ./do_test.bash

all: build

build: $(SOURCES) $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET_DIR)/$@

clean:
	rm -rf $(TARGET_DIR)

.PHONY: debug test build clean