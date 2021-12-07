
MKCWD=mkdir -p $(@D)

PROJECT_NAME = test

CXX ?= g++
WARNS = -Wall -Werror -Wextra -Wvla -fsanitize=undefined -fsanitize=address
CFLAGS = -std=c++17 -Ofast -march=native -Isrc/ $(WARNS)

BUILD_DIR = build

# source files

CFILES = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp) $(wildcard src/*/*/*.cpp)
HFILES = $(wildcard src/*.hpp)
DFILES = $(patsubst src/%.cpp, $(BUILD_DIR)/%.d, $(CFILES))
OFILES = $(patsubst src/%.cpp, $(BUILD_DIR)/%.o, $(CFILES))

OUTPUT = build/$(PROJECT_NAME).elf


$(OUTPUT): $(OFILES)
	@$(MKCWD)
	@echo " LD  [ $@ ] $<"
	@$(CXX) $(CFLAGS) -flto -lpthread -ldl -llua -lm -lSDL2 -lX11 -o $@ $^


$(BUILD_DIR)/%.o: src/%.cpp
	@$(MKCWD)
	@echo " CXX [ $@ ] $<"
	@$(CXX) $(CFLAGS) -MMD -MP $< -c -o $@

run: $(OUTPUT)
	@$(OUTPUT) ./samples/hello.lua

all: $(OUTPUT)

screen: $(OUTPUT)
	Xephyr -br -noreset -screen "1024x640" :1 &
	sleep 0.5
	DISPLAY=:1.0 $(OUTPUT) ./samples/hello.lua

clean:
	@rm -rf build/

-include $(DFILES)
