#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>  // Inclusion de la bibliothèque assert

// Définition des structures Row et Table
struct Row {
    int id;
    char nom_animal[50];
    char race[10];
};

struct Table {
    struct Row rows[100];  // La table peut contenir jusqu'à 100 lignes
    int row_count;         // Nombre de lignes actuellement insérées
};

// Fonction pour initialiser la table avec des données par défaut
void initialize_table(struct Table* table) {
    table->rows[0].id = 1;
    strcpy(table->rows[0].nom_animal, "Max");
    strcpy(table->rows[0].race, "chien");

    table->rows[1].id = 2;
    strcpy(table->rows[1].nom_animal, "Bella");
    strcpy(table->rows[1].race, "chat");

    table->rows[2].id = 3;
    strcpy(table->rows[2].nom_animal, "Spirit");
    strcpy(table->rows[2].race, "cheval");

    table->row_count = 3; // Il y a actuellement 3 lignes dans la table
}

// Fonction pour afficher toutes les lignes de la table
void print_table(struct Table* table) {
    for (int i = 0; i < table->row_count; i++) {
        printf("ID: %d, Nom Animal: %s, Race: %s\n", table->rows[i].id, table->rows[i].nom_animal, table->rows[i].race);
    }
}

// Fonction pour insérer une nouvelle ligne dans la table
void insert_row(struct Table* table, int id, const char* nom_animal, const char* race) {
    if (table->row_count < 100) {
        table->rows[table->row_count].id = id;
        strcpy(table->rows[table->row_count].nom_animal, nom_animal);
        strcpy(table->rows[table->row_count].race, race);
        table->row_count++;
    } else {
        printf("On ne peut plus effectuer d'insert.\n");
    }
}

// Fonction pour sélectionner et afficher une ligne par ID
void select_by_id(struct Table* table, int id) {
    for (int i = 0; i < table->row_count; i++) {
        if (table->rows[i].id == id) {
            printf("ID: %d, Nom Animal: %s, Race: %s\n", table->rows[i].id, table->rows[i].nom_animal, table->rows[i].race);
            return;
        }
    }
    printf("Il n'y a pas de ligne avec cet ID %d\n", id);
}

// Fonction pour sélectionner et afficher une ligne par nom d'animal
void select_by_name(struct Table* table, const char* nom_animal) {
    for (int i = 0; i < table->row_count; i++) {
        if (strcmp(table->rows[i].nom_animal, nom_animal) == 0) {
            printf("ID: %d, Nom Animal: %s, Race: %s\n", table->rows[i].id, table->rows[i].nom_animal, table->rows[i].race);
            return;
        }
    }
    printf("Pas de ligne avec ce nom d'animal %s\n", nom_animal);
}

// Fonction pour tester le code avec des assertions
void run_tests() {
    struct Table table;
    initialize_table(&table);

    // Test de l'initialisation
    assert(table.row_count == 3);
    assert(table.rows[0].id == 1);
    assert(strcmp(table.rows[0].nom_animal, "Max") == 0);
    assert(strcmp(table.rows[0].race, "chien") == 0);

    // Test d'insertion
    insert_row(&table, 4, "Milo", "chien");
    assert(table.row_count == 4);
    assert(table.rows[3].id == 4);
    assert(strcmp(table.rows[3].nom_animal, "Milo") == 0);
    assert(strcmp(table.rows[3].race, "chien") == 0);

    // Test de sélection par ID
    select_by_id(&table, 2); // Devrait afficher "Bella"
    assert(strcmp(table.rows[1].nom_animal, "Bella") == 0);

    // Test de sélection par nom
    select_by_name(&table, "Spirit"); // Devrait afficher "Spirit"
    assert(strcmp(table.rows[2].nom_animal, "Spirit") == 0);

    printf("Tous les tests ont réussi.\n");
}

// Fonction pour analyser les commandes utilisateur et exécuter l'action correspondante
void execute_command(struct Table* table, const char* command) {
    char action[10];
    sscanf(command, "%s", action);

    // Vérifier si la commande est INSERT
    if (strcmp(action, "INSERT") == 0) {
        int id;
        char nom_animal[50], race[10];

        // Lire les valeurs de la commande INSERT
        if (sscanf(command, "INSERT %d %49s %9s", &id, nom_animal, race) == 3) {
            insert_row(table, id, nom_animal, race);
            printf("Nouvelle ligne : ID=%d, Nom Animal=%s, Race=%s\n", id, nom_animal, race);
        } else {
            printf("Commande invalide. Essayez : INSERT <id> <nom_animal> <race>\n");
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
                printf("Commande invalide pour l'ID. Essayez: SELECT id <id>\n");
            }
        } else if (strcmp(criteria, "nom") == 0) {
            char nom_animal[50];
            if (sscanf(command, "SELECT nom %49s", nom_animal) == 1) {
                select_by_name(table, nom_animal);
            } else {
                printf("Commande invalide pour le nom. Essayez: SELECT nom <nom_animal>\n");
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

    // Exécuter les tests
    run_tests();

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
