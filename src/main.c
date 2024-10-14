#include <stdio.h>
#include <stdlib.h>
#include "repl.c"
#include <stdbool.h>
#include <string.h>

// Définition des structures Row et Table
struct Row {
    int id;
    char name[50];
    int age;

};

struct Table {
    struct Row rows[100];
    int row_count;
};

// Fonction pour initialiser la table avec des données par défaut
void initialize_table(struct Table* table) {
    // Initialisation d'exemples de lignes
    table->rows[0].id = 1;
    strcpy(table->rows[0].name, "Alice");
    table->rows[0].age = 30;

    table->rows[1].id = 2;
    strcpy(table->rows[1].name, "Bob");
    table->rows[1].age = 25;

    table->rows[2].id = 3;
    strcpy(table->rows[2].name, "Charlie");
    table->rows[2].age = 35;

    table->row_count = 3; // Il y a actuellement 3 lignes dans la table
}

// Fonction pour afficher les lignes de la table
void print_table(struct Table* table) {
    for (int i = 0; i < table->row_count; i++) {
        printf("ID: %d, Name: %s, Age: %d\n", table->rows[i].id, table->rows[i].name, table->rows[i].age);
    }
}


int main(){
  
    struct Table table;

    // Initialiser la table
    initialize_table(&table);

    // Afficher le contenu de la table
    print_table(&table);

    return 0;
  
}
