# Nombre del ejecutable
TARGET = app1

# Archivos fuente
SRCS = main.c parser.c metrics.c

# Archivos de cabecera
HEADERS = parser.h order.h metrics.h order.h

# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Regla principal
$(TARGET): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

# Limpiar archivos generados
clean:
	rm -f $(TARGET)
