# ============================================================
#  CHESS2D - Makefile (WSL / Linux)
# ============================================================

CC = gcc
TARGET = chess2d
SRC_DIR = src

# Add new .c files here as you create them
SRCS = $(SRC_DIR)/main.c

OBJS = $(SRCS:.c=.o)

# pkg-config automatically finds SDL2 installed via apt
SDL_CFLAGS = $(shell pkg-config --cflags sdl2 SDL2_image SDL2_ttf)
SDL_LIBS   = $(shell pkg-config --libs   sdl2 SDL2_image SDL2_ttf)

# -Wall: all warnings  -Wextra: extra warnings  -g: debug info  -std=c99: C standard
CFLAGS = -Wall -Wextra -g -std=c99 $(SDL_CFLAGS)

# ============================================================
#  BUILD RULES
# ============================================================

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(SDL_LIBS) -o $(TARGET)
	@echo ""
	@echo "=== Build successful: $(TARGET) ==="

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# ============================================================
#  UTILITY RULES
# ============================================================

# Delete compiled files to rebuild from scratch
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)
	@echo "Cleaned."

# Build and immediately run the game
run: all
	./$(TARGET)

.PHONY: all clean run