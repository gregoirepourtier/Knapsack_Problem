#include "knapsack.h"
#include <ctime>

int main() {
  instance inst ;
  int choix ;
  solution sol ;

  do {
    cout<< "Programme avec lequel on résoud le problème :"<<endl;
    cout<<"1- heuristic.cpp     2- bruteforce.cpp "<<endl;
    cout<<"3- dp1.cpp           4- dp2.cpp "<<endl;
    cout << "0- Quitter le programme " << endl ;
    cout << "Choix : " ;
    cin >> choix ;

    switch (choix){

      case 0 :
        break ;

      case 1 : // On résoud le problème avec l'heuristic
        remplir_instance (inst) ;
        sol = solution_heuristique_trie (inst) ;

        cout << "Profit total = " << sol.profit_sol << endl ;
        cout << "Objets présents dans le sac : " << sol.id_objet[0] ;
        for (int i = 1 ; i < sol.id_objet.size() ; i ++){
          cout << " , " << sol.id_objet[i] ;
        }
        cout << endl ;
        cout << endl ;
        break ;

      case 2 : // On résoud le problème avec bruteforce
        remplir_instance (inst) ;
        sol = brute_force (inst) ;

        cout << "Profit total = " << sol.profit_sol << endl ;
        cout << "Objets présents dans le sac : " << sol.id_objet[0] ;
        for (int i = 1 ; i < sol.id_objet.size() ; i ++){
          cout << " , " << sol.id_objet[i] ;
        }
        cout << endl ;
        cout << endl ;
        break ;

      case 3 : // On résoud le problème avec le programme dynamique v1
        remplir_instance (inst) ;
        sol = dynamique_2 (inst) ;

        cout << "Profit total = " << sol.profit_sol << endl ;
        cout << "Objets présents dans le sac : " << sol.id_objet[0] ;
        for (int i = 1 ; i < sol.id_objet.size() ; i ++){
          cout << " , " << sol.id_objet[i] ;
        }
        cout << endl ;
        cout << endl ;
        break ;

      case 4 : // On résoud le problème avec le programme dynamique v2
        remplir_instance (inst) ;
        sol = solution_optimale (inst) ;

        cout << "Profit total = " << sol.profit_sol << endl ;
        cout << "Objets présents dans le sac : " << sol.id_objet[0] ;
        for (int i = 1 ; i < sol.id_objet.size() ; i ++){
          cout << " , " << sol.id_objet[i] ;
        }
        cout << endl ;
        cout << endl ;
        break ;

      default :
        cout << "Cas non valide" << endl ;
        break ;
    }
  } while (choix != 0) ;

  return 0;
}
