#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>

using namespace std ;

// Déclaration du type objet, composé de 3 membres
struct objet {
  int i ; // permet d'identifier l'objet
  int wi ; // poids de l'objet
  int pi ; //profit de l'objet
};

// Déclaration du type instance, composé de 2 membres
struct instance {
  int w ; // Capacité du sac à dos
  vector <objet> objet_dispo ; // objets disponibles
};

// Déclaration du type solution, composé de 2 membres
struct solution {
  int profit_sol ; // profit de la solution
  vector <int> id_objet ; // identifiants des objets placés dans le sac
};

// Déclaration du type etat, composé de 3 membres
struct etat {
  int profit ; // profit associé à l'état
  int poids ; // poids associé à l'état
  int predecesseur ; // prédécesseur de l'état
};

// Exercice 2
void remplir_instance (instance &inst) ;
void remplir_solution_fichier (instance inst) ;

// Exercice 3
solution solution_heuristique (instance inst) ;
void affichage_solution_heuristique (instance &inst) ;

bool operator < (objet u1 , objet u2) ;

void echange(objet &a , objet &b) ;
int MinVec (vector<objet> v , int debut , int fin ) ;
void tri (vector <objet>& v) ;
solution solution_heuristique_trie (instance inst) ;
void affichage_solution_heuristique_trie (instance inst) ;

// Exercice 4
void convertisseur (vector <int>& v1 , int nb) ;
solution brute_force (instance inst) ;

// Exercice 5
int dynamique (instance inst) ;
void echange_entier (int &a , int &b);
int MinVec_entier (vector<int> v , int debut , int fin );
void tri_entier (vector <int>& v);
solution dynamique_2 (instance inst) ;

// Exercice 6
void echange_etat(etat &a , etat &b);
int MinVec_etat (vector<etat> v , int debut , int fin );
void tri_etat (vector <etat>& v);
void retire (vector<etat>& v1,int capacite);
vector <etat> dyna (vector<etat> v1 , objet &a , int &cap);
solution solution_optimale (instance inst);
