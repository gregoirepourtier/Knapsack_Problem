#include "knapsack.h"

//////////////////////////// Question 1 ////////////////////////////////////////

// Fonction qui étant donné une instance retourne une solution en ajoutant les objets tant que ceux-ci ne dépasse pas la capacité du sac
// Paramètre d'entrée : instance pour laquelle on cherche la solution
// Sortie : solution du problème du sac à dos

solution solution_heuristique (instance inst){

  int somme_poids = 0 ; // Somme des poids des objets dans le sac
  solution sol ; // Solution fournie par l'algorithme

  sol.profit_sol = 0 ;

  // Ajoute des objets dans la solution si la somme des poids de cette objet et de ceux dèjà dans la solution ne dépasse pas la capacité du sac
  for (int i = 0 ; i < inst.objet_dispo.size() ; i++){
    somme_poids = somme_poids + inst.objet_dispo[i].wi ;
    if (somme_poids < inst.w){
      sol.profit_sol = sol.profit_sol + inst.objet_dispo[i].pi ;
      sol.id_objet.push_back (inst.objet_dispo[i].i) ;
    } else {
      somme_poids = somme_poids - inst.objet_dispo[i].wi ;
    }
  }
  return sol ;
}

// Fonction qui affiche la solution de solution_heuristique
void affichage_solution_heuristique (instance &inst){
  solution sol ;
  sol = solution_heuristique (inst) ;

  cout << "Profit total = " << sol.profit_sol << endl ;
  cout << "Objets présents dans le sac : " << sol.id_objet[0] ;
  for (int i = 1 ; i < sol.id_objet.size() ; i ++){
    cout << " , " << sol.id_objet[i] ;
  }

  cout << endl ;
}


//////////////////////////// Question 2 ////////////////////////////////////////

// Surcharge de l'opérateur < , pour comparer deux objets en fonction de leur utilité
// Paramètre d'entrée : les deux objets à comparer
// Sortie : renvoie true si l'utilité de l'objet 1 est inférieure à celle de l'objet 2 et false sinon

bool operator < (objet u1 , objet u2){
  double utilite_1 , utilite_2 ; // Utilité de chaque objet
  utilite_1 = (double(u1.pi) / u1.wi) ;
  utilite_2 = (double(u2.pi) / u2.wi) ;
  if (utilite_1 < utilite_2){
    return true ;
  } else {
    return false ;
  }
}

//////////////////////////// Question 3 ////////////////////////////////////////


// Fonction qui échange les valeurs de deux objets
// Paramètre d'entrée : deux objets
// Sortie : ces deux objets de valeurs echangés via les références

void echange (objet &a , objet &b){
  objet temp = a ; // Variable temporaire
  a = b ;
  b = temp ;
}

// Fonction qui recherche la position du plus petit élément entre les indices "debut" et "fin" (inclus)
// Paramètre d'entrée : tableau dans lequel on recherche le plus petit élément, bornes entre lesquelles on cherche le minimum
// Sortie : renvoie la postion du minimum

int MinVec (vector<objet> v , int debut , int fin ){
  objet min = v[debut] ; // Initialisation du minimum
  int min_pos = debut ; // Initialisation de la position du minimum
  // On parcout les éléments du tableau de droite à gauche (l'indice début est supérieur à l'indice fin)
  for (int i = debut ; i > fin ; i--) {
    if (v[i] < min ){
      min = v[i] ;
      min_pos = i ;
    }
  }
  return min_pos ;
}

// Fonction qui trie par ordre décroissant d'utilité les objets contenus dans le tableau v
// Paramètre d'entrée : tableau d'objets v
// Sortie : tableau d'objets v trié via la référence

void tri (vector <objet>& v){
  // Part du tableau entier et réduit l'indice de la borne supérieur de 1 à chaque itération
  //  après avoir déplacé le plus petit élément entre les deux bornes
  for (int i = v.size()-1 ; i > -1 ; i--){
    int indice_min = MinVec(v , i , -1) ;
    echange (v[indice_min] , v[i]) ;
  }
}
// Fonction solution_heuristique modifiée :
//   fonction qui étant donné une instance retourne une solution en ajoutant les objets triés par utilité décroissante
//   tant que ceux-ci ne dépasse pas la capacité du sac
// Paramètre d'entrée : instance pour laquelle on cherche la solution
// Sortie : solution du problème du sac à dos

solution solution_heuristique_trie (instance inst){

  int somme_poids = 0 ; // Somme des poids des objets dans le sac
  solution sol ; // Solution fournie par l'algorithme
  int Taille ; // Nombres d'objets disponibles

  Taille = inst.objet_dispo.size() ;

  vector <objet> obj (Taille) ; // Tableau d'objets intermédiaire qu'on va trier

  sol.profit_sol = 0 ;

  // Remplissage du tableau obj avec les objets disponibles
  for (int i = 0 ; i < Taille ; i++){
    obj [i] = inst.objet_dispo[i] ;
  }

  tri (obj) ;

  // Ajoute des objets dans la solution si la somme des poids de cette objet et de ceux dèjà dans la solution ne dépasse pas la capacité du sac
  for (int i = 0 ; i < Taille ; i++){
    somme_poids = somme_poids + obj[i].wi ;
    if (somme_poids <= inst.w){
      sol.profit_sol = sol.profit_sol + obj[i].pi ;
      sol.id_objet.push_back (obj[i].i) ;
    } else {
      somme_poids = somme_poids - obj[i].wi ;
    }
  }
  tri_entier (sol.id_objet) ;
  return sol ;
}

// Fonction qui affiche la solution de solution_heuristique_trie
void affichage_solution_heuristique_trie (instance inst){
  solution sol ;
  sol = solution_heuristique_trie (inst) ;

  cout << "Profit total = " << sol.profit_sol << endl ;
  cout << "Objets présents dans le sac : " << sol.id_objet[0] ;
  for (int i = 1 ; i < sol.id_objet.size() ; i ++){
    cout << " , " << sol.id_objet[i] ;
  }

  cout << endl ;
}
