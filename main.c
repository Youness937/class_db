#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>  // Pour utiliser assert dans les tests

// Définition des structures Animal et Refuge
struct Animal {
    int id;
    char nom[50];
    char race[10];
};

struct Refuge {
    struct Animal listeAnimaux[100];  // Liste d'animaux pouvant contenir jusqu'à 100 entrées
    int totalAnimaux;                 // Nombre total d'animaux dans le refuge
    int indiceActuel;                 // Position actuelle utilisée pour suivi
};

// Fonction pour ajouter des animaux par défaut dans le refuge
void creerRefuge(struct Refuge* refuge) {
    refuge->listeAnimaux[0].id = 1;
    strcpy(refuge->listeAnimaux[0].nom, "Ace");
    strcpy(refuge->listeAnimaux[0].race, "chien");

    refuge->listeAnimaux[1].id = 2;
    strcpy(refuge->listeAnimaux[1].nom, "Oreo");
    strcpy(refuge->listeAnimaux[1].race, "chat");

    refuge->listeAnimaux[2].id = 3;
    strcpy(refuge->listeAnimaux[2].nom, "Sousval");
    strcpy(refuge->listeAnimaux[2].race, "cheval");

    refuge->totalAnimaux = 3;   // Trois animaux sont dans le refuge
    refuge->indiceActuel = 0;   // Départ à la première position
}

// Fonction pour afficher tous les animaux du refuge
void afficherRefuge(struct Refuge* refuge) {
    for (int i = 0; i < refuge->totalAnimaux; i++) {
        printf("ID: %d, Nom: %s, Race: %s\n", refuge->listeAnimaux[i].id, refuge->listeAnimaux[i].nom, refuge->listeAnimaux[i].race);
    }
}

// Fonction pour ajouter un nouvel animal dans le refuge
void ajouterAnimal(struct Refuge* refuge, int id, const char* nom, const char* race) {
    if (refuge->totalAnimaux < 100) {
        refuge->listeAnimaux[refuge->totalAnimaux].id = id;
        strcpy(refuge->listeAnimaux[refuge->totalAnimaux].nom, nom);
        strcpy(refuge->listeAnimaux[refuge->totalAnimaux].race, race);
        refuge->totalAnimaux++;
        refuge->indiceActuel = refuge->totalAnimaux - 1;  // Mise à jour de la position actuelle
    } else {
        printf("Le refuge est plein, impossible d'ajouter plus d'animaux.\n");
    }
}

// Fonction pour rechercher un animal par ID
void chercherParId(struct Refuge* refuge, int id) {
    for (int i = 0; i < refuge->totalAnimaux; i++) {
        if (refuge->listeAnimaux[i].id == id) {
            printf("ID: %d, Nom: %s, Race: %s\n", refuge->listeAnimaux[i].id, refuge->listeAnimaux[i].nom, refuge->listeAnimaux[i].race);
            refuge->indiceActuel = i;  // Mise à jour de la position actuelle
            return;
        }
    }
    printf("Aucun animal trouvé avec cet ID %d\n", id);
}

// Fonction pour rechercher un animal par nom
void chercherParNom(struct Refuge* refuge, const char* nom) {
    for (int i = 0; i < refuge->totalAnimaux; i++) {
        if (strcmp(refuge->listeAnimaux[i].nom, nom) == 0) {
            printf("ID: %d, Nom: %s, Race: %s\n", refuge->listeAnimaux[i].id, refuge->listeAnimaux[i].nom, refuge->listeAnimaux[i].race);
            refuge->indiceActuel = i;  // Mise à jour de la position actuelle
            return;
        }
    }
    printf("Aucun animal trouvé avec ce nom %s\n", nom);
}

// Fonction pour tester le code avec des assertions
void verifierCode() {
    struct Refuge refuge;
    creerRefuge(&refuge);

    // Test d'initialisation
    assert(refuge.totalAnimaux == 3);
    assert(refuge.listeAnimaux[0].id == 1);
    assert(strcmp(refuge.listeAnimaux[0].nom, "Ace") == 0);
    assert(strcmp(refuge.listeAnimaux[0].race, "chien") == 0);

    // Test d'ajout
    ajouterAnimal(&refuge, 4, "Psst", "chien");
    assert(refuge.totalAnimaux == 4);
    assert(refuge.listeAnimaux[3].id == 4);
    assert(strcmp(refuge.listeAnimaux[3].nom, "Psst") == 0);
    assert(strcmp(refuge.listeAnimaux[3].race, "chien") == 0);
    assert(refuge.indiceActuel == 3);

    // Test de recherche par ID
    chercherParId(&refuge, 2);  // Doit afficher "Oreo"
    assert(strcmp(refuge.listeAnimaux[1].nom, "Oreo") == 0);
    assert(refuge.indiceActuel == 1);

    // Test de recherche par nom
    chercherParNom(&refuge, "Sousval");  // Doit afficher "Sousval"
    assert(strcmp(refuge.listeAnimaux[2].nom, "Sousval") == 0);
    assert(refuge.indiceActuel == 2);

    printf("Tests réussis.\n");
}

// Fonction pour analyser les commandes utilisateur et exécuter l'action correspondante
void executerCommande(struct Refuge* refuge, const char* commande) {
    char action[10];
    sscanf(commande, "%s", action);

    // Vérifier si la commande est INSERT
    if (strcmp(action, "INSERT") == 0) {
        int id;
        char nom[50], race[10];

        // Lire les valeurs de la commande INSERT
        if (sscanf(commande, "INSERT %d %49s %9s", &id, nom, race) == 3) {
            ajouterAnimal(refuge, id, nom, race);
            printf("Nouvel animal ajouté : ID=%d, Nom=%s, Race=%s\n", id, nom, race);
        } else {
            printf("Format incorrect. Essayez : INSERT <id> <nom> <race>\n");
        }
    }
    // Vérifier si la commande est SELECT par ID ou nom
    else if (strcmp(action, "SELECT") == 0) {
        char critere[10];
        sscanf(commande, "SELECT %s", critere);

        if (strcmp(critere, "id") == 0) {
            int id;
            if (sscanf(commande, "SELECT id %d", &id) == 1) {
                chercherParId(refuge, id);
            } else {
                printf("Format incorrect. Essayez : SELECT id <id>\n");
            }
        } else if (strcmp(critere, "nom") == 0) {
            char nom[50];
            if (sscanf(commande, "SELECT nom %49s", nom) == 1) {
                chercherParNom(refuge, nom);
            } else {
                printf("Format incorrect. Essayez : SELECT nom <nom>\n");
            }
        } else {
            printf("Critère non reconnu. Utilisez 'id' ou 'nom'.\n");
        }
    }
    // Commande pour quitter
    else if (strcmp(action, "QUIT") == 0) {
        printf("Fin du programme.\n");
        exit(0);
    }
    // Si la commande est inconnue
    else {
        printf("Commandes valides : INSERT, SELECT, QUIT\n");
    }
}

int main() {
    struct Refuge refuge;

    // Exécuter les tests
    verifierCode();

    // Initialiser le refuge avec des animaux par défaut
    creerRefuge(&refuge);

    char commande[100];

    // Boucle principale qui attend les commandes de l'utilisateur
    while (1) {
        printf("\nEntrer une commande : ");
        fgets(commande, 100, stdin);  // Lire la commande de l'utilisateur
        commande[strcspn(commande, "\n")] = 0;  // Retirer le saut de ligne

        // Exécuter la commande
        executerCommande(&refuge, commande);
    }

    return 0;
}
