#include "knapsack.h"

// Fonction qui convertie un entier en base décimale en binaire
// Paramètres d'entrée : tableau dans lequel on écrira l'entier en binaire (chaque 0 ou 1 sera un élément du tableau) , entier à convertir
// Sorite : tableau contenant l'entier en binaire via la référence

void convertisseur (vector <int>& v1 , int nb){
  int ind = 0 ; // Indice du tableau
  while (nb != 0){
    if (nb%2 == 0){
      v1[ind] = 0 ;
    } else {
      v1[ind] = 1 ;
    }
    nb = nb / 2 ;
    ind++ ;
  }
}

// Fonction qui calcule la solution au problème du sac à dos avec l'algorithme brute force
// Paramètre d'entrée ; instance pour laquelle on veut résoudre le problème
// Sortie : solution au problème

solution brute_force (instance inst){
  vector <int> binaire ; // Tableau contenant un entier convertie en binaire
  vector <vector<int> > temporaire ; // Matrice contenant l'ensemble des 2^n solutions possibles au problème
  int n ; // Taille de l'instance
  solution sol ; // Solution au problème

  sol.profit_sol = 0 ;

  n = inst.objet_dispo.size() ;

  binaire.resize (n) ;

  for (int i = 0 ; i < n ; i++){
    binaire [i] = 0 ;
  }
  // On remplit notre matrice avec les 2^n solutions possibles
  for (int i = 0 ; i < pow(2,n) ; i++){
    convertisseur (binaire,i) ;
    temporaire.push_back(binaire) ;
  }
  // profit_max : variable permettant  de comparer les solutions par rapport à leur profit
  // somme_poids : somme des poids des objets dans le sac
  // indice_sol : indice de la solution dans la matrice ( elle est sur une ligne entière dans la matrice)
  // profit : profit associé à une solution
  // cpt : compteur pour parcourir les solutions dans temporaire jusqu'à la première qui est réalisable
  int profit_max, somme_poids, indice_sol, profit, cpt = 0 ;

  // on parcourt les solutions dans temporaire jusqu'à la première qui est réalisable
  do {
    somme_poids = 0;
    profit = 0;
    for(int j=0 ; j<temporaire[cpt].size() ; j++){
      if(temporaire[cpt][j]==1){
        somme_poids += inst.objet_dispo[j].wi;
        profit += inst.objet_dispo[j].pi;
      }
    }
    cpt += 1 ;
  } while (somme_poids>inst.w);
  indice_sol = cpt-1 ;
  profit_max = profit ;

  // on test toutes les solution restantes dans temporaire pour trouver la solution réalisable avec le plus grand profit
  for (int k=cpt ; k<temporaire.size() ; k++){
    somme_poids =0;
    profit = 0;
    for(int j=0 ; j<temporaire[k].size() ; j++){
      if(temporaire[k][j]==1){
        somme_poids += inst.objet_dispo[j].wi;
        profit += inst.objet_dispo[j].pi;
      }
    }
    if(somme_poids<=inst.w){
      if(profit>profit_max){
        indice_sol = k;
        profit_max = profit;
      }
    }
  }
  sol.profit_sol = profit_max ;
  // la solution est l'élément d'indice indice_sol dans temporaire
  for (int j =0; j<temporaire[indice_sol].size(); j++){
    if(temporaire[indice_sol][j]==1){
      sol.id_objet.push_back(j+1);
    }
  }
  return sol;
}
