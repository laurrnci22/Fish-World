
#ifndef evolution_hpp_
#define evolution_hpp_

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "fonct.hpp"
#include "monde.hpp"
#include "sortie_svg.hpp"
using namespace std;



void energie(Monde *monde);
void mort_energie(Monde *monde);
void manger(Monde *mon_monde);
void disparition_population(Monde *mon_monde);
void action_population(Monde *monde);
Case rechercheDeplacementRequin(Monde monde, Case poisson );
Case recherche4Voisins(Monde monde, Case poisson );


Monde initialiser_Monde(int hauteur, int largeur,int nbres_predateurs, int nbres_proies,int max_energie, int max_age, int temps_generation ){//Pour initialiser le monde en ajoutant des individus
	Monde mon_monde;
	mon_monde = creer_Monde(mon_monde, hauteur, largeur);//creer un monde vide
	mon_monde.MAX_ENERGIE = max_energie;
	mon_monde.MAX_AGE = max_age ;//durée de vie Poisson
	mon_monde.TEMPS_GENERATION = temps_generation;

	for( int i = 0; i < nbres_predateurs; i++ ){ // ajouter les premiers predateurs 
		ajouter_Predateur(&mon_monde);
	}

	for( int i = 0; i < nbres_proies; i++ ){ // ajouter les premiers proies 
		ajouter_Proie(&mon_monde);
	}
	return mon_monde;
}


void disparition_population(Monde *mon_monde){//Ca sert à supprimer les individus morts dans le monde et dans mon tableau des individus
	Case pos;
	Especes especes;
	int i = 0;
    
  while ( i < mon_monde->especes.nbr_proies ){
		if  (mon_monde->especes.Proie[i].mourir ){
			pos = mon_monde->especes.Proie[i].position;//recuper la position de l'individu mort
			mon_monde->monde[ pos.lig * mon_monde->largeur + pos.col] = 0;
			disparition_Individu(mon_monde, i,"proie");		
		} 
		else{
      i++;
    }
  }
     
  i = 0;
  while (i < mon_monde->especes.nbr_predateurs) {
    if (mon_monde->especes.Predateur[i].mourir) {        
      pos = mon_monde->especes.Predateur[i].position;//recuper la position de l'individu mort
      mon_monde->monde[ pos.lig * mon_monde->largeur + pos.col] = 0; // met a jour mon monde		
			disparition_Individu(mon_monde, i,"predateur");
    } else {
      i++;
    }
	}
}


void reproPred(Monde *monde, float nbr){//Sert à augmenter le nombre de predateur suivant une valeur de taux
	int N = monde->especes.nbr_predateurs;
	
  for(int i = 0; i < N ; i++){
  	int nb = LoiDePoisson(nbr);//On a utilisé une loi nommée "Loi de Poissson",qui calcule la probabilité du nombre d'evenements possibles dans une intervalle de temps, dans ce tp, on essaye d'en extraire le nombre probable de poisson à creer
		for(int j=0; j<nb; j++){
			if( (monde->especes.nbr_predateurs + monde->especes.nbr_proies + nb) <= ( monde->hauteur * monde->largeur) ){
			
    		ajouter_Predateur(monde); //creation d'un individu Poisson
  		}	
		}
	}		
}


void reprProie(Monde *monde, float nbr){//Sert à augmenter le nombre de proie suivant une valeur de taux 
	int N = monde->especes.nbr_proies;
	
  for(int i = 0; i <N  ; i++){
		int nb = LoiDePoisson(nbr);//Comme on a vu au dessus, pour la creation de Proie, on a raisonné aussi à partir de la loi de Poisson pour trouver le nombre de Proie à ajouter
		for(int j=0; j<nb; j++){
			if( (monde->especes.nbr_predateurs + monde->especes.nbr_proies + nb) < (monde->hauteur * monde->largeur) ){
				ajouter_Proie(monde); //Ajoute un individu Proie
  		}
		}
	}
}


void reproduction_population(Monde *monde){
	float nb = 1.5 / (monde->TEMPS_GENERATION); // generation taux de reproduction
	
	reprProie(monde, nb);//Sert à augmenter le nombre de proie suivant une valeur de taux
	nb = 1.1 / (monde->TEMPS_GENERATION); // generation taux de reproduction
	reproPred(monde, nb);//Sert à augmenter le nombre de predateur suivant une valeur de taux		
}


void observer(Monde monde){//Sert à observer l'evolution des individus.
	// affiche les caracteristiques des individues
	int taille = monde.especes.nbr_predateurs;

	if( taille == 0 ){
		cout<<"\nIl n'y a pas de predateurs";
	}		
	else{
		cout<<"La liste des predateurs "<<endl;
		for( int i = 0; i < taille ; i++ ){
			cout<<"Predateur "<< i + 1 <<endl;
			cout<<"Il se trouve a la position: ("<< monde.especes.Predateur[i].position.lig <<" , "<< monde.especes.Predateur[i].position.col<<")";
			cout<<", Son energie "<< monde.especes.Predateur[i].energie << " il a "<<monde.especes.Predateur[i].age<<" an(s) "<<endl;
		}
		cout<<"\nIl y a "<< taille <<" predateurs dans le monde \n"<<endl;
	}
	
	taille = monde.especes.nbr_proies;
	if(taille == 0){
		cout<<"\nIl n'y a pas de proies";
	}	
	else{
		cout<<"La liste des proies "<<endl;
		for( int i = 0; i < taille ; i++ ){
			cout<<"Proie "<< i+1 <<endl;
			cout<<"Il se trouve a la position: ("<< monde.especes.Proie[i].position.lig <<" , "<< monde.especes.Proie[i].position.col <<")";
			cout<<", son energie "<< monde.especes.Proie[i].energie <<" il a "<<monde.especes.Predateur[i].age<<" an(s) "<<endl;
		}
	}
	cout<<"\nIl y a "<< taille <<" proies dans le monde "<<endl;
}


void manger(Monde *mon_monde){//Sert à indiquer que le predateur a tué une proie 
  int largeur = mon_monde->largeur;
	
	for( int i = 0; i < mon_monde->especes.nbr_predateurs ; i++ ){
		
		for ( int j = 0; j < mon_monde->especes.nbr_proies ; j++ ){
			
	
			if( (mon_monde->especes.Predateur[i].position.lig == mon_monde->especes.Proie[j].position.lig) && (mon_monde->especes.Predateur[i].position.col == mon_monde->especes.Proie[j].position.col) ){ //verifie si il existe des predateurs qui ont les memes coordonnees que la proie
			  if( mon_monde->especes.Predateur[i].energie + 1 <= mon_monde->MAX_ENERGIE ){
				  mon_monde->especes.Predateur[i].energie++; // si le predateur mange son energie augmente
				}
	
				mon_monde->especes.Proie[j].mourir = true; // le predateur mange la proie
			}
		}
	}
	disparition_population(mon_monde);
	
}


void energie(Monde *monde){//Analyse de l'energie des especes
	// epuisement des individus
	for(int i = 0; i < monde->especes.nbr_predateurs; i++){
		monde->especes.Predateur[i].energie--;
	}
	for(int i = 0; i < monde->especes.nbr_proies; i++){
		monde->especes.Proie[i].energie--;
	}
}


void mort_energie(Monde *monde){
	//Mort par energie
	//Si l'energie est 0, alors on peut dire que l'espece est morte
	for( int i = 0; i < monde->especes.nbr_predateurs; i++){
		if(monde->especes.Predateur[i].energie <= 0){
		monde->especes.Predateur[i].mourir = true;	
		}
	}
	
	for(int i = 0; i < monde->especes.nbr_proies; i++){
		if(monde->especes.Proie[i].energie <= 0){
			monde->especes.Proie[i].mourir = true;	
		}
	}
 // disparition_population(monde);//Ca sert à supprimer les individus morts dans le monde et dans mon tableau des individus
	
}


void vieillir_individu(Individu *ind, Monde monde){
	// faire vieillir un individu
	ind->age++;
	if(ind->age >= monde.MAX_AGE){
		ind->mourir = true;
	}
}


void vieillir_population(Monde *monde){
	//Faire vieillir la population
	for(int i = 0; i < monde->especes.nbr_proies; i++){
		vieillir_individu( &(monde->especes.Proie[i]), *monde);
	}

	for(int i=0; i<monde->especes.nbr_predateurs; i++){
		vieillir_individu(&( monde->especes.Predateur[i]), *monde);
	}
 // disparition_population(monde); // tuer les individus vieux
}


void iteration(Monde *monde){
	

	action_population(monde); // deplacement
	vieillir_population(monde); //Vieillir
	mort_energie(monde); // mort energie
	disparition_population(monde); // mort individu dans mourir est true
	reproduction_population(monde); // reproduvtion
	
}


void evolution_print(Monde *monde,int nbres_generations){
	//Affiche la simulation dans la console
	for(int i = 0; i < nbres_generations ; i++){ 
		cout<<endl;
		iteration(monde);
    afficher_Monde(*monde);
		observer(*monde);
		cout<<endl;
		
	}
}


void evolution_output(Monde *monde, int nbres_generations){
	// Exporte la simulation dans dans des fichiers svg
	for( int i = 0; i < nbres_generations ; i++){      
		//Codage des noms de fichier
		string str = to_string(i);
		string L;
		
		if( i < 10){
			L = "00";
		}
		else{
			L = "0";
		}		
		string nom_fichier = "out_" + L+ str +".svg";
		exporter_monde(monde, nom_fichier);    // exporter
		iteration(monde);	
	}
}

Case recherche4Voisins(Monde monde, Case coord ){//Pour rechercher la case vide et pour renouveler la position de l'individu
	int col = monde.largeur;
	int lig = monde.hauteur;
	
	int Card[4][2] = { {0,1}, {0,-1}, {-1,0}, {1,0} };// Designe les cases des E,W,N,S
	Case possible[4];
	int indice = 0;
		
	for(int i = 0; i<4; i++){
		Case temp;
		
		temp.lig = (coord.lig + Card[i][0] + lig) % lig;
		temp.col = (coord.col + Card[i][1] + col) % col;

		//Rempli le tableau des positions possibles
		if(monde.monde[temp.lig * col + temp.col] == 0){
			possible[indice] = temp;
			indice ++;
		}
	}
	if(indice == 0){
		return coord;
	}
	// Retourne une position aleatoire
	int val = alea(0, indice-1);
	return possible[val];		  
}



Case recherche8Voisins(Monde monde, Case coord ){
	// Rechherche si le predateur peut manger une proie
	int col = monde.largeur;
	int lig = monde.hauteur;

	//Correspond aux huit possibilites
	int Card[8][2] = { {0,1}, {0,-1}, {-1,0}, {1,0}, {1,1}, {-1,-1}, {1, -1}, {-1, 1} };
	Case possible[8];
	int indice = 0;
		
	for(int i = 0; i<8; i++){
		Case temp;
		
		temp.lig = (coord.lig + Card[i][0] + lig) % lig;
		temp.col = (coord.col + Card[i][1] + col) % col;
		//Rempli le tableau des positions possibles

		if(monde.monde[temp.lig * col + temp.col] == 1){
			possible[indice] = temp;
			indice ++;
		}
	}
	if(indice == 0){
		return coord;
	}
	// Retourne une position aleatoire
	int val = alea(0, indice-1);
	return possible[val];	
  
}

Case position_possible( Monde monde, Individu ind , int type_rech){
	Case pos;
	// Recherche et renvoie la case possible selon le critere recherche
	if(type_rech == 4){
		pos =  recherche4Voisins(monde, ind.position);
	}
	if(type_rech == 8){
		pos =  recherche8Voisins(monde, ind.position);
	}
	return pos;
}

void deplacer_aleatoire(Monde *monde, Individu *ind, int type){
	//Permet de deplacer un individu
	int largeur = monde->largeur;
	
	monde->monde [ ind->position.lig * largeur + ind->position.col] = 0; // met a jour le tableau monde
	//Recupere la nouvelle position
	Case position = position_possible( *monde, *ind , 4);
	ind->position = position;
	// Met a jour le tableau monde
	monde->monde [ ind->position.lig * largeur + ind->position.col] = type;
}


void predation(Monde *monde, Individu *ind){
	//Faire le deplacement d'un predateur
	int largeur = monde->largeur;
	Case position_A = ind->position;
	
	monde->monde [ ind->position.lig * largeur + ind->position.col] = 0; // met a jour le taleau monde

	//Rcherche si il peut manger une proie
	Case position = position_possible( *monde, *ind , 8);
	ind->position = position;

	//Si il n'a pas manger une proie, il se deplace comme les proies
	if( (position_A.lig == position.lig) && (position_A.col == position.col) ){
		deplacer_aleatoire(monde,ind, 2);
		
	}
	manger(monde);//Sert à indiquer que le predateur a tué une proie 
	
	monde->monde [ ind->position.lig * largeur + ind->position.col] = 2; // met a jour le tableau monde
}

void action_proie(Monde *monde){
	// Faire deplacer nos proies
	for( int i = 0; i < monde->especes.nbr_proies ; i++ ){
		
		if(monde->especes.Proie[i].energie + 1 <= monde->MAX_ENERGIE){
			monde->especes.Proie[i].energie += alea(0,1); // augemente l'energie de la proie soit de 0 ou 1
		}
		deplacer_aleatoire(monde,&(monde->especes.Proie[i]) ,1);	
	}
}

void action_predateur(Monde *monde){
	//Faire deplacer nos predateurs
	for( int i = 0; i < monde->especes.nbr_predateurs ; i++ ){
		predation(monde, &(monde->especes.Predateur[i]) );
	}
}

void action_population(Monde *monde){//Permettant aux individux de se deplacer 
	action_predateur(monde);
	action_proie(monde);
	energie(monde); // met a jour l'energie des individus

}

void test_predation(Monde *monde, Case case_proie, Case case_predateur,int hauteur, int largeur, int temps_generation ){
// Permet de simuler une condition specifique pour tester la fonction predation
	*monde =  creer_Monde(*monde,  hauteur, largeur);//creer un monde vide
	monde->MAX_ENERGIE = 10;
	monde->MAX_AGE = 10 ;//durée de vie Poisson
	monde->TEMPS_GENERATION = temps_generation;
	
	//Pour initialiser le monde en ajoutant des individus
	Individu proie;
  Case coord = case_proie;
	proie.energie = monde->MAX_ENERGIE;
  proie.position = coord;
	proie.typeP = "proie";
	monde->especes.Proie[ monde->especes.nbr_proies ] = proie;
	monde->especes.nbr_proies++;
	monde->monde[ coord.lig * monde->largeur + coord.col ] = 1; // 1 caracterisant les proies

	Individu predateur;
	coord = case_predateur;//Fait appel, au fonction aleatoire pour avoir une bonne coordonnée
	predateur.energie = monde->MAX_ENERGIE;
  predateur.position = coord;
	predateur.typeP = "predateur";
	monde->especes.Predateur[ monde->especes.nbr_predateurs ] = predateur;
	monde->especes.nbr_predateurs++;
	monde->monde[ coord.lig * monde->largeur + coord.col ] = 2;// 2 caracterisant les predateurs
}

void analyse_entete(string nom_fichier){
	//affivhe l'entete
	fstream fic(nom_fichier, ios::in | ios::out | ios::trunc);
	fic<<"Resultats de notre simulation du monde pour differentes generations"<<endl;
	fic<<"Iterations;Nombres Proies; Nombres Predateurs;Nombres iterations finales"<<endl;
}

bool est_rempli(Monde monde){
	//verifie si le monde est rempli par un individu
	if(monde.especes.nbr_proies >= monde.hauteur*monde.largeur){
		return true;
	}
	if(monde.especes.nbr_predateurs >= monde.hauteur*monde.largeur){
		return true;
	}
	return false;
}

void analyse_corps( int nbrs_proies, int nbrs_predateurs, int *generation, int nbr_generation, int hauteur, int largeur, int max_energie , int max_age,string nom_fichier){
	
	fstream fic(nom_fichier, ios::in | ios::out | ios::ate);
	
	for(int i = 0; i < nbr_generation; i++ ){
		int nbr_iteration = 0;
		int temps_generation = generation[i]; // recupere la valeur de la generation dans le tableau monde
		
		Monde monde = initialiser_Monde(hauteur,largeur,nbrs_predateurs, nbrs_proies,max_energie, max_age, temps_generation); // initialise le monde
		int j = 0;
		while( j < temps_generation){
			
			// verifie si le monde est rempli par un individu
			if(!est_rempli(monde)){
				iteration(&monde);
				nbr_iteration = j;
			}
			
			if ( est_rempli(monde) ){
				break;
			}
			j++;
		}
		// Ecrit les valeurs dans le tableau
		fic<<temps_generation<<";"<<monde.especes.nbr_proies<<";"<<monde.especes.nbr_predateurs<<";"<<nbr_iteration+1<<endl;
		
		
	cout<<"Proies :"	<<monde.especes.nbr_proies<<", Predateurs: "<<monde.especes.nbr_predateurs<<endl;
detruire_Monde(&monde);
	}
	
}

void analyse_fin(string nom_fichier, int nbrs_proies, int nbrs_predateurs, int hauteur, int largeur, int max_energie , int max_age){
	
	fstream fic(nom_fichier, ios::in | ios::out | ios::ate);
	//Affiche les information concernat le monde
	fic<<endl;
	fic<<"Configuration du monde: "<<endl;
	fic<<"Largeur: ;"<<largeur<<endl;
	fic<<"hauteur: ;"<<hauteur<<endl;
	fic<<"Nombre Proies initiales: ;"<<nbrs_proies<<endl;
	fic<<"Nombre Predateurs initial : ;"<<nbrs_predateurs<<endl;
	fic<<"Max energie: ;"<<max_energie<<endl;
	fic<<"Max age: ;"<<max_age<<endl;
}
void analyse_output( int nbrs_proies, int nbrs_predateurs, int *generation, int nbr_generation, int hauteur, int largeur, int max_energie , int max_age,string nom_fichier ){
	// Renvoi toutes les donnees dans le fichier excel
	analyse_entete( nom_fichier );
	analyse_corps( nbrs_proies,nbrs_predateurs,generation, nbr_generation, hauteur,  largeur, max_energie , max_age, nom_fichier );
	analyse_fin(nom_fichier,  nbrs_proies,  nbrs_predateurs,  hauteur,  largeur,  max_energie ,  max_age);
	
	
}



#endif

