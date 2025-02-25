CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -I$(RAYLIB_DIR)
LDFLAGS = $(RAYLIB_DIR)/libraylib.a -lm

RAYLIB_DIR = resource/raylib/src
SRC_DIR = src
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
	rm -rf $(TARGET)

reinstall: uninstall all
