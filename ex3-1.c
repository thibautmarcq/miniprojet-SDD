/* MONO 3
Maëlle LIU 21204734
Thibaut MARCQ 21202966 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "biblioLC/biblioLC.h"
#include "biblioLC/entreeSortieLC.h"
#include "biblioH/biblioH.h"
#include "biblioH/entreeSortieH.h"

int main(){
    Biblio* bLC = charger_n_entrees("GdeBiblio.txt", 40000); 
    BiblioH* bH = charger_n_entreesH("GdeBiblio.txt", 40000);
    clock_t temps_initLC;
    clock_t temps_finLC;
    double temps_totLC;
    clock_t temps_initH;
    clock_t temps_finH;
    double temps_totH;

    //Recherche par NUMERO, cas livre présent
    temps_initLC = clock(); //Nombre de "ticks" consommés par le programme jusqu’ici
    chercher_num(bLC, 1200); 
    chercher_num(bLC, 2900); 
    chercher_num(bLC, 990);
    chercher_num(bLC, 150);
    chercher_num(bLC, 190);
    chercher_num(bLC, 4000);
    temps_finLC = clock (); //Nombre de "ticks" consommés par le programme jusqu’ici
    //On convertit les "ticks" consommés par fct en secondes
    temps_totLC = ((double)(temps_finLC - temps_initLC))/CLOCKS_PER_SEC;
    printf("Liste Chainee, Recherche par num (cas livre present): %fs\n",temps_totLC);

    temps_initH = clock(); 
    chercher_numeroH(bH, 1200);
    chercher_numeroH(bH, 2900);
    chercher_numeroH(bH, 990);
    chercher_numeroH(bH, 150);
    chercher_numeroH(bH, 190);
    chercher_numeroH(bH, 4000);
    temps_finH = clock ();
    temps_totH = ((double)(temps_finH - temps_initH))/CLOCKS_PER_SEC;
    printf("Table Hachage, Recherche par num (cas livre present): %fs\n",temps_totH);

    //Recherche par NUMERO, cas livre absent
    temps_initLC = clock(); 
    chercher_num(bLC, 120000);
    chercher_num(bLC, 110500);
    chercher_num(bLC, 160000);
    chercher_num(bLC, 200000);
    chercher_num(bLC, 150000);
    temps_finLC = clock (); 
    temps_totLC = ((double)(temps_finLC - temps_initLC))/CLOCKS_PER_SEC;
    printf("Liste Chainee, Recherche par num (cas livre absent): %fs\n",temps_totLC);

    temps_initH = clock(); 
    chercher_numeroH(bH, 120000);
    chercher_numeroH(bH, 115000);
    chercher_numeroH(bH, 160000);
    chercher_numeroH(bH, 200000);
    chercher_numeroH(bH, 150000);
    temps_finH = clock ();
    temps_totH = ((double)(temps_finH - temps_initH))/CLOCKS_PER_SEC;
    printf("Table Hachage, Recherche par num (cas livre absent): %fs\n\n",temps_totH);


    //Recherche par TITRE, cas livre présent
    temps_initLC = clock(); 
    chercher_titre(bLC, "JWFMPQWFBSZFNKZL");
    chercher_titre(bLC, "SADEUGUUMOQCDRUBE");
    chercher_titre(bLC, "DSYCQHKLEEWH");
    chercher_titre(bLC, "RFXJU");
    chercher_titre(bLC, "WBUGFEOWSGXBKDQ");
    chercher_titre(bLC, "EPLHRZR");
    temps_finLC = clock (); 
    temps_totLC = ((double)(temps_finLC - temps_initLC))/CLOCKS_PER_SEC;
    printf("Liste Chainee, Recherche par titre (cas livre present): %fs\n",temps_totLC);

    temps_initH = clock(); 
    chercher_titreH(bH, "JWFMPQWFBSZFNKZL");
    chercher_titreH(bH, "SADEUGUUMOQCDRUBE");
    chercher_titreH(bH, "DSYCQHKLEEWH");
    chercher_titreH(bH, "RFXJU");
    chercher_titreH(bH, "WBUGFEOWSGXBKDQ");
    chercher_titreH(bH, "EPLHRZR");
    temps_finH = clock ();
    temps_totH = ((double)(temps_finH - temps_initH))/CLOCKS_PER_SEC;
    printf("Table Hachage, Recherche par titre (cas livre present): %fs\n",temps_totH);

    //Recherche par TITRE, cas livre absent
    temps_initLC = clock(); 
    chercher_titre(bLC, "LEMONDESTLANUIT");
    chercher_titre(bLC, "LEPETITPRINCE");
    chercher_titre(bLC, "ILETAITUNEFOISLAVIE");
    chercher_titre(bLC, "JENAIPLUSDIDEE");
    chercher_titre(bLC, "BONNELECTURE");
    temps_finLC = clock (); 
    temps_totLC = ((double)(temps_finLC - temps_initLC))/CLOCKS_PER_SEC;
    printf("Liste Chainee, Recherche par titre (cas livre absent): %fs\n",temps_totLC);

    temps_initH = clock(); 
    chercher_titreH(bH, "LEMONDEETLANUIT");
    chercher_titreH(bH, "LEPETITPRINCE");
    chercher_titreH(bH, "ILETAITUNEFOISLAVIE");
    chercher_titreH(bH, "JENAIPLUSDIDEE");
    chercher_titreH(bH, "BONNELECTURE");
    temps_finH = clock ();
    temps_totH = ((double)(temps_finH - temps_initH))/CLOCKS_PER_SEC;
    printf("Table Hachage, Recherche par titre (cas livre absent): %fs\n\n",temps_totH);


    //Recherche par AUTEUR, cas livre présent
    temps_initLC = clock(); 
    chercher_auteur(bLC, "jddn");
    chercher_auteur(bLC, "wsiqyoygyxy");
    chercher_auteur(bLC, "hapj");
    chercher_auteur(bLC, "suyoypayulye");
    chercher_auteur(bLC, "ndq");
    chercher_auteur(bLC, "hkchzdfli");
    temps_finLC = clock (); 
    temps_totLC = ((double)(temps_finLC - temps_initLC))/CLOCKS_PER_SEC;
    printf("Liste Chainee, Recherche par auteur (cas livre present): %fs\n",temps_totLC);

    temps_initH = clock(); 
    chercher_auteurH(bH, "jddn");
    chercher_auteurH(bH, "wsiqyoygyxy");
    chercher_auteurH(bH, "hapj");
    chercher_auteurH(bH, "suyoypayulye");
    chercher_auteurH(bH, "ndq");
    chercher_auteurH(bH, "hkchzdfli");
    temps_finH = clock ();
    temps_totH = ((double)(temps_finH - temps_initH))/CLOCKS_PER_SEC;
    printf("Table Hachage, Recherche par auteur (cas livre present): %fs\n",temps_totH);


    //Recherche par AUTEUR, cas livre absent
    temps_initLC = clock(); 
    chercher_auteur(bLC, "vacheret");
    chercher_auteur(bLC, "montesquieu");
    chercher_auteur(bLC, "victorhugo");
    chercher_auteur(bLC, "zola");
    chercher_auteur(bLC, "mozart");
    chercher_auteur(bLC, "sxrdctfevybhfnoiezjfzoubyerei");
    temps_finLC = clock (); 
    temps_totLC = ((double)(temps_finLC - temps_initLC))/CLOCKS_PER_SEC;
    printf("Liste Chainee, Recherche par auteur (cas livre absent): %fs\n",temps_totLC);

    temps_initH = clock(); 
    chercher_auteurH(bH, "vacheret");
    chercher_auteurH(bH, "montesquieu");
    chercher_auteurH(bH, "victorhugo");
    chercher_auteurH(bH, "zola");
    chercher_auteurH(bH, "mozart");
    chercher_auteurH(bH, "sxrdctfevybhfnoiezjfzoubyerei");
    temps_finH = clock ();
    temps_totH = ((double)(temps_finH - temps_initH))/CLOCKS_PER_SEC;
    printf("Table Hachage, Recherche par auteur (cas livre absent): %fs\n",temps_totH);


    liberer_biblio(bLC);
    liberer_biblioH(bH);

}