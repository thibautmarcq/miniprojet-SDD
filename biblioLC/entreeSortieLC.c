/* MONO 3
Maëlle LIU 21204734
Thibaut MARCQ 21202966 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "biblioLC.h"
#include "entreeSortieLC.h"


Biblio* charger_n_entrees(char* nomfic, int n){
    /* Lis les n premières entrees du fichier nomfic et retourne la BiblioH associée */
    FILE* f = fopen(nomfic, "r");
    if(f==NULL){ // Vérifie si le fichier est bien ouvert
        printf("Erreur d'ouverture : %s\n", nomfic);
        exit(1);
    }
    Biblio *b = creer_biblio();
    char buffer[512]; // Taille max 64char par ligne
    int i=0;
    while(i<n){
        int num;
        char titre[256];
        char auteur[256];
        fgets(buffer, 512, f); // Parcours les lignes du fichier
        sscanf(buffer, "%d %s %s", &num, titre, auteur); // Découpe les données de la ligne lue : les met dans les buffer correspondant
        inserer_en_tete(b, num, titre, auteur); // Ajoute les infos dans un livre en tête de la biblio
        i++;
    }
    fclose(f); // Ferme le fichier ouvert
    return b; 
}

void enregistrer_biblio(Biblio *b, char* nomfic){
    /* Enregistre la biblio b dans le fichier nomfic */
    FILE* f = fopen(nomfic, "w");
    if(f==NULL){ // Vérifie si le fichier est bien ouvert
        printf("Erreur d'ouverture : %s\n", nomfic);
        exit(1);
    }
    Livre* lv = b->L; // Pointeur vers la liste des livres
    while(lv){ // Parcours tous les livres
        fprintf(f, "%d %s %s\n", lv->num, lv->titre, lv->auteur);
        lv = lv->suiv;
    }
    fclose(f); // Ferme le fichier ouvert
    printf("Bibliothèque enregistrée sous : %s\n", nomfic);
}