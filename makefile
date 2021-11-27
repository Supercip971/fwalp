
MKCWD=mkdir -p $(@D)

PROJECT_NAME = test

CC ?= gcc
CFLAGS = -O2 --analyzer -Isrc/ -fsanitize=address -fsanitize=undefined

BUILD_DIR = build

# source files

CFILES = $(wildcard src/*.c)
HFILES = $(wildcard src/*.h)
DFILES = $(patsubst src/%.c, $(BUILD_DIR)/%.d, $(CFILES))
OFILES = $(patsubst src/%.c, $(BUILD_DIR)/%.o, $(CFILES))

OUTPUT = build/$(PROJECT_NAME).elf


$(OUTPUT): $(OFILES)
	@$(MKCWD)
	@echo " LD [ $@ ] $<"
	@$(CC)  -llua -lSDL2 -lX11 -o $@ $^ $(CFLAGS)

$(BUILD_DIR)/%.o: src/%.c
	@$(MKCWD)
	@echo " CC [ $@ ] $<"
	@$(CC) $(CFLAGS) -MMD -MP $< -c -o $@

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
