#include "knapsack.h"

// Fonction permettant de remplir une variable de type instance avec les données du problème contenues dans un fichier
// Paramètre en entrée : variable de type instance à remplir
// Sortie : instance remplir via la référence

void remplir_instance (instance &inst){

  string name ; // nom du fichier contenant les données du problème (Instance)
  int Taille ; // Nombres d'objets disponibles (Taille de l'instance)

  cout << "Choisir un fichier : " ;
  cin >> name ;

  ifstream infile ;
  infile.open (name.c_str()) ;

  infile >> Taille >> ws ;
  infile >> inst.w >> ws ;

  inst.objet_dispo.resize(Taille) ;

  // Remplissage de chaque objet par son profit et son poids
  for (int i = 0 ; i < inst.objet_dispo.size() ; i++){
    inst.objet_dispo[i].i = i+1 ;
    infile >> inst.objet_dispo[i].pi >> ws ;
    infile >> inst.objet_dispo[i].wi >> ws ;
  }
  infile.close() ;
}


// Fonction qui écrit une solution dans un fichier
// Paramètre en entrée : variable de type instance pour laquelle on a cherché des solutions
// Sortie : fichier rempli avec les solutions de l'instance

void remplir_solution_fichier (instance inst){

  string name ; // nom du fichier dans lequel on écrit la solution
  solution sol ; // solution du problème pour l'instance donnée

  sol = solution_heuristique_trie (inst) ;

  ofstream file ;
  cout << "Nom du fichier dans lequel enregistrer : " ;
  cin >> name ;
  file.open (name.c_str()) ;

  // Pour chaque objet le programme écrit 1 est dans le sac et 0 sinon
  for (int i=0 ; i < inst.objet_dispo.size() ; i++){
    int test = 0 ; // Si l'objet d'identifiant i+1 est dans le sac la variable test prendra la valeur 1 sinon elle restera à 0
    for (int j=0 ; j < sol.id_objet.size() ; j++){
      if (sol.id_objet[j] == i+1){
        test = 1 ;
      }
    }
    if (test == 1){
      file << 1 << " " ;
    } else {
      file << 0 << " " ;
    }
  }
  file << endl ;

  file.close() ;
}
