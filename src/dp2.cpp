#include "knapsack.h"

// Fonction qui échange les valeurs de deux variables de type état
// Paramètre d'entrée : deux variables de type état
// Sortie : ces deux variables dont la valeur a été échangée via les références

void echange_etat(etat &a , etat &b){
  etat temp = a ; // variable temporaire
  a = b ;
  b = temp ;
}

// Fonction qui recherche la position de l'élément de v entre les indices "debut" et "fin" (inclus) ayant le plus petit profit
// Paramètre d'entrée : tableau dans lequel on recherche l'élément, bornes entre lesquelles on cherche le minimum
// Sortie : renvoie la postion du minimum

int MinVec_etat (vector<etat> v , int debut , int fin ){
  etat min = v[debut] ;
  int min_pos = debut ;
  for (int i = debut ; i < fin ; i++) {
    if (v[i].profit < min.profit ){
      min = v[i] ;
      min_pos = i ;
    }
  }
  return min_pos ;
}

// Fonction qui trie par ordre de profit croissant les états contenus dans le tableau v
// Paramètre d'entrée : tableau d'états v
// Sortie : tableau d'états v trié, via la référence

void tri_etat (vector <etat>& v){
  // Augmente l'indice de la borne supérieur de 1 à chaque itération
  //  après avoir déplacé le plus petit élément entre les deux bornes
  for (int i = 0 ; i < v.size() ; i++){
    int indice_min = MinVec_etat(v , i , v.size()) ;
    echange_etat (v[indice_min] , v[i]) ;
  }
}


// Fonction qui étant donné un vecteur trié contenant des états vérifie
//  les relations de dominance et retire les états dominés
// Paramètres d'entrée : tableau duquel on veut retirer les états dominés
// Sortie : Tableau sans les états dominés via la référence

void retire (vector<etat>& v1,int capacite){
  for (int i = 0 ; i < v1.size() ; i++){
    if ((v1[i].poids > v1[i+1].poids)&&(i<v1.size()-1)||(v1[i].poids > capacite)||((v1[i].poids == v1[i+1].poids))){
      for(int j = i + 1 ; j < v1.size()+1 ; j++){
        v1[j - 1] = v1[j];  // Ensuite, on supprime le dernier élément du tableau
      }
	    v1.pop_back();// Ne pas oublier de décrémenter i !  Ainsi, au prochain tour de la boucle, on évaluera l'élément qui a pris la place de tab[i].
	    i -= 1;
    }
  }
}

// Fonction qui crée et retourne la colonne suivante du programme dynamique
// Paramètres d'entrée : tableau contenant les états de la colonne actuelle du programme dynamique , objet à ajouter pour créer la colonne suivante du programme dynamique , et capacité du sac à dos
// Sortie : colonne suivante du programme dynamique

vector <etat> dyna (vector<etat> v1 , objet &a , int &cap){
  vector<etat> c ; // Tableau contenant les états dans la colonne suivante du programme dynamique
  etat e,f ; // Les deux états générés à partir d'un état de la colonne précédente du programme dynamique

  // Remplissage de la colonne suivante
  for (int i = 0 ; i < v1.size() ; i++){
    e.poids = v1[i].poids ;
    e.profit = v1[i].profit ;
    e.predecesseur = i ;

    if (e.poids <= cap){
      c.push_back(e) ;
    }

    f.poids = a.wi + v1[i].poids ;
    f.profit = a.pi + v1[i].profit ;
    f.predecesseur = i ;

    if (f.poids <= cap) {
      c.push_back(f) ;
    }
  }
  tri_etat(c) ;
  retire (c,cap) ;
  return c ;
}


// Fonction qui calcule la solution au problème du sac à dos avec l'algorithme de programmation dynamique v2
// Paramètre d'entrée ; instance pour laquelle on veut résoudre le problème
// Sortie : solution au problème

solution solution_optimale (instance inst){
  solution sol; // Solution au problème
  vector <etat> tab (1) ; // Colonne du programme dynamique en cours de traitement
  vector < vector <etat> > tab2 ; // Matrice du programme dynamique

  int capacite = inst.w ; // Capacité du sac à dos

  // Crée la matrice du programme dynamique
  for (int i = 0 ; i < inst.objet_dispo.size() ; i++){
    objet a = inst.objet_dispo[i] ;
    tab = dyna (tab,a,capacite) ;
    tab2.push_back (tab) ;
  }
  // On retrouve ensuite les objets qui sont dans la solution optimale
  etat d ; // Etat dont on regarde le prédécesseur afin de déterminer si on ajoute ou pas l'objet correspondant à cette état dans la solution optimale
  int cpt = tab2.size()-1  ;  // colonne de l'état qu'on considère
  d = tab2[cpt][tab2[cpt].size()-1]; // état qu'on considère
  sol.profit_sol = tab2[cpt][tab2[cpt].size()-1].profit ;
  int profit_temp = 0 ; // Somme des profits des objets qui sont déjà dans la solution optimale

  // On test le dernier état du tableau et les prédécesseurs consécutifs jusqu'à celui dans la colonne de l'objet 2 compris
  while (cpt != 0){
    cpt--;
    if (( d.profit != tab2[cpt][d.predecesseur].profit) || (d.poids != tab2[cpt][d.predecesseur].poids)){
      sol.id_objet.push_back(cpt+2);
      profit_temp += inst.objet_dispo[cpt+1].pi ;
    }
    d = tab2[cpt][d.predecesseur];
  }
  // On test si l'objet 1 est dans la solution
  if (sol.profit_sol != profit_temp ){
    sol.id_objet.push_back (1) ;
  }

  tri_entier (sol.id_objet) ;

  return sol ;
}
