EXEC = bdd_c
SRC = main.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -g
CC = gcc

all: $(EXEC)
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ) $(EXEC)
clean_obj:
	rm -f $(OBJ)
rebuild: clean all

run: $(EXEC)
	./$(EXEC)


