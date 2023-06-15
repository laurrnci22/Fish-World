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
	
	srand(stoi(argv[6]));
	// srand(time(NULL));

	Monde monde;
	
	int hauteur = stoi(argv[1]);
	int largeur = stoi(argv[2]);
	int nbres_predateurs = stoi(argv[3]);
	int nbres_proies = stoi(argv[4]);

	int max_energie = 100;
	int max_age = 15;//durée de vie Poisson
	int temps_generation =  stoi(argv[5]);
	monde = initialiser_Monde(hauteur,largeur,nbres_predateurs, nbres_proies,max_energie, max_age, temps_generation);

	

 	afficher_Monde(monde);
	observer(monde);
	 // evolution_output(&monde, monde.TEMPS_GENERATION, "out");
	evolution_print(&monde,monde.TEMPS_GENERATION);
	// observer(monde);
	
	
}