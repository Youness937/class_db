# Nom de l'exécutable final
EXEC = bdd_c

# Liste des fichiers sources
SRC = main.c

# Liste des fichiers objets (correspond à SRC mais avec extension .o)
OBJ = $(SRC:.c=.o)

# Flags de compilation
CFLAGS = -Wall -Wextra -g

# Compilateur
CC = gcc

# Règle par défaut pour générer l'exécutable
all: $(EXEC)

# Règle pour créer l'exécutable en liant les objets
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

# Règle pour compiler les fichiers .c en fichiers .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f $(OBJ) $(EXEC)

# Nettoyage des fichiers objets seulement
clean_obj:
	rm -f $(OBJ)

# Nettoyage complet et recompilation complète
rebuild: clean all

# Exécution du programme après la compilation
run: $(EXEC)
	./$(EXEC)

