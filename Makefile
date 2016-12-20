GXX := clang++
BIN_NAME := main
CPP_FILES := $(wildcard src/*.cpp)

build:
	@$(GXX) $(CPP_FILES) -o $(BIN_NAME) -O2

run:
	@./$(BIN_NAME)
