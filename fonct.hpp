
#ifndef fonct_hpp_
#define fonct_hpp_
#include <iostream>
#include <cmath>

using namespace std;

struct Case{ //coordonnees
	int lig;
	int col;
};

int alea(int a, int b){ // renvoie une valeur aleatoire entre a et b
	return rand()%(b-a+1)+a;
}

int LoiDePoisson(float lambda){
	//permet de fixer un taux de reproduction
  int k=0;
  int p=1;
  int u;
  while(p>exp(-lambda)){
    u=alea(0,1);
    p=p*u;
    k++;
  }
  return k-1;
}

#endif