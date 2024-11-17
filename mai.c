#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Définition de la structure pour un nœud de l'arbre binaire
struct Node {
    int id;
    char nom[50];
    char race[10];
    struct Node* left;
    struct Node* right;
};

// Fonction pour créer un nouveau nœud
struct Node* create_node(int id, const char* nom, const char* race) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->id = id;
    strcpy(new_node->nom, nom);
    strcpy(new_node->race, race);
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Fonction d'insertion dans l'arbre binaire
struct Node* insert_node(struct Node* root, int id, const char* nom, const char* race) {
    if (root == NULL) {
        return create_node(id, nom, race);
    }

    if (id < root->id) {
        root->left = insert_node(root->left, id, nom, race);
    } else if (id > root->id) {
        root->right = insert_node(root->right, id, nom, race);
    }

    return root;
}

// Fonction de recherche d'un animal par ID
struct Node* search_by_id(struct Node* root, int id) {
    if (root == NULL || root->id == id) {
        return root;
    }

    if (id < root->id) {
        return search_by_id(root->left, id);
    } else {
        return search_by_id(root->right, id);
    }
}

// Fonction de parcours en ordre (in-order traversal)
void inorder_traversal(struct Node* root) {
    if (root == NULL) {
        return;
    }

    inorder_traversal(root->left);
    printf("ID: %d, Nom: %s, Race: %s\n", root->id, root->nom, root->race);
    inorder_traversal(root->right);
}

// Fonction pour supprimer un nœud de l'arbre
struct Node* delete_node(struct Node* root, int id) {
    if (root == NULL) {
        return root;
    }

    if (id < root->id) {
        root->left = delete_node(root->left, id);
    } else if (id > root->id) {
        root->right = delete_node(root->right, id);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = root->right;
        while (temp && temp->left != NULL) {
            temp = temp->left;
        }

        root->id = temp->id;
        strcpy(root->nom, temp->nom);
        strcpy(root->race, temp->race);

        root->right = delete_node(root->right, temp->id);
    }

    return root;
}

// Fonction pour analyser et exécuter les commandes de l'utilisateur
void execute_command(struct Node** root, const char* command) {
    char action[10];
    sscanf(command, "%s", action);

    if (strcmp(action, "INSERT") == 0) {
        int id;
        char nom[50], race[10];
        if (sscanf(command, "INSERT %d %49s %9s", &id, nom, race) == 3) {
            *root = insert_node(*root, id, nom, race);
            printf("L'animal avec ID=%d, Nom=%s, Race=%s a été ajouté.\n", id, nom, race);
        } else {
            printf("Commande invalide. Utilisez : INSERT <id> <nom> <race>\n");
        }
    } else if (strcmp(action, "SELECT") == 0) {
        int id;
        if (sscanf(command, "SELECT id %d", &id) == 1) {
            struct Node* found = search_by_id(*root, id);
            if (found) {
                printf("ID: %d, Nom: %s, Race: %s\n", found->id, found->nom, found->race);
            } else {
                printf("Aucun animal trouvé avec ID=%d.\n", id);
            }
        } else {
            printf("Commande invalide pour l'ID. Utilisez : SELECT id <id>\n");
        }
    } else if (strcmp(action, "QUIT") == 0) {
        printf("Fermeture du programme...\n");
        exit(0);
    } else {
        printf("Commande inconnue. Utilisez : INSERT, SELECT, QUIT.\n");
    }
}

// Fonction principale
int main() {
    struct Node* refuge = NULL;  // L'arbre binaire (racine)

    char command[100];
    while (1) {
        printf("\nEntrez une commande (INSERT, SELECT, QUIT) : ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;  // Supprimer le saut de ligne

        execute_command(&refuge, command);

        printf("\nAffichage de l'arbre (in-order):\n");
        inorder_traversal(refuge);  // Afficher l'arbre après chaque commande
    }

    return 0;
}
