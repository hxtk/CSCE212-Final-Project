SRC = src
BUILD = build
OBJ = obj
BIN = bin

OBJECTS = $(addprefix $(OBJ)/,main.o gba.o graphics.o player.o ball.o)

vpath %.h $(SRC)
vpath %.c $(SRC)
vpath %.o $(OBJ)
vpath %.elf $(BIN)

CC = arm-none-eabi-gcc
CFLAGS := -O2 -std=c11 -mthumb-interwork -mthumb -Wall -Wextra -Wcast-align \
-Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op \
-Wmissing-declarations -Wmissing-include-dirs -Wredundant-decls -Wshadow \
-Wsign-conversion -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused

# Phony rules
all: $(BUILD)/main.gba

clean:
	rm -rf $(BIN) $(OBJ) $(BUILD)

distclean:
	rm -rf $(BIN) $(OBJ)

run:
	visualboyadvance-m $(BUILD)/main.gba

.PHONY: all clean run

# Release rules
$(BUILD)/main.gba: main.elf | $(BUILD)
	arm-none-eabi-objcopy -v -O binary $^ $@
	gbafix $@

# Binary rules
$(BIN)/main.elf: $(OBJECTS) | $(BIN)
	$(CC) $(CFLAGS) $^ -o $@ -specs=gba.specs

# Object rules
$(OBJECTS): | $(OBJ)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)/main.o: main.c

$(OBJ)/gba.o: gba.c gba.h

$(OBJ)/graphics.o: graphics.c graphics.h gba.h

$(OBJ)/player.o: player.c player.h graphics.h

$(OBJ)/ball.o: ball.c ball.h graphics.h

# Build environment rules
$(BUILD):
	mkdir -p $(BUILD)

$(BIN):
	mkdir -p $(BIN)

$(OBJ):
	mkdir -p $(OBJ)

