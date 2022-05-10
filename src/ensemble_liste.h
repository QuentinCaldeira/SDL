/* file     ensemble.h
 * brief    Déclaration d'un ensemble d'entiers et des prototypes des fonctions
 *          applicables sur cet ensemble
 */

#include <stdio.h>

#define T_MAX_PILE 108



/* structure d'enregistrement COUPLE */
typedef struct couple {
    int valeur;
    char couleur;
    struct couple *suivant;
} CARTE;

/* structure d'enregistrement ENSEMBLE */
typedef struct ens {
    unsigned int cardinal;
    CARTE *elements;
} ENSEMBLE;

/* structure d'enregistrement ENSEMBLE */
typedef struct {
    int sommet;
    CARTE* T[T_MAX_PILE];
} Pile;

/* prototypes des fonctions ensemmble */
ENSEMBLE *init_ensemble();
ENSEMBLE* init_paquet();
CARTE* creer_carte(int valeur, char couleur);
int compare(CARTE x, CARTE y);
int vacuite(ENSEMBLE ens);
int appartenance(CARTE x, ENSEMBLE ens);
void ajout(CARTE x, ENSEMBLE *ptr_ens);
void affichage(ENSEMBLE ens);
void suppression(CARTE x, ENSEMBLE *ptr_ens);
CARTE* lire_carte(ENSEMBLE ens,int position);
void liberation_liste(CARTE *lst);
void init_pioche(ENSEMBLE* src,Pile* Pioche,int alea);
void liberation_ensemble(ENSEMBLE *ptr_ens);
void distribution_random(ENSEMBLE *src,ENSEMBLE *dst, int nb,int alea);
int recherche_couleur_valeur(CARTE x,ENSEMBLE main);
void Defausse_vide(Pile* Defausse,Pile* Pioche);
void afficher_table(Pile Defausse, Pile Pioche);
int effet_de_le_carte(CARTE carte_cour,CARTE carte_table);;
int modulo(int x,int N);
int tour_de_joueur(int joueur_cour,int sens,int nb_joueur);



/* prototypes des fonctions Pile */
void init_pile(Pile *P);
int pile_est_vide(Pile P);
int pile_est_pleine(Pile P);
void empiler(Pile *P, CARTE* elem);
CARTE* depiler(Pile *P);
void afficher_pile(Pile P);
void vider_pile(Pile *P);

