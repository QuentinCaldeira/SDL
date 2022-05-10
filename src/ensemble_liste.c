/* file     ensemble_liste.c
 * brief    Listes simplement chaînées : representation d'un ensemble
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ensemble_liste.h"

/* Implementation fonctions pour ENSEMBLE*/

/* fonction qui retourne un ensemble vide */
ENSEMBLE *init_ensemble(){
    ENSEMBLE* ens=(ENSEMBLE*)malloc(sizeof(ENSEMBLE));
    ens->cardinal=0;
    ens->elements=NULL;
    return ens;
}

/* fonction qui teste si un ensemble est vide */
int vacuite(ENSEMBLE ens){
    return ens.cardinal==0; 
}

/* fonction qui compare deux cartes pour savoir si elles sont identiques*/
int compare(CARTE x, CARTE y){
	if (x.valeur==y.valeur && x.couleur==y.couleur )return 1;
	else return 0;
}

/* fonction qui crée une carte*/
CARTE* creer_carte(int valeur, char couleur){
	CARTE*c = (CARTE*)malloc(sizeof(CARTE));
	c->valeur=valeur;
	c->couleur=couleur;
 	c->suivant=NULL;
 	return c;
}

/* fonction qui teste l’appartenance d’un entier à un ensemble */
int appartenance(CARTE x, ENSEMBLE ens){
    if (vacuite(ens)) return 0;
    CARTE *c=ens.elements;
    while (c!=NULL){
    		if (compare(x,*c))return 1;
    		else c=c->suivant; 
    }
    return 0;
}

/* fonction qui ajoute un entier à un ensemble (en tête de liste) */
void ajout(CARTE x, ENSEMBLE *ptr_ens){
    /*if (appartenance(x,*ptr_ens)) return ;*/
    CARTE*c = (CARTE*)malloc(sizeof(CARTE));
    c->valeur=x.valeur;
    c->couleur=x.couleur;
    c->suivant=ptr_ens->elements;
    ptr_ens->elements=c;
    ptr_ens->cardinal++;
    return;
}

/* fonction qui supprime une carte dans un ensemble*/
void suppression(CARTE x, ENSEMBLE *ptr_ens){
    CARTE *c;
    CARTE *p;
    if (!appartenance(x,*ptr_ens)) return ; 
    c=ptr_ens->elements;
    if (compare(*c,x)){
    		ptr_ens->elements=c->suivant;
    		ptr_ens->cardinal--;
    		
    }
    p=c;
    c=c->suivant;
    while(c!=NULL){
    		if (compare(*c,x)){
    			p->suivant=c->suivant;
    			
    			ptr_ens->cardinal--;
				return;
    		}
    		p=c;
    		c=c->suivant;
    }
    p->suivant=NULL;
    
    return;
}

/* fonction qui affiche tous les entiers aaffichage(*ens2);ppartenant à un ensemble */
void affichage(ENSEMBLE ens){
    printf("Affichage : \n");
    CARTE *c;
    c=ens.elements;
    while (c!=NULL){
    		printf("[ %d : %c ]  ",c->valeur,c->couleur);
    		c=c->suivant;
    }
    printf("\n");
}


/* fonction qui libère l'espace mémoire de tous les maillons de la liste lst */
void liberation_liste(CARTE *lst){
    if (lst==NULL) return;
    liberation_liste(lst->suivant);
    free(lst);
}

/* fonction qui libère l'espace mémoire occupée par un ensemble */
void liberation_ensemble(ENSEMBLE *ptr_ens){
    liberation_liste(ptr_ens->elements);
    free(ptr_ens);
    return;
}




/* Implementation des fonctions Pile */


/* fonction qui initialise une pile */
void init_pile(Pile *P){	
    int i;
    for (i=0;i<T_MAX_PILE;i++)P->T[i]=NULL;
    P->sommet=0;
    return;
}

/* fonction qui verifie si une pile est vide */
int pile_est_vide(Pile P){
    return (P.sommet==0);
}

/* fonction qui verifie si une pile est pleine */
int pile_est_pleine(Pile P){ 
    return (P.sommet==T_MAX_PILE);
}

/* fonction qui empile un element si la pile n'est pas pleine */
void empiler(Pile *P, CARTE* elem){
    if (pile_est_pleine(*P)) return;
    P->T[P->sommet]=elem;
    P->sommet++;
    return;
}

/* fonction qui depile un elemnt si la pile n'est pas vide */
CARTE* depiler(Pile *P){	
    if (pile_est_vide(*P)) return NULL;
    CARTE* ret;
    ret=P->T[P->sommet-1];
    P->sommet--;
    return ret;
}

/* fonction qui affiche les elements d'une pile */
void afficher_pile(Pile P){
	if (P.sommet==0 ){
		printf("Pile Vide\n");
		return;}
    int i;
	/*printf("Nb pile : %d\n",P.sommet);*/
    for (i=P.sommet-1;i>=0;i--){ printf("_______________________\n Valeur: %d  Couleur: %c\n",P.T[i]->valeur,P.T[i]->couleur);}
   	printf("_______________________\n");
   	return;
}

/* fonction qui depile tous les elements de la pile */
void vider_pile(Pile *P){
    P->sommet=0;
}





/* Fonction du jeu*/

ENSEMBLE* init_paquet(){
	int i,j;
	CARTE*c;
	ENSEMBLE* ens=init_ensemble();
	/* La carte 0 est presente qu'une fois dans chaque couleur*/
	c=creer_carte(0,'R');
	ajout(*c,ens);
	c=creer_carte(0,'V');
	ajout(*c,ens);
	c=creer_carte(0,'B');
	ajout(*c,ens);
	c=creer_carte(0,'J');
	ajout(*c,ens);
	/* Les cartes 1 à 9,les blocages(10), et les inverses(11) et les +2(12) sont presentes 2 fois dans chaque couleur*/
	for (i=1;i<=12;i++){
		for (j=0;j<2;j++){
			c=creer_carte(i,'R');
			ajout(*c,ens);
			c=creer_carte(i,'V');
			ajout(*c,ens);
			c=creer_carte(i,'B');
			ajout(*c,ens);
			c=creer_carte(i,'J');
			ajout(*c,ens);
		}
	}
	/* Les cartes changement de couleur (13) et les +4 (14) sont presentes 4 fois [couleur noire]*/
	for (i=13;i<=14;i++){
		for (j=0;j<4;j++){
			c=creer_carte(i,'N');
			ajout(*c,ens);
		}
	}
	return ens;
}

void init_pioche(ENSEMBLE* src,Pile* Pioche,int alea){
		ENSEMBLE* Pioche_mix=init_ensemble();
		distribution_random(src,Pioche_mix, src->cardinal,alea);
		/*printf("Pioche Mix : \n");
		affichage(*Pioche_mix);*/
		CARTE* prec;
		CARTE* suiv=Pioche_mix->elements;
		while(suiv!=NULL){
			prec=suiv;
			suiv=suiv->suivant;
			prec->suivant=NULL;
			empiler(Pioche, prec);
		}
		/*printf("src :%d\n",src->cardinal);*/
		src->cardinal=0;
		src->elements=NULL;
		return;
}

CARTE* lire_carte(ENSEMBLE ens,int position){
	CARTE* c;
    c=ens.elements;
	while (position>0){
		c=c->suivant;
		position-=1;
	}
	return c;

}

void distribution_random(ENSEMBLE* src,ENSEMBLE* dst, int nb,int alea){
	int i;
	int indice;
	float nb_random=src->cardinal;
	CARTE* x;

	srand(alea);
	/*printf("src :%d\n",src->cardinal);*/
	for (i=0;i<nb;i++){
		indice=1+rand()*nb_random/(RAND_MAX+1.0)-1;
		/*printf("indice = %d\n",indice);*/
		nb_random-=1.0;
		if (indice!=0)x=lire_carte(*src,indice);
		else x=lire_carte(*src,0);
		/*printf("carte %d :  %d %c\n",i+1,x->valeur,x->couleur );*/
		ajout(*x, dst);
		suppression(*x,src);
	}
	
}

int recherche_couleur_valeur(CARTE x,ENSEMBLE main){
		CARTE* c=main.elements;
		while (c!=NULL){
			if (c->valeur==x.valeur || c->couleur==x.couleur || c->couleur=='N') return 1;
			else c=c->suivant;
		}
		return 0;
}

/*fonction permetant de mettre la premiere carte sur la table (debut de partie ou apres que la pioche soit de nouveau pleine*/
void Defausse_vide(Pile* Defausse,Pile* Pioche){
	if (Defausse->sommet==0){
		CARTE* carte_courante=depiler(Pioche);
		while (carte_courante->valeur>9) {
			empiler(Defausse,carte_courante);
			carte_courante=depiler(Pioche);
		}
		empiler(Defausse,carte_courante);
	}
	return;
}

void afficher_table(Pile Defausse, Pile Pioche){
	printf("\n====Table====\n");

	printf("\n");
	printf("-Pioche: \n");
	printf("Nb pile : %d\n",Pioche.sommet);
	/*afficher_pile(Pioche);*/
	printf("\n");
	printf("-Defausse: \n");
	printf("Nb pile : %d\n\n",Defausse.sommet);
	afficher_pile(Defausse);
	printf("\n\n");
	return;
}

int effet_de_le_carte(CARTE carte_cour,CARTE carte_table){
	if ((carte_cour.valeur==11 && carte_cour.couleur==carte_table.couleur) || (carte_cour.valeur==carte_table.valeur && carte_cour.valeur==11 )) return 2;   /*inverse*/
	else if ((carte_cour.valeur==10 && carte_cour.couleur==carte_table.couleur) || (carte_cour.valeur==carte_table.valeur && carte_cour.valeur==11 )) return 3;   /*blocage*/
	else if (carte_cour.valeur==13) return 4;   /*chgt couleur*/
	else if (carte_cour.valeur==12 && carte_cour.couleur==carte_table.couleur) return 5;   /*+2*/
	else if (carte_cour.valeur==14) return 6;   /*+4*/
	else if (carte_cour.valeur==carte_table.valeur || carte_cour.couleur==carte_table.couleur) return 1; /*carte normal*/
	else return -1;
}

int modulo(int x,int N){
    return (x % N + N) %N;
}

int tour_de_joueur(int joueur_cour,int sens,int nb_joueur){
	return modulo((joueur_cour+sens),nb_joueur);
}




