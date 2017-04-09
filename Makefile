SRC = src
BUILD = build
OBJ = obj
BIN = bin

CC = arm-none-eabi-gcc
CFLAGS := -O2 -std=c11 -mthumb-interwork -mthumb -Wall -Wextra -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wredundant-decls -Wshadow -Wsign-conversion -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused

all: $(BUILD)/main.gba

clean:
	rm -r $(BIN) $(OBJ) $(BUILD)

$(BUILD)/main.gba: $(BIN)/main.elf
	mkdir -p $(BUILD)
	arm-none-eabi-objcopy -v -O binary $^ $@
	gbafix $@

$(BIN)/main.elf: $(OBJ)/main.o $(OBJ)/gba.o
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) $^ -o $@ -specs=gba.specs

$(OBJ)/main.o: $(SRC)/main.c
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -o $@ -c $(SRC)/main.c

$(OBJ)/gba.o: $(SRC)/gba.c $(SRC)/gba.h
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -o $@ -c $(SRC)/gba.c

.PHONY: all clean
