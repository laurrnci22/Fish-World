// DESIR et RANDRIANALISOA
// Simulation d'un monde aquatique 
// 2022
#ifndef monde_hpp_
#define monde_hpp_

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "fonct.hpp"

using namespace std;
const int MAX_INDIV = 10000;

struct Individu {
	bool mourir = false;	
	Case position;
	int energie ;
	string typeP;
	int age = 1; 
};


struct Especes{
	Individu Proie[MAX_INDIV];
	int nbr_proies = 0;
	Individu Predateur[MAX_INDIV];
	int nbr_predateurs = 0;
};


struct Monde{
	int hauteur;
	int largeur;
	int *monde; // Tableau de monde;
	Especes especes;
	int taille_Case;	
	
	/*Parametre*/
	int MAX_ENERGIE;
	int MAX_AGE ;//durée de vie Poisson
	int TEMPS_GENERATION;
};


Monde creer_Monde(Monde mon_monde, int hauteur, int largeur){//creer un monde vide
	mon_monde.hauteur = hauteur;
	mon_monde.largeur = largeur;
	mon_monde.taille_Case = 20; 
	
	mon_monde.monde = new int [hauteur*largeur];
	
	for(int i = 0; i < hauteur; i++){
		for(int j = 0; j < largeur; j++){	
			mon_monde.monde[ i * largeur + j ] = 0; // Initialisation a vide, on suppose que 0, indique la non-occupation de la case
		}
	}
	return mon_monde;
}


void detruire_Monde(Monde *mon_monde){//Destruction de monde et ses individus 	
	mon_monde->largeur = mon_monde->hauteur = 0;//Remise à 0 de sa taille
	mon_monde->especes.nbr_proies = mon_monde->especes.nbr_predateurs =  0;//Remise à 0 du nombre d'especes
	mon_monde->monde = nullptr;
	delete mon_monde->monde;
}


void afficher_Monde(Monde mon_monde){	//Affichage de la grille du monde
	cout<<endl;
	for(int i = 0; i < mon_monde.hauteur; i++){
		for (int j = 0; j < mon_monde.largeur; j++){
			if(mon_monde.monde[ i * mon_monde.largeur + j ] == 0){
				cout<<" ";//Ici pour la case non occupée, on remplace par une " "
			}
			if(mon_monde.monde[ i * mon_monde.largeur + j ] == 1){
				cout<<"P";//Designe la proie
			}
			if( mon_monde.monde[ i * mon_monde.largeur + j ] == 2){
				cout<<"R";//Designe le predateur
			}
			cout<<" ";
		}
		cout<<endl;
	}
}


Case position_aleatoire(Monde monde){
	//recherche une position aleatoire pour placer mes premiers individu
	Case coord;
  coord.lig=alea( 0, monde.hauteur - 1 );
  coord.col=alea( 0, monde.largeur - 1 );

	while(monde.monde[ coord.lig * monde.largeur + coord.col ] != 0){
		coord.lig = alea( 0, monde.hauteur - 1 );
  	coord.col = alea( 0, monde.largeur - 1 );
	}
	return coord;
}


void ajouter_Proie(Monde *monde){//Permet l ajout d une proie
	Individu proie;
  Case coord = position_aleatoire(*monde);//Appel au fonction precedente pour avoir une bonne coordonnée
	proie.energie = monde->MAX_ENERGIE;
  proie.position = coord;
	proie.typeP = "proie";
	monde->especes.Proie[ monde->especes.nbr_proies ] = proie;
	monde->especes.nbr_proies++;
	monde->monde[ coord.lig * monde->largeur + coord.col ] = 1; // 1 caracterisant les proies
}


void ajouter_Predateur(Monde *monde){	// permet d'ajouter un predateur
	Individu predateur;
	Case coord = position_aleatoire(*monde);//Fait appel, au fonction aleatoire pour avoir une bonne coordonnée
	predateur.energie = monde->MAX_ENERGIE;
  predateur.position = coord;
	predateur.typeP = "predateur";
	monde->especes.Predateur[ monde->especes.nbr_predateurs ] = predateur;
	monde->especes.nbr_predateurs++;
	monde->monde[ coord.lig * monde->largeur + coord.col ] = 2;// 2 caracterisant les predateurs
}


void disparition_Individu(Monde *monde, int indice, string typeP){
	if(typeP == "predateur"){
		monde->especes.nbr_predateurs--;	
		monde->especes.Predateur[ indice ] =  monde->especes.Predateur[ monde->especes.nbr_predateurs ]; //met a jour mon tableau d'individu
	}
    
	if(typeP == "proie"){
		monde->especes.nbr_proies--;
		monde->especes.Proie[ indice ] = monde->especes.Proie[ monde->especes.nbr_proies ]; //met a jour mon tableau d'individu		
	}
  
}

#endif

		
		
		