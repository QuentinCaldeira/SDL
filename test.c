/* file     ensemble_liste.c
 * brief    Listes simplement chaînées : representation d'un ensemble
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ensemble_liste.h"

int main(){	

	srand(time(NULL));
	printf("\n\n=====================================\n");
	printf("=============  JEU UNO  =============\n");
	printf("=====================================\n\n");



	printf("-----------------\n");
	printf(" INITIALISATION\n");
	printf("-----------------\n\n");

	/*Initialisation du paquet de carte Uno soit 108 cartes*/
	ENSEMBLE* Paquet=init_paquet();
	printf("Paquet de carte du jeu : \n");
	printf("caridinal :%d\n",Paquet->cardinal);
	/*affichage(*Paquet);*/
	
	/*Initialisation et creation des mains des joueurs */
	ENSEMBLE* J1=init_ensemble();
	ENSEMBLE* J2=init_ensemble();
	ENSEMBLE* J3=init_ensemble();
	ENSEMBLE* J4=init_ensemble();
	
	/*Distribution des cartes dans la main de chaque joueurs*/
	distribution_random(Paquet,J1, 7,rand());
	distribution_random(Paquet,J2, 7,rand());
	distribution_random(Paquet,J3, 7,rand());
	distribution_random(Paquet,J4, 7,rand());
	
	/*AFfichage des mains de tous les joueurs*/
	printf("\n");
	printf("Joueur 0 : %d cartes\n",J1->cardinal);
	affichage(*J1);
	printf("\n");
	printf("Joueur 1 : %d cartes\n",J2->cardinal);
	affichage(*J2);
	printf("\n");
	printf("Joueur 2: %d cartes\n",J3->cardinal);
	affichage(*J3);
	printf("\n");
	printf("Joueur 3 : %d cartes\n",J4->cardinal);
	affichage(*J4);

	/*Initialisation de la Pioche et de la Defausse ainsi que leurs remplissage*/
	Pile Defausse;
	Pile Pioche;
	init_pile(&Pioche);
	init_pile(&Defausse);
	init_pioche(Paquet,&Pioche,rand());
	/*Affichage de la Pioche et de la Defause c'est a dire la Table*/
	afficher_table(Defausse,Pioche);
	



	printf("\n\n--------------------------------\n");
	printf("--------Debut de partie --------\n");
	printf("--------------------------------\n");

	/* On retourne la premiere carte de la pioche differente des cartes speciales*/
	Defausse_vide(&Defausse,&Pioche);
	

	int tour_joueur=0;
	int sens=1;
	int choix_carte;
	int effet_carte;
	char effet_couleur;
	ENSEMBLE* joueur_cour;
	CARTE* carte_cour;
	CARTE carte_table;
	
	joueur_cour=J1;
	while (joueur_cour->cardinal!=0 ){
		
		carte_table=*Defausse.T[Defausse.sommet-1];    /*Carte sur la table */
		
		if (effet_carte==6 ||effet_carte==4 )  {      /* effet emit par le joueur precedent*/
			carte_table.couleur=effet_couleur;
			carte_table.valeur=-1;}
		
		
		printf("\n\n------Table------\n");
		printf("Carte sur la table v:%d c:%c\n\n",carte_table.valeur,carte_table.couleur);
		/*afficher_table(Defausse,Pioche);*/
		printf("\n\nJoueur %d\n",tour_joueur+1);    /*Determanation du tour du joueur*/
		switch(tour_joueur){
			case 0:
				joueur_cour=J1;
				break;
			case 1:
				joueur_cour=J2;
				break;
			case 2:
				joueur_cour=J3;
				break;
			case 3:
				joueur_cour=J4;
				break;	
			default:
				break;
		}
		
		printf("-------------------\n");
		printf("Joueur %d: %d cartes\n",tour_joueur+1,joueur_cour->cardinal);
		affichage(*joueur_cour);

		if (!(recherche_couleur_valeur(carte_table,*joueur_cour))){       /* Le joueur pioche car il n'a pas de carte pour jouer*/
			printf("Joueur %d pioche car il ne possede pas de carte a jouer\n",tour_joueur+1);
			ajout(*depiler(&Pioche),joueur_cour);
			printf("Joueur %d apres pioche: %d cartes\n",tour_joueur+1,joueur_cour->cardinal);
			affichage(*joueur_cour);
		}
		else{
			do{                      /* La carte choisi doit etre valide*/
				do{     			 /*On demande la position de la carte choisie qui ne doit pas depasser le nombre de cartes dans la main*/
					printf("Choix du numero de la carte  ?\n");
					scanf("%d",&choix_carte);
				}while(choix_carte>joueur_cour->cardinal);
				carte_cour=lire_carte(*joueur_cour,choix_carte-1);
				printf("Carte choisie %d %c\n",carte_cour->valeur,carte_cour->couleur);
				effet_carte= effet_de_le_carte(*carte_cour,carte_table);   /* 1: Carte normal    2: Carte inversee    3: Carte bloquage  4:chgt couleur 5: 2+   6: +4 */
				printf("Effet de carte : %d\n",effet_carte);
			}while(effet_carte==-1);			
			
			empiler(&Defausse,carte_cour);
			afficher_pile(Defausse);
			suppression(*carte_cour, joueur_cour);
			printf("Joueur %d apres suppression: %d cartes\n",tour_joueur+1,joueur_cour->cardinal);
		}
		if (effet_carte==1) tour_joueur=tour_de_joueur(tour_joueur,sens,4);  /*effet normal*/
		if (effet_carte==2) {				/*effet inverse */
			sens=sens*-1;
			tour_joueur=tour_de_joueur(tour_joueur,sens,4);
			printf("INVERSE TOUR DE JOUEUR : %d \n",tour_joueur);
			}  
		if (effet_carte==3) tour_joueur=tour_de_joueur(tour_joueur,sens*2,4);  /*effet blocage */
		if (effet_carte==4) {    /*effet chgt couleur */
			printf("Couleur Choisie ? \n");
			scanf(" %c",&effet_couleur);
			tour_joueur=tour_de_joueur(tour_joueur,sens,4);
			}
		if (effet_carte==5) {     /*effet +2 */
			printf("Joueur %d pioche 2 cartes\n",tour_joueur+2);
			tour_joueur=tour_de_joueur(tour_joueur,sens,4);
			switch(tour_joueur){
				case 0:
					joueur_cour=J1;
					break;
				case 1:
					joueur_cour=J2;
					break;
				case 2:
					joueur_cour=J3;
					break;
				case 3:
					joueur_cour=J4;
					break;	
				default:
					break;
		    }
			ajout(*depiler(&Pioche),joueur_cour);
			ajout(*depiler(&Pioche),joueur_cour);
			}
		if (effet_carte==6) {     /*effet +4 */
			printf("Couleur Choisie ? \n");
			scanf(" %c",&effet_couleur);
			printf("Joueur %d pioche 4 cartes\n",tour_joueur+1);
			tour_joueur=tour_de_joueur(tour_joueur,sens,4);
			switch(tour_joueur){                         /*modulo a ne pas oublier*/
				case 0:
					joueur_cour=J1;
					break;
				case 1:
					joueur_cour=J2;
					break;
				case 2:
					joueur_cour=J3;
					break;
				case 3:
					joueur_cour=J4;
					break;	
				default:
					break;
			}
			ajout(*depiler(&Pioche),joueur_cour);
			ajout(*depiler(&Pioche),joueur_cour);
			ajout(*depiler(&Pioche),joueur_cour);
			ajout(*depiler(&Pioche),joueur_cour);}
		


	}
	
	


	return 0;
}

