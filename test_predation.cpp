#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "fonct.hpp"
#include "monde.hpp"
#include "evolution.hpp"

using namespace std;

int main(int argc, char *argv[]) {
	if (argc==0) {
		cout<<"hauteur, largeur, nbres_predateurs, nbres_proies, taille case, nom_fichier"<<endl;
		return (EXIT_FAILURE);
	}
	
	srand(stoi(argv[3]));
	// srand(time(NULL));

	Monde monde;
	
	int hauteur = stoi(argv[1]);
	int largeur = stoi(argv[2]);
	
	//Creation de notre monde
	int max_energie = 100;
	int max_age = 15;//durée de vie Poisson
	int temps_generation =  1;
	//Coordonnes pour la proie
	Case case_proie;
	case_proie.lig = 0;
	case_proie.col = 0;

	//Coordonnees pour le predateur
	Case case_predateur; 
	case_predateur.lig = 0;
	case_predateur.col = 1;
	
	test_predation(&monde,  case_proie,  case_predateur, hauteur,  largeur,  temps_generation );
	monde.TEMPS_GENERATION = 1;

	afficher_Monde(monde);
	observer(monde);
	 iteration(&monde);
	afficher_Monde(monde);
	observer(monde);
	
	
	
}