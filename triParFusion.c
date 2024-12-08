#include <stdio.h>
#include <stdlib.h>

typedef struct Element Element;
struct Element {
    int valeur;
    Element *suivant;
};

// Fonction pour trouver le milieu de la liste
Element* getMillieu(Element *tete) {
    if (tete == NULL) return NULL;

    Element *fast = tete->suivant;
    Element *slow = tete;

    while (fast != NULL && fast->suivant!= NULL) {
        slow = slow->suivant;
        fast = fast->suivant->suivant;
    }

    return slow;
}

// Fonction pour fusionner deux listes triées
Element* merge(Element* gauche, Element* droit) {
    if (gauche == NULL) return droit;
    if (droit == NULL) return gauche;

    Element *result = NULL;

    if (gauche->valeur <= droit->valeur) {
        result = gauche;
        result->suivant = merge(gauche->suivant, droit);
    } else {
        result = droit;
        result->suivant = merge(gauche, droit->suivant);
    }

    return result;
}

// Fonction pour trier une liste chaînée par tri fusion
void mergeSort(Element **tete) {
    if (*tete == NULL || (*tete)->suivant == NULL) return;

    // Trouver le milieu
    Element *millieu = getMillieu(*tete);
    Element *droit = millieu->suivant;
    millieu->suivant = NULL;

    // Tri récursif sur les deux moitiés
    mergeSort(tete);
    mergeSort(&droit);

    // Fusionner les deux listes triées
    *tete = merge(*tete, droit);
}

// Fonction pour ajouter un élément à la fin de la liste
void append(Element **tete, int valeur) {
    Element *element = malloc(sizeof(Element));
    element->valeur = valeur;
    element->suivant = NULL;

    if (*tete == NULL) {
        *tete = element;
        return;
    } else {
        Element *tmp = *tete;
        while (tmp->suivant != NULL) {
            tmp = tmp->suivant;
        }
        tmp->suivant = element;
    }
}

// Fonction pour afficher une liste chaînée
void afficher(Element *element) {
    while (element != NULL) {
        printf("%d -> ", element->valeur);
        element = element->suivant;
    }
    printf("NULL\n");
}

// Fonction principale
int main() {
    Element *liste = NULL;

    // Ajouter des éléments à la liste
    append(&liste, 10);
    append(&liste, 20);
    append(&liste, 30);
    append(&liste, -5);
    append(&liste, 5);
    append(&liste, 15);
    append(&liste, 25);
    append(&liste, 40);

    // Afficher la liste avant le tri
    printf("Affichage de la liste chaînée avant le tri par fusion :\n\t");
    afficher(liste);

    // Trier la liste avec mergeSort
    mergeSort(&liste);

    // Afficher la liste après le tri
    printf("Affichage de la liste chaînée après le tri par fusion :\n\t");
    afficher(liste);

    return 0;
}
