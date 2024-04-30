/* MONO 3
Maëlle LIU 21204734
Thibaut MARCQ 21202966 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "biblioLC/biblioLC.h"
#include "biblioLC/entreeSortieLC.h"
#include "biblioH/biblioH.h"
#include "biblioH/entreeSortieH.h"


int main(){
    clock_t temps_initLC;
    clock_t temps_finLC;
    double temps_totLC;
    clock_t temps_initH;
    clock_t temps_finH;
    double temps_totH;
    
    for(int i = 1000; i<50001; i=i+1000){
        Biblio* bLC = charger_n_entrees("GdeBiblio.txt",i);
        BiblioH* bH = charger_n_entreesH("GdeBiblio.txt",i);

        temps_initLC = clock(); 
        Biblio* bLC2 = plusieurs_livres(bLC);
        temps_finLC = clock ();
        temps_totLC = ((double)(temps_finLC - temps_initLC))/CLOCKS_PER_SEC;

        temps_initH = clock(); 
        BiblioH* bH2 = plusieurs_livresH(bH);
        temps_finH = clock ();
        temps_totH = ((double)(temps_finH - temps_initH))/CLOCKS_PER_SEC;

        printf("%d\t%f\t%f\n",i, temps_totLC, temps_totH);

        liberer_biblio(bLC);
        liberer_biblioH(bH);
        liberer_biblio(bLC2);
        liberer_biblioH(bH2);
    }
    return 0;
}