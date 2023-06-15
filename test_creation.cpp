#include <iostream>
#include <cstdlib>
#include <ctime>
#include "fonct.hpp"
#include "monde.hpp"
//#include "evolution.hpp"

using namespace std;


// //  g++ -o main -I. test_ajout.cpp


int main(int argc, char *argv[]) {
	if (argc==0) {
		return (EXIT_FAILURE);
	}
	
	srand(time(NULL));
	Monde monde;
	int hauteur = stoi(argv[1]);
	int largeur = stoi(argv[2]);
	
	monde = creer_Monde( monde, hauteur,largeur );
	
	afficher_Monde(monde);
	detruire_Monde(&monde);
	 
}

