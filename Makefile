# Carpetas
SRC_DIR = src
INC_DIR = include

# Archivos fuente y headers detectados automáticamente
SRCS = $(wildcard $(SRC_DIR)/*.c)
HEADERS = $(wildcard $(INC_DIR)/*.h)

# Nombre del ejecutable (ahora en la raíz del proyecto)
TARGET = app1

# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I$(INC_DIR)

# Regla principal
all: $(TARGET)

# Compilar y generar el ejecutable
$(TARGET): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

# Limpiar archivos generados
clean:
	rm -f $(TARGET)
