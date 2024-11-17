CC = gcc
CFLAGS = -Wall -Wextra -g

# Noms des fichiers objets et de l'exécutable
OBJS = main.o
EXEC = bdd_c

# Règle par défaut pour créer l'exécutable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

# Compilation de main.o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

# Règle pour exécuter le programme
run: $(EXEC)
	./$(EXEC)

# Règle pour nettoyer les fichiers objets et l'exécutable
clean:
	rm -f $(OBJS) $(EXEC)
