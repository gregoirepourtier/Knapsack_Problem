#include "knapsack.h"

//////////////////////////// Question 1 ////////////////////////////////////////

// Fonction qui initialise une matrice de taille n+1 x W+1 puis calcule les valeurs correspondant au programme dynamique
// Paramètre d'entrée : instance pour laquelle on veut résoudre le problème du sac à dos
// Question 2 :
//    Sortie : valeur de la solution optimale

int dynamique (instance inst){

  vector <vector <int> > matrice (inst.w + 1  , vector <int> (inst.objet_dispo.size() + 1 )) ; // matrice de taille n+1 x W+1 contenant les états du programme dynamique

  // Remplissage de la matrice avec les différents états
  for (int i = 0 ; i < inst.w + 1  ; i++){
    for (int j = 0 ; j < inst.objet_dispo.size() + 1 ; j++){
      if (j == 0){
        matrice [i][j] = 0 ;
      } else {
        if (i < inst.objet_dispo[j-1].wi){
          matrice [i][j] = matrice [i][j-1] ;
        } else {
          if (matrice[i][j-1] > inst.objet_dispo[j-1].pi + matrice [i-inst.objet_dispo[j-1].wi][j-1]){
            matrice [i][j] = matrice [i][j-1] ;
          } else {
            matrice [i][j] = inst.objet_dispo[j-1].pi + matrice [i-inst.objet_dispo[j-1].wi][j-1] ;
          }
        }
      }
    }
  }

  int resultat = matrice [inst.w][inst.objet_dispo.size()] ; // Valeur de la solution optimale
  return resultat ;
}

//////////////////////////// Question 3 ////////////////////////////////////////

// Fonction qui échange les valeurs de deux entiers
// Paramètre d'entrée : deux entiers
// Sortie : ces deux entiers de valeurs echangés via les références

void echange_entier (int &a , int &b){
  int temp = a ; // Variable temporaire
  a = b ;
  b = temp ;
}

// Fonction qui recherche la position du plus petit élément entre les indices "debut" et "fin" (inclus)
// Paramètre d'entrée : tableau dans lequel on recherche le plus petit élément, bornes entre lesquelles on cherche le minimum
// Sortie : renvoie la postion du minimum

int MinVec_entier (vector<int> v , int debut , int fin ){
  int min = v[debut] ; // Initialisation du minimum
  int min_pos = debut ; // Initialisation de la position du minimum
  // On parcout les éléments du tableau de droite à gauche (l'indice début est supérieur à l'indice fin)
  for (int i = debut ; i < fin ; i++) {
    if (v[i] < min ){
      min = v[i] ;
      min_pos = i ;
    }
  }
  return min_pos ;
}

// Fonction qui trie par ordre croissant les entiers contenus dans le tableau v
// Paramètre d'entrée : tableau d'entiers v
// Sortie : tableau d'entiers v trié via la référence

void tri_entier (vector <int>& v){
  // Augmente l'indice de la borne supérieur de 1 à chaque itération
  //  après avoir déplacé le plus petit élément entre les deux bornes
  for (int i = 0 ; i < v.size() ; i++){
    int indice_min = MinVec_entier(v , i , v.size()) ;
    echange_entier (v[indice_min] , v[i]) ;
  }
}


// Fonction qui étant donné une instance et la matrice d'un programme
//  dynamique calcule calcule et retourne une solution optimale de l'instance
// Paramètre d'entrée : instance pour laquelle on veut résoudre le problème du sac à dos

solution dynamique_2 (instance inst){

  solution sol ; // Solution optimale

  vector <vector <int> > matrice (inst.w + 1  , vector <int> (inst.objet_dispo.size() + 1 )) ; // matrice de taille n+1 x W+1 contenant les états du programme dynamique

// Remplissage de la matrice avec les différents états
  for (int i = 0 ; i < inst.w + 1  ; i++){
    for (int j = 0 ; j < inst.objet_dispo.size() + 1 ; j++){
      if (j == 0){
        matrice [i][j] = 0 ;
      } else {
        if (i < inst.objet_dispo[j-1].wi){
          matrice [i][j] = matrice [i][j-1] ;
        } else {
          if (matrice[i][j-1] > inst.objet_dispo[j-1].pi + matrice [i-inst.objet_dispo[j-1].wi][j-1]){
            matrice [i][j] = matrice [i][j-1] ;
          } else {
            matrice [i][j] = inst.objet_dispo[j-1].pi + matrice [i-inst.objet_dispo[j-1].wi][j-1] ;
          }
        }
      }
    }
  }

  int cpt1 = inst.w , cpt2 = inst.objet_dispo.size() ; //compteurs pour retrouver les prédécesseurs de l'état de la solution optimale

// Retrouve les objets qui sont dans la solution
  while (matrice[cpt1][cpt2] != 0){
    if (matrice [cpt1][cpt2] == matrice[cpt1][cpt2-1]){
      cpt2 = cpt2 -1 ;
    } else {
      sol.id_objet.push_back(cpt2) ;
      cpt2 = cpt2 -1 ;
      cpt1 = cpt1 -inst.objet_dispo[cpt2].wi ;
    }
  }

  tri_entier (sol.id_objet) ;

  sol.profit_sol = matrice [inst.w][inst.objet_dispo.size()] ;
  return sol ;
}
