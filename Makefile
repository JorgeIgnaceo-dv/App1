# Carpetas
SRC_DIR = src
INC_DIR = include
BIN_DIR = .

# Archivos fuente y headers detectados automáticamente
SRCS = $(wildcard $(SRC_DIR)/*.c)
HEADERS = $(wildcard $(INC_DIR)/*.h)

# Nombre del ejecutable
TARGET = $(BIN_DIR)/app1

# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I$(INC_DIR)

# Regla principal
all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

# Limpiar archivos generados
clean:
	rm -f $(TARGET)
