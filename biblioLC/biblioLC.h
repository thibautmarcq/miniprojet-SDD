/* MONO 3
Maëlle LIU 21204734
Thibaut MARCQ 21202966 */

typedef struct livre {
    int num ;
    char * titre ;
    char * auteur ;
    struct livre * suiv ;
} Livre ;


typedef struct { /* Tete fictive */
    Livre * L ; /* Premier element */
} Biblio ;

Livre* creer_livre(int num, char* titre,char* auteur);

void liberer_livre(Livre *l);

Biblio * creer_biblio();

void liberer_biblio(Biblio* b);

void inserer_en_tete(Biblio*b, int num, char* titre, char* auteur);

void afficher_livre(Livre* l);

void afficher_biblio(Biblio* b);

Livre* chercher_num(Biblio* b, int num);

Livre* chercher_titre(Biblio* b, char* titre);

Biblio* chercher_auteur(Biblio* b, char* auteur);

int supprimer_livre(Biblio*b, int num, char* titre, char* auteur);

void fusion_biblio(Biblio** b1, Biblio* b2);

Biblio* plusieurs_livres(Biblio* b);

