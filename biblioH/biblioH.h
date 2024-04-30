/* MONO 3
Maëlle LIU 21204734
Thibaut MARCQ 21202966 */

typedef struct livreh{
    int clef;
    int num; 
    char* titre;
    char* auteur;
    struct livreh *suivant;
} LivreH;

typedef struct table {
    int nE; // nombre d’elements contenus dans la table de hachage 
    int m; // taille de la table de hachage : [0..m-1]
    LivreH ** T; //table de hachage avec resolution des collisions par chainage
} BiblioH;

int fonctionClef(char* auteur);

LivreH* creer_livreH(int num, char* titre, char* auteur);

void liberer_livreH(LivreH* l);

BiblioH* creer_biblioH(int m);

void liberer_biblioH(BiblioH* b);

int fonctionHachage(int cle, int m);

void inserer(BiblioH* b, int num, char* titre, char* auteur);

void afficher_livreH(LivreH* l);

void afficher_biblioH(BiblioH* b);

LivreH* chercher_numeroH(BiblioH* b, int num);

LivreH* chercher_titreH(BiblioH* b, char* titre);

BiblioH* chercher_auteurH(BiblioH* b, char* auteur);

int supprimer_livreH(BiblioH* b, int num, char* titre, char* auteur);

void fusion_biblioH(BiblioH** b1, BiblioH* b2);

BiblioH* plusieurs_livresH(BiblioH* b);

