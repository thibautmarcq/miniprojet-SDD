/* MONO 3
Maëlle LIU 21204734
Thibaut MARCQ 21202966 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "biblioH.h"
#include "entreeSortieH.h"

BiblioH* charger_n_entreesH(char* nomfic, int n){
    /* Lis les n premières entrees du fichier nomfic et retourne la BiblioH associée */
    FILE* f = fopen(nomfic, "r");
    if(f==NULL){ // Vérifie si le fichier est bien ouvert
        printf("Erreur d'ouverture : %s\n", nomfic);
        exit(1);
    }
    int i=0;
    BiblioH *b = creer_biblioH(n);
    char buffer[512]; // Taille max 64char par ligne
    while(i<n){
        int num;
        char titre[256];
        char auteur[256];
        fgets(buffer, 512, f); // Parcours les lignes du fichier
        sscanf(buffer, "%d %s %s", &num, titre, auteur); // Découpe les données de la ligne lue : les met dans les buffer correspondant
        inserer(b, num, titre, auteur); // Ajoute les infos dans un livre en tête de la biblio
        i++;
    }
    fclose(f); // Ferme le fichier ouvert
    return b;
}

void enregistrer_biblioH(BiblioH *b, char* nomfic){
    /* Enregistre la biblio b dans le fichier nomfic */
    FILE* f = fopen(nomfic, "w");
    if(f==NULL){ // Vérifie si le fichier est bien ouvert
        printf("Erreur d'ouverture : %s\n", nomfic);
        exit(1);
    }
    LivreH** tab = b->T; // Table en elle-meme
    for(int i=0; i < b->m; i++){ // Parcours de la table
        if (tab[i]!=NULL){ // Vérifie que la case n'est pas vide

            LivreH* lv = tab[i]; // Copie pour ne pas modifier la LC de la case
            while (lv){ // Parcours la LC dans la case
                fprintf(f, "%d %s %s\n", lv->num, lv->titre, lv->auteur);
                lv = lv->suivant;
            }
        }
    }
    fclose(f); // Ferme le fichier ouvert
    printf("Bibliothèque enregistrée sous : %s\n", nomfic);
}