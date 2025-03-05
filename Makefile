CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -I$(RAYLIB_DIR)
#for Linux
LDFLAGS = $(RAYLIB_DIR)/libraylib.a -lm
#for MacOS
#LDFLAGS = $(RAYLIB_DIR)/libraylib.a -framework Cocoa -framework IOKit

RAYLIB_DIR = resource/raylib/src
SRC_DIR = src
OBJ_DIR = obj
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET = endgame

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
	rm -f $(RAYLIB_DIR)/*.o

reinstall: uninstall all
