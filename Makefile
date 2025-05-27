CC = gcc
CFLAGS = -Wall -Wextra
SRC = src/main.c src/tarefa.c src/lista.c src/pilha.c src/fila.c
OBJ = $(SRC:.c=.o)
TARGET = gerenciador

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean 