CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -I$(INC_DIR)
#for Linux
LDFLAGS = $(RAYLIB_DIR)/linux/libraylib.a -lm
#for MacOS
#LDFLAGS = $(RAYLIB_DIR)/macos/libraylib.a -framework Cocoa -framework IOKit

RAYLIB_DIR = resource/raylib
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET = endgame

all: $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(OBJECTS)

uninstall: clean
	rm -rf $(OBJ_DIR)
	rm -f $(TARGET)

reinstall: uninstall all
