#include <stdio.h>
#include <stdlib.h>
#include "repl.c"
#include <stdbool.h>
#include <string.h>

// Définition des structures Row et Table
struct Row {
    int id;
    char nom[50];
    int age;
};

struct Table {
    struct Row rows[100];  // La table peut contenir jusqu'à 100 lignes
    int row_count;         // Nombre de lignes actuellement insérées
};

// Fonction pour initialiser la table avec des données par défaut
void initialize_table(struct Table* table) {
    table->rows[0].id = 1;
    strcpy(table->rows[0].nom, "You");
    table->rows[0].age = 25;

    table->rows[1].id = 2;
    strcpy(table->rows[1].nom, "Mesrines");
    table->rows[1].age = 33;

    table->rows[2].id = 3;
    strcpy(table->rows[2].nom, "ALI");
    table->rows[2].age = 22;

    table->row_count = 3; // Il y a actuellement 3 lignes dans la table
}

// Fonction pour afficher toutes les lignes de la table
void print_table(struct Table* table) {
    for (int i = 0; i < table->row_count; i++) {
        printf("ID: %d, Nom: %s, Age: %d\n", table->rows[i].id, table->rows[i].nom, table->rows[i].age);
    }
}

// Fonction pour insérer une nouvelle ligne dans la table
void insert_row(struct Table* table, int id, const char* nom, int age) {
    if (table->row_count < 100) {
        table->rows[table->row_count].id = id;
        strcpy(table->rows[table->row_count].nom, nom);
        table->rows[table->row_count].age = age;
        table->row_count++;
    } else {
        printf("On ne peut plus effectuer d'insert.\n");
    }
}

// Fonction pour sélectionner et afficher une ligne par ID
void select_by_id(struct Table* table, int id) {
    for (int i = 0; i < table->row_count; i++) {
        if (table->rows[i].id == id) {
            printf("ID: %d, Nom: %s, Age: %d\n", table->rows[i].id, table->rows[i].nom, table->rows[i].age);
            return;
        }
    }
    printf("Il n'y a pas de ligne avec cet ID %d\n", id);
}

// Fonction pour sélectionner et afficher une ligne par nom
void select_by_name(struct Table* table, const char* nom) {
    for (int i = 0; i < table->row_count; i++) {
        if (strcmp(table->rows[i].nom, nom) == 0) {
            printf("ID: %d, Nom: %s, Age: %d\n", table->rows[i].id, table->rows[i].nom, table->rows[i].age);
            return;
        }
    }
    printf("Pas de ligne avec ce nom %s\n", nom);
}

// Fonction pour analyser les commandes utilisateur et exécuter l'action correspondante
void execute_command(struct Table* table, const char* command) {
    char action[10];
    sscanf(command, "%s", action);

    // Vérifier si la commande est INSERT
    if (strcmp(action, "INSERT") == 0) {
        int id, age;
        char nom[50];

        // Lire les valeurs de la commande INSERT
        if (sscanf(command, "INSERT %d %49s %d", &id, nom, &age) == 3) {
            insert_row(table, id, nom, age);
            printf("Nouvelle ligne : ID=%d, Nom=%s, Age=%d\n", id, nom, age);
        } else {
            printf("Commande invalide. Essayez : INSERT <id> <nom> <age>\n");
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
                printf("Commande invalide  pour l'ID. Essayez: SELECT id <id>\n");
            }
        } else if (strcmp(criteria, "nom") == 0) {
            char nom[50];
            if (sscanf(command, "SELECT nom %49s", nom) == 1) {
                select_by_name(table, nom);
            } else {
                printf("Commande invalide pour le nom. Essayez: SELECT nom <nom>\n");
            }
        } else {
            printf("Les critères sont invalides. Utilisez 'id' ou 'nom'.\n");
        }
    }
    // Commande pour quitter
    else if (strcmp(action, "QUIT") == 0) {
        printf("Exiting...\n");
        exit(0);
    }
    // Si la commande est inconnue
    else {
        printf("Commande inconnue. Commande valide: INSERT, SELECT, QUIT\n");
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
