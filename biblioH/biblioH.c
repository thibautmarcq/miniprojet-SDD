/* MONO 3
Maëlle LIU 21204734
Thibaut MARCQ 21202966 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "biblioH.h"

int fonctionClef(char* auteur){
	/* Renvoie le hachage de l'auteur (additionne toutes ses lettres)*/
	int res=0;
	int i = 0;
	while(auteur[i]!='\0'){ // Parcours toutes les lettres l'auteur
		res+=auteur[i]; // Ajoute la valeur (entier) de la lettre à res
		i++;
	}
	return res;
}

LivreH* creer_livreH(int num, char* titre, char* auteur){
	/* Crée un livre à partir des ses infos (num/titre/auteur) + cree sa clef*/
	LivreH* l = (LivreH*)malloc(sizeof(LivreH)); // Alloue la mémoire pour le livre
	l->num = num;
	l->titre = strdup(titre); // Fait une copie du titre
	l->auteur = strdup(auteur); // Fait une copie de l'auteur
	l->clef = fonctionClef(auteur); // Crée la clef à partir de l'auteur
	l->suivant = NULL;
	return l;
}

void liberer_livreH(LivreH* l){
	/* Libère un livre */
	free(l->titre);
	free(l->auteur);
	free(l);
}

BiblioH* creer_biblioH(int m){
	/* Crée une biblio de taille m */
	BiblioH* b=(BiblioH*)malloc(sizeof(BiblioH)); // Alloue la mémoire nécessaire à la biblio
	b->nE = 0; // Initialise son nb de livres actuels à 0
	b->m = m; // Initialise sa taille max à m
	b->T = (LivreH**)malloc(m*sizeof(LivreH*));
	for(int i=0; i<m;i++){ // Initialise toutes les cases du tableau a NULL
		b->T[i] = NULL;
	}
	return b;
}

void liberer_biblioH(BiblioH* b){
	/* Libère entièrement une biblio b*/
	LivreH** tab = b->T;
	LivreH* tmp;
	for(int i=0; i<b->m; i++){ // Parcours les cases du tableau
		LivreH * l= tab[i];
		if(l!=NULL){ // Vérifie si la case est vide
			while(l){
				tmp=l->suivant;
				liberer_livreH(l); // Libère chaque livre du tableau
				l=tmp;
			}
		}
	}
	free(tab); // Libère le pointeur du tableau
	free(b); // Libère le pointeur de la biblio
}

int fonctionHachage(int cle, int m){
	/* Transforme la clé en valeur utilisable par la table de H, de taille m*/
	double A = ((sqrt(5)-1)/2); // Nombre d'or
	return (int)(m*(cle*A-(int)(cle*A))); // Formule du cours/de l'enoncé
}

void inserer(BiblioH* b, int num, char* titre, char* auteur){ // 1
	/* Insère un livre dans la biblio b à partir de ses infos */
	int cleH = fonctionClef(auteur);
	int idH = fonctionHachage(cleH, b->m);

	LivreH* LC_case = b->T[idH];
	LivreH* new = NULL;
	b->nE+=1; // Augmente le nb d'elements dans le tab
	if (LC_case==NULL){ // La case du tab est vide
		b->T[idH] = creer_livreH(num, titre, auteur); 
	} else {  // La case du tab n'est pas vide : insertion en tete
		new = creer_livreH(num, titre, auteur);
		new->suivant=LC_case;
		b->T[idH] = new;
	}
}

void afficher_livreH(LivreH* l){
	/* Produit l'affichage des informations d'un livre */
	if(l!= NULL)
		printf("%d %s %s\n",l->num, l->titre, l->auteur);
}

void afficher_biblioH(BiblioH* b){ 
	/* Affiche une bibliothèque b */
	if(b!=NULL){ // Vérifie si la biblio n'est pas vide
		LivreH** tab= b->T;
		LivreH* lv;
		for (int i=0; i<b->m; i++){
			lv = tab[i]; // Liste des livres en cours (case du tableau)
			while(lv){ // Parcours les livres de la case du tableau
				afficher_livreH(lv);
				lv=lv->suivant;
			}
		}
	}
}

LivreH* chercher_numeroH(BiblioH* b, int num){
	/* Cherche un livre dans la biblio b à partir de son numéro */
	LivreH** tab = b->T;
	for (int i=0; i<b->m; i++){ // Parcours le tableau
		LivreH* lv = tab[i];
		while(lv){ // Parcours les livres de la case du tableau
			if (lv->num==num){ // Vérifie si le livre en cours a le numéro voulu
				return lv; 
			}
			lv=lv->suivant;
		}
	}
	return NULL;
}

LivreH* chercher_titreH(BiblioH* b, char* titre){
	/* Cherche un livre dans la biblio b à partir de son titre */
	LivreH** tab = b->T;
	for (int i=0; i<b->m; i++){ // Parcours le tableau
		LivreH* lv = tab[i];
		while(lv){ // Parcours les livres de la case du tableau
			if (strcmp(lv->titre, titre)==0){ // Compare les titres renvoie 0 si =
				return lv; 
			}
			lv=lv->suivant;
		}
	}
	return NULL;
}

BiblioH* chercher_auteurH(BiblioH* b, char* auteur){
	/* Cherche les livres d'un meme auteur dans la biblio b - Renvoie une biblio de ses livres */
	int cleH = fonctionClef(auteur); 
	int idH = fonctionHachage(cleH, b->m); 

	BiblioH* res = creer_biblioH(1); // Crée une biblio de taille 1 => 1 seul auteur dedans
	LivreH* LCauteur = b->T[idH]; // Endroit où devrait être l'auteur
	while (LCauteur){ // Parcours les livres (case du tableau de clé auteur)
		if(strcmp(LCauteur->auteur, auteur)==0){ // Compare les auteurs renvoie 0 si =
			inserer(res, LCauteur->num, LCauteur->titre, LCauteur->auteur); // Insère le livre correspondant dans la biblio de retour
		}
		LCauteur=LCauteur->suivant;
	}
	return res; 
}

int supprimer_livreH(BiblioH* b, int num, char* titre, char* auteur){
	/* Supprime un livre de la biblio b à partir de ses infos retourne 0 si la suppression est faite sinon 1*/
	int cleH = fonctionClef(auteur); 
	int idH = fonctionHachage(cleH, b->m); 

	LivreH* courant = b->T[idH]; // Endroit où devrait être l'auteur
	LivreH* prec = NULL; // Livre qui sera le précedent du courant
	while(courant){
		if (courant->num==num && strcmp(courant->titre, titre)==0 && strcmp(courant->auteur, auteur)==0){ 
			if (prec==NULL){ // Regarde si l'élément à supprimer est le premier livre de T[idH]
				b->T[idH]=courant->suivant;
				liberer_livreH(courant);
				return 0;
			} else {
				prec->suivant=courant->suivant;
				liberer_livreH(courant);
				return 0;
			}
		}
		prec=courant;
		courant=courant->suivant;
	}
	return 1;
}

void fusion_biblioH(BiblioH** b1, BiblioH* b2){
	/* Fusionne deux biblios b1 et b2 dans b1 et supprime b2 (ajout de b2 dans b1)*/
    if (*b1 == NULL){ 
        *b1 = creer_biblioH(b2->m);
    }

	LivreH** tab2 = b2->T;
	for (int i=0; i< b2->m; i++){ // Parcours tous les livres de b2 et les insèrent dans b1
		LivreH* lv = tab2[i];
		while(lv){
			inserer(*b1, lv->num, lv->titre, lv->auteur);
			lv=lv->suivant;
		}
	}
}

BiblioH* plusieurs_livresH(BiblioH* b) {
    /* Renvoie la bibliothèque des livres identiques (titre et auteur)*/
    BiblioH* res = creer_biblioH(1); // Le tableau de sortie est de taille 1

    for (int i=0; i<b->m; i++) { // Parcours le tableau
        LivreH* l1 = b->T[i];

        while (l1) {
            LivreH* l2 = l1->suivant; // l2 commence un rang après l1, pour ne pas avoir les livres en commun à chaque fois
            while (l2) {
                if (strcmp(l1->titre, l2->titre)==0 && strcmp(l1->auteur, l2->auteur)==0) { // Compare les livres des deux listes parcourues : true si les deux livres ont le meme titre et auteur
                    inserer(res, l1->num, l1->titre, l1->auteur);
                    inserer(res, l2->num, l2->titre, l2->auteur);
                }
                l2 = l2->suivant;
            }
            l1 = l1->suivant;
        }
    }
    return res; // Retourne la biblio des livres en commun
}
