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
    struct Row rows[100];  // La table peut contenir jusqu'à 100 lignes
    int row_count;         // Nombre de lignes actuellement insérées
};

// Fonction pour initialiser la table avec des données par défaut
void initialize_table(struct Table* table) {
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

// Fonction pour afficher toutes les lignes de la table
void print_table(struct Table* table) {
    for (int i = 0; i < table->row_count; i++) {
        printf("ID: %d, Name: %s, Age: %d\n", table->rows[i].id, table->rows[i].name, table->rows[i].age);
    }
}

// Fonction pour insérer une nouvelle ligne dans la table
void insert_row(struct Table* table, int id, const char* name, int age) {
    if (table->row_count < 100) {
        table->rows[table->row_count].id = id;
        strcpy(table->rows[table->row_count].name, name);
        table->rows[table->row_count].age = age;
        table->row_count++;
    } else {
        printf("Table is full, cannot insert new row.\n");
    }
}

// Fonction pour sélectionner et afficher une ligne par ID
void select_by_id(struct Table* table, int id) {
    for (int i = 0; i < table->row_count; i++) {
        if (table->rows[i].id == id) {
            printf("Selected Row - ID: %d, Name: %s, Age: %d\n", table->rows[i].id, table->rows[i].name, table->rows[i].age);
            return;
        }
    }
    printf("No row found with ID %d\n", id);
}

// Fonction pour sélectionner et afficher une ligne par nom
void select_by_name(struct Table* table, const char* name) {
    for (int i = 0; i < table->row_count; i++) {
        if (strcmp(table->rows[i].name, name) == 0) {
            printf("Selected Row - ID: %d, Name: %s, Age: %d\n", table->rows[i].id, table->rows[i].name, table->rows[i].age);
            return;
        }
    }
    printf("No row found with Name %s\n", name);
}

// Fonction pour analyser les commandes utilisateur et exécuter l'action correspondante
void execute_command(struct Table* table, const char* command) {
    char action[10];
    sscanf(command, "%s", action);

    // Vérifier si la commande est INSERT
    if (strcmp(action, "INSERT") == 0) {
        int id, age;
        char name[50];

        // Lire les valeurs de la commande INSERT
        if (sscanf(command, "INSERT %d %49s %d", &id, name, &age) == 3) {
            insert_row(table, id, name, age);
            printf("Row inserted: ID=%d, Name=%s, Age=%d\n", id, name, age);
        } else {
            printf("Invalid INSERT command. Usage: INSERT <id> <name> <age>\n");
        }
    }
    // Vérifier si la commande est SELECT par ID
    else if (strcmp(action, "SELECT") == 0) {
        char criteria[10];
        sscanf(command, "SELECT %s", criteria);

        if (strcmp(criteria, "id") == 0) {
            int id;
            if (sscanf(command, "SELECT id %d", &id) == 1) {
                select_by_id(table, id);
            } else {
                printf("Invalid SELECT command for ID. Usage: SELECT id <id>\n");
            }
        } else if (strcmp(criteria, "name") == 0) {
            char name[50];
            if (sscanf(command, "SELECT name %49s", name) == 1) {
                select_by_name(table, name);
            } else {
                printf("Invalid SELECT command for Name. Usage: SELECT name <name>\n");
            }
        } else {
            printf("Invalid SELECT criteria. Use 'id' or 'name'.\n");
        }
    }
    // Commande pour quitter
    else if (strcmp(action, "QUIT") == 0) {
        printf("Exiting...\n");
        exit(0);
    }
    // Si la commande est inconnue
    else {
        printf("Unknown command. Available commands: INSERT, SELECT, QUIT\n");
    }
}

int main() {
    struct Table table;

    // Initialiser la table avec des données par défaut
    initialize_table(&table);

    char command[100];

    // Boucle principale qui attend les commandes de l'utilisateur
    while (1) {
        printf("\nEnter command: ");
        fgets(command, 100, stdin);  // Lire la commande de l'utilisateur
        command[strcspn(command, "\n")] = 0;  // Enlever le saut de ligne à la fin

        // Exécuter la commande
        execute_command(&table, command);
    }

    return 0;
}
