/* MONO 3
Maëlle LIU 21204734
Thibaut MARCQ 21202966 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "biblioLC/biblioLC.h"
#include "biblioLC/entreeSortieLC.h"
#include "biblioH/biblioH.h"
#include "biblioH/entreeSortieH.h"


void menu(){
    printf("\nInserer un numéro :\n");
    printf("0-Sortie du programme, 1-Affichage, 2-Inserer ouvrage, 3-Suppression ouvrage, 4-Rechercher ouvrage par numero,\n5-Rechercher ouvrage par titre, 6-Rechercher ouvrages par auteur, 7-Recherche ouvrages avec plusieurs exemplaire,\n8-Enregistrement de la bibliothèque dans un fichier\n");
}

int main(int argc, char** argv){

    if(argc!=3){
        printf("Usage : %s <fichier biblio> <nb livres>\n", argv[0]);
        return 1;
    }
    
    char type[3]; // Prend une entrée de taille 3 : le numéro, \0 et \n
    char rep[3];
    char buffer[256]; // Taille max 64 caractères
    int num;
    char titre[256];
    char auteur[256];
    char fichier[256];

    printf("1-Liste chainée, 2-Table de Hachage\n");
    fgets(type, sizeof(type), stdin);

    if(atoi(type)==1){ // Liste chainée
        Biblio* bLC = charger_n_entrees(argv[1], atoi(argv[2]));
        
        do{
            menu();
            fgets(rep, sizeof(rep), stdin);

            switch (atoi(rep)){

            case 1: // Affichage de biblio
                printf("Affichage :\n");
                afficher_biblio(bLC);
                break;  

            case 2: // Inserer un livre dans la biblio
                printf("Veuillez ecrire le numero , le titre et l'auteur de l'ouvrage a ajouter \n" );
                fgets(buffer, sizeof(buffer), stdin);
                if(sscanf(buffer, "%d %s %s", &num, titre, auteur)==3){ 
                    inserer_en_tete(bLC, num, titre, auteur);
                    printf("Ajout fait\n");
                }else{
                    printf("Erreur format\n");
                }
                break;

            case 3: // Supprimer un livre dans la biblio
                printf("Veuillez ecrire le numero , le titre et l'auteur de l'ouvrage a supprimer \n" );
                fgets(buffer, sizeof(buffer), stdin);
                if(sscanf(buffer,"%d %s %s" ,&num, titre, auteur)==3){
                    int result = supprimer_livre(bLC, num, titre, auteur);
                    if (result == 0)
                        printf("Suppression faite\n");
                    else
                        printf("Impossible de supprimer le livre : livre introuvable dans la bibliothèque\n");
                }else{
                    printf("Erreur format\n");
                }
                break;

            case 4: // Recherche d'un livre par son numéro
                printf("Veuillez ecrire le numero de l'ouvrage\n" );
                fgets(buffer, sizeof(buffer), stdin);
                if(sscanf(buffer,"%d" ,&num) == 1){
                    Livre* l1 = chercher_num(bLC, num);
                    if (l1 == NULL)
                        printf("Le numéro n'est pas dans la bibliothèque\n");
                    else
                        afficher_livre(l1);
                }else{
                    printf("Erreur format\n");
                }
                break;
            
            case 5: // Recherche des livres par son titre
                printf("Veuillez ecrire le titre de l'ouvrage\n" );
                fgets(buffer, sizeof(buffer), stdin);
                if(sscanf(buffer,"%s" ,titre)==1){
                    Livre *l2 = chercher_titre(bLC, titre);
                    if (l2 ==NULL)
                        printf("Le titre n'est pas dans la bibliothèque\n");
                    else
                        afficher_livre(l2);
                }else{
                    printf("Erreur format\n");
                }
                break;

            case 6: // Recherche d'un livre par son auteur
                printf("Veuillez ecrire l'auteur des ouvrages que vous voulez\n" );
                fgets(buffer, sizeof(buffer), stdin);
                if(sscanf(buffer,"%s" ,auteur)==1){
                    Biblio* b = chercher_auteur(bLC, auteur);
                    if (b->L==NULL)
                        printf("L'auteur n'a pas de livres dans la biblio\n");
                    else
                        afficher_biblio(b);
                    liberer_biblio(b);
                }else{
                    printf("Erreur format\n");
                }
                break;

            case 7:  // Recherche de plusieurs livres identiques (titre et auteur) dans la biblio
                ;
                Biblio* plusieurs = plusieurs_livres(bLC);
                if (plusieurs->L==NULL){
                    printf("Aucun livre n'est présent en plusieurs exemplaires\n");
                } else {
                    afficher_biblio(plusieurs);
                }    
                liberer_biblio(plusieurs);
                break;

            case 8 : // Enregistrer la biblio dans un fichier
                printf("Veuillez entrer le nom du fichier où enregistrer la biblio\n");
                fgets(buffer, sizeof(buffer), stdin);
                if(sscanf(buffer,"%s", fichier) == 1){
                    enregistrer_biblio(bLC, fichier);
                }
            }

        }while(atoi(rep) !=0);
        printf("Merci, et au revoir.\n");
        liberer_biblio(bLC);
        return 0;

    }

    if(atoi(type)==2){ // Table de Hachage
        BiblioH* bH = charger_n_entreesH(argv[1], atoi(argv[2]));
        
        do{
            menu();
            fgets(rep, sizeof(rep), stdin);

            switch (atoi(rep)){
                
            case 1: // Affichage de la biblio
                printf("Affichage :\n");
                afficher_biblioH(bH);
                break;  

            case 2: // Inserer un livre dans la biblio
                printf("Veuillez ecrire le numero , le titre et l'auteur de l'ouvrage a ajouter \n" );
                fgets(buffer, sizeof(buffer), stdin);
                if(sscanf(buffer, "%d %s %s", &num, titre, auteur)==3){
                    inserer(bH, num, titre, auteur);
                    printf("Ajout fait\n");
                }else{
                    printf("Erreur format\n");
                }
                break;

            case 3: // Supprimer un livre da la biblio
                printf("Veuillez ecrire le numero , le titre et l'auteur de l'ouvrage a supprimer \n" );
                fgets(buffer, sizeof(buffer), stdin);
                if(sscanf(buffer,"%d %s %s" ,&num, titre, auteur)==3){
                    int result = supprimer_livreH(bH, num, titre, auteur);
                    if (result == 0)
                        printf("Suppression faite\n");
                    else
                        printf("Impossible de supprimer le livre : livre introuvable dans la bibliothèque\n");
                }else{
                    printf("Erreur format\n");
                }
                break;

            case 4: // Recherche d'un livre par son numéro
                printf("Veuillez ecrire le numero de l'ouvrage\n" );
                fgets(buffer, sizeof(buffer), stdin);
                if(sscanf(buffer,"%d" ,&num) == 1){
                    LivreH* l1 = chercher_numeroH(bH, num);
                    if(l1 == NULL)
                        printf("Le numéro n'est pas dans la bibliothèque\n");
                    else
                        afficher_livreH(l1);
                }else{
                    printf("Erreur format\n");
                }
                break;
            
            case 5: // Recherche d'un livre par son titre
                printf("Veuillez ecrire le titre de l'ouvrage\n" );
                fgets(buffer, sizeof(buffer), stdin);
                if(sscanf(buffer,"%s" ,titre)==1){
                    LivreH *l2 = chercher_titreH(bH, titre);
                    if(l2 == NULL)
                        printf("Le titre n'est pas dans la bibliothèque\n");
                    else
                        afficher_livreH(l2);
                }else{
                    printf("Erreur format\n");
                }
                break;

            case 6: // Recherche des livres par son auteur
                printf("Veuillez ecrire l'auteur des ouvrages que vous voulez\n" );
                fgets(buffer, sizeof(buffer), stdin);
                if(sscanf(buffer,"%s" ,auteur)==1){
                    BiblioH* b = chercher_auteurH(bH, auteur);
                    if (b->T==NULL)
		                printf("L'auteur n'a pas de livre dans la biblio\n");
	                else
                        afficher_biblioH(b);
                    liberer_biblioH(b);
                }else{
                    printf("Erreur format\n");
                }
                break;

            case 7: // Recherche de plusieurs livres identiques(titre et auteur) dans la biblio 
                ;
                BiblioH* plusieurs = plusieurs_livresH(bH);
                if (plusieurs->T[0]==NULL){ // étant donné que le tableau renvoyé par plusieurs_livresH est de taille 1
                    printf("Aucun livre n'est présent en plusieurs exemplaires\n");
                } else {
                    afficher_biblioH(plusieurs);
                }
                liberer_biblioH(plusieurs);
                break;

            case 8 : // Enregistrer la biblio dans un fichier
                printf("Veuillez entrer le nom du fichier où enregistrer la biblio\n");
                fgets(buffer, sizeof(buffer), stdin);
                if(sscanf(buffer,"%s", fichier) == 1){
                    enregistrer_biblioH(bH, fichier);
                }
            }

        }while(atoi(rep) !=0);
        printf("Merci, et au revoir.\n");
        liberer_biblioH(bH);
        return 0;
    }
    return 0;
}
