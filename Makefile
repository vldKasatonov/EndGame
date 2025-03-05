CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -I$(RAYLIB_DIR)
LDFLAGS = $(RAYLIB_DIR)/libraylib.a -lm
LDFLAGS_MACOS = $(RAYLIB_DIR)/libraylib.a -lm -framework Cocoa -framework IOKit

RAYLIB_DIR = resource/raylib/src
SRC_DIR = src
OBJ_DIR = obj
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET = endgame
MACOS = endgame

macos:
	$(MAKE) -C $(RAYLIB_DIR)
	$(MAKE) $(MACOS)

$(MACOS): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS_MACOS) -o $(MACOS)

all:
	$(MAKE) -C $(RAYLIB_DIR)
	$(MAKE) $(TARGET)

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
	rm -f $(RAYLIB_DIR)/libraylib.a

reinstall: uninstall all
