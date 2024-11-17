#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>  // Inclusion de la bibliothèque assert

// Définition des structures Row et Table
struct Row {
    int id;
    char nom[50];
    char race[10];
};

struct Table {
    struct Row rows[100];  // La table peut contenir jusqu'à 100 lignes
    int row_count;         // Nombre de lignes actuellement insérées
};

// Fonction pour initialiser la table avec des données par défaut
void initialize_table(struct Table* table) {
    table->rows[0].id = 1;
    strcpy(table->rows[0].nom, "Ace");
    strcpy(table->rows[0].race, "chien");

    table->rows[1].id = 2;
    strcpy(table->rows[1].nom, "Oreo");
    strcpy(table->rows[1].race, "chat");

    table->rows[2].id = 3;
    strcpy(table->rows[2].nom, "Sousval");
    strcpy(table->rows[2].race, "cheval");

    table->row_count = 3; // Il y a 3 lignes dans la table
}

// Fonction pour afficher toutes les lignes de la table
void print_table(struct Table* table) {
    for (int i = 0; i < table->row_count; i++) {
        printf("ID: %d, Prenom: %s, Race: %s\n", table->rows[i].id, table->rows[i].nom, table->rows[i].race);
    }
}

// Fonction pour insérer une nouvelle ligne dans la table
void insert_row(struct Table* table, int id, const char* nom, const char* race) {
    if (table->row_count < 100) {
        table->rows[table->row_count].id = id;
        strcpy(table->rows[table->row_count].nom, nom);
        strcpy(table->rows[table->row_count].race, race);
        table->row_count++;
    } else {
        printf("On ne peut plus accueillir d'animaux.\n");
    }
}

// Fonction pour sélectionner et afficher une ligne par ID
void select_by_id(struct Table* table, int id) {
    for (int i = 0; i < table->row_count; i++) {
        if (table->rows[i].id == id) {
            printf("ID: %d, Nom: %s, Race: %s\n", table->rows[i].id, table->rows[i].nom, table->rows[i].race);
            return;
        }
    }
    printf("Il n'y a rien  avec cet ID %d\n", id);
}

// Fonction pour sélectionner et afficher une ligne par nom d'animal
void select_by_name(struct Table* table, const char* nom) {
    for (int i = 0; i < table->row_count; i++) {
        if (strcmp(table->rows[i].nom, nom) == 0) {
            printf("ID: %d, Nom: %s, Race: %s\n", table->rows[i].id, table->rows[i].nom, table->rows[i].race);
            return;
        }
    }
    printf("Il n'y a personne avec ce prenom %s\n", nom);
}

// Fonction pour tester le code avec des assertions
void run_tests() {
    struct Table table;
    initialize_table(&table);

    // Test de l'initialisation
    assert(table.row_count == 3);
    assert(table.rows[0].id == 1);
    assert(strcmp(table.rows[0].nom, "Ace") == 0);
    assert(strcmp(table.rows[0].race, "chien") == 0);

    // Test d'insertion
    insert_row(&table, 4, "Psst", "chien");
    assert(table.row_count == 4);
    assert(table.rows[3].id == 4);
    assert(strcmp(table.rows[3].nom, "Psst") == 0);
    assert(strcmp(table.rows[3].race, "chien") == 0);

    // Test de sélection par ID
    select_by_id(&table, 2);//affiche  "Oreo"
    assert(strcmp(table.rows[1].nom, "Oreo") == 0);

    // Test de sélection par nom
    select_by_name(&table, "Sousval");// affiche  "Sousval"
    assert(strcmp(table.rows[2].nom, "Sousval") == 0);

    printf("Tests réussi.\n");
}

// Fonction pour analyser les commandes utilisateur et exécuter l'action correspondante
void execute_command(struct Table* table, const char* command) {
    char action[10];
    sscanf(command, "%s", action);

    // Vérifier si la commande est INSERT
    if (strcmp(action, "INSERT") == 0) {
        int id;
        char nom[50], race[10];

        // Lire les valeurs de la commande INSERT
        if (sscanf(command, "INSERT %d %49s %9s", &id, nom, race) == 3) {
            insert_row(table, id, nom, race);
            printf("Nouvelle ligne : ID=%d, Prenom=%s, Race=%s\n", id, nom, race);
        } else {
            printf("Essayez : INSERT <id> <nom> <race>\n");
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
                printf("Essayez: SELECT id <id>\n");
            }
        } else if (strcmp(criteria, "nom") == 0) {
            char nom[50];
            if (sscanf(command, "SELECT nom %49s", nom) == 1) {
                select_by_name(table, nom);
            } else {
                printf("Essayez: SELECT nom <nom>\n");
            }
        } else {
            printf("Utilisez 'id' ou 'nom'.\n");
        }
    }
    // Commande pour quitter
    else if (strcmp(action, "QUIT") == 0) {
        printf("Exiting...\n");
        exit(0);
    }
    // Si la commande est inconnue
    else {
        printf("Commande valide: INSERT, SELECT, QUIT\n");
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
