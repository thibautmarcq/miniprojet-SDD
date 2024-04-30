/* MONO 3
Maëlle LIU 21204734
Thibaut MARCQ 21202966 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "biblioLC.h"

Livre* creer_livre(int num, char* titre, char* auteur){
    /* Crée un livre à partir des ses infos (num/titre/auteur) */
    Livre* l = (Livre*)malloc(sizeof(Livre));
    l->num = num;
    l->titre = strdup(titre); // Fait une copie du titre
    l->auteur = strdup(auteur); // Fait une copie de l'auteur
    l->suiv=NULL;
    return l;
}


void liberer_livre(Livre *l){
    /* Libère un livre */
    free(l->titre);
    free(l->auteur);
    free(l);
}


Biblio * creer_biblio(){
    /* Crée une biblio */
    Biblio* b=(Biblio*)malloc(sizeof(Biblio));
    b->L = NULL;
    return b;
}


void liberer_biblio(Biblio* b) {
    /* Libère une biblio */
    Livre* courant = b->L; // Pointeur vers les livres de la biblio
    Livre* next;
    while (courant) { // Parcours la bibliothèque
        next = courant->suiv;
        liberer_livre(courant); // Libère chaque livre dans la biblio
        courant = next;
    }
    free(b); //Libère le pointeur de la biblio
}


void inserer_en_tete(Biblio* b, int num, char* titre, char* auteur){
    /* Insère un livre en tête d'une biblio à partir de ses infos (num/titre/auteur) */
    Livre* l = creer_livre(num, titre, auteur); // Crée un nouveau livre
    l->suiv = b->L; // Le suivant de ce livre est l'ancienne liste de livres
    b->L = l; // Le premier livre de la biblio est le livre crée
}


void afficher_livre(Livre* l){
    /* Produit l'affichage des informations d'un livre */
    if(l!=NULL)
        printf("%d %s %s\n", l->num, l->titre, l->auteur);
}


void afficher_biblio(Biblio* b){
    /* Produit l'affichage des livres d'une biblio */
    if(b!=NULL){
        Livre* courant = b->L;
        while(courant){ // Parcours des livres de la biblio
            afficher_livre(courant);
            courant = courant->suiv;
        }
    }
}


Livre* chercher_num(Biblio* b, int num){
    /* Cherche un livre dans une biblio à partir de son numéro */
    Livre* courant = b->L;
    while(courant){ // Parcours des livres de la biblio
        if (courant->num==num){ // Regarde si le num du livre est le num attendu
            return courant;
        }
        courant=courant->suiv; // Avance dans les livres
    }
    return NULL; // Livre non trouvé
}


Livre* chercher_titre(Biblio* b, char* titre){
    /* Cherche un livre dans une biblio à partir de son titre */
    Livre* courant=b->L;
    while(courant){ // Parcours des livres de la biblio
        if(strcmp(courant->titre,titre)==0){ // Compare les titres et renvoie 0 si =
            return courant;
        }
        courant=courant->suiv; // Avance dans les livres
    }
    return NULL; // Livre non trouvé
}

Biblio* chercher_auteur(Biblio* b, char* auteur){
    /* Cherche tous les livres d'un auteur, renvoie une biblio de ses livres */
    Livre* courant = b->L;
    Biblio* res = creer_biblio();
    while(courant){ // Parcours des livres de la biblio
        if (strcmp(courant->auteur, auteur) == 0){ // Compare les auteurs et renvoie 0 si =
            inserer_en_tete(res, courant->num, courant->titre, courant->auteur);
        }
        courant=courant->suiv; // Avance dans les livres
    }
    return res; // Retourne la nouvelle biblio
}

int supprimer_livre(Biblio* b, int num, char* titre, char* auteur){
    /* Supprime un livre d'une biblio à partir de son num/titre/auteur retourne 0 si suppression faite 1 sinon*/
    Livre* courant = b->L;
    Livre* prec = NULL; 
    while(courant){ // Parcours les livres de la biblio
        if(courant->num==num && strcmp(courant->titre, titre) == 0 && strcmp(courant->auteur, auteur) == 0){ // Compare les infos des livres - true si toutes les infos correspondent + livre ne vaut pas NULL
            if (prec==NULL){ // Vérifie si l'ouvrage à supprimer est en tete de liste
                b->L=courant->suiv;
                liberer_livre(courant);
                return 0;
            } else {
                prec->suiv=courant->suiv;
                liberer_livre(courant);
                return 0;
            }
        }
        prec=courant;
        courant=courant->suiv;
    }
    return 1;
}

void fusion_biblio(Biblio** b1, Biblio* b2){
    /* Fusionne deux biblios b1 et b2 dans b1 et supprime b2 (ajout de b2 dans b1)*/
    if (*b1 == NULL){ // Si b1 n'est pas alloué
        *b1 = creer_biblio();
    }
    Biblio* Bdeux = b2; // Pointeur pour ne pas modifier b2
    while(Bdeux->L){ // Parcours des livres de b2
        inserer_en_tete(*b1, Bdeux->L->num, Bdeux->L->titre, Bdeux->L->auteur); // Insertion des livres de b2 dans b1
        Bdeux->L = Bdeux->L->suiv; // Parcours des livres de b2
    }
    liberer_biblio(b2);
}

Biblio* plusieurs_livres(Biblio* b){
    /* Renvoie la bibliothèque des livres identiques (titre et auteur)*/
    Livre* l1=b->L; // Pointeur vers les livres de b
    Biblio* res=creer_biblio(); // Nouvelle bibliothèque où stocker les livres en plusieurs exemplaires

    while (l1){
        Livre* l2 = l1->suiv; // l2 commence un rang après l1, pour ne pas avoir les livres en commun à chaque fois
        while(l2){
            if (strcmp(l1->titre, l2->titre)==0 && strcmp(l1->auteur, l2->auteur)==0){ // Compare les livres des deux listes parcourues : true si les deux livres ont le meme titre et auteur
                inserer_en_tete(res, l1->num, l1->titre, l1->auteur);
                inserer_en_tete(res, l2->num, l2->titre, l2->auteur);
            }
            l2=l2->suiv; // Avance dans les livres de l2
        }
        l1=l1->suiv; // Avance dans les livres de l1
    }
    return res; // Retourne la biblio des livres en commun
}