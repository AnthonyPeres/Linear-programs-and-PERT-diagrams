//
//  ProgrammeLineaire.hpp
//  ade_project
//
//  Created by Anthony Peres da Cruz on 19/02/2020.
//  Copyright © 2020 Anthony Peres da Cruz. All rights reserved.
//

#ifndef ProgrammeLineaire_hpp
#define ProgrammeLineaire_hpp

#include <stdio.h>
#include <string>
#include <vector>

/*  Attention au respect de l'intervalle "reel", voir si on peut random un float. */

class ProgrammeLineaire {
    
public:

//  Constructeur et destructeur
    ProgrammeLineaire();
    ~ProgrammeLineaire();
    
//  Fonctions
    void init();
    void simplexe();
    
//  Les accesseurs
    float get_temps_resolution();
    int get_nb_variables_decisions();
    int get_nb_contraintes();
    int get_indice_colonne_pivot();
    int get_indice_ligne_pivot();
    int get_valeur_pivot();
    std::vector<int> get_profit();
    std::vector<std::vector<int>> get_matrice();
    std::vector<int> get_composantes_base();
    
//  Les mutateurs
    void set_temps_resolution(float t);
    void set_nb_variable_decisions(int n);
    void set_nb_contraintes(int c);
    void set_indice_colonne_pivot(int indice_colonne_pivot);
    void set_indice_ligne_pivot(int indice_ligne_pivot);
    void set_valeur_pivot(int valeur_pivot);
    void set_profit(std::vector<int> z);
    void set_matrice(std::vector<std::vector<int>> a);
    void set_composantes_base(std::vector<int> b);
    
private:

//  Les variables
    float _temps_resolution;
    int _nb_variables_decisions;
    int _nb_contraintes;
    int _indice_colonne_pivot;
    int _indice_ligne_pivot;
    int _valeur_pivot;
    std::vector<int> _vecteur_profit;
    std::vector<std::vector<int>> _matrice;
    std::vector<int> _composantes_base;
    
//  Fonctions de resolution
    void modifier_matrice();
    bool solution_optimale();
    void trouver_colonne_pivot();
    void trouver_pivot();
    void resoudre_pivot();
    
//  Les fonctions d'attribution de valeurs random
    int random_variables_decisions();
    int random_contraintes();
    int random_profit();
    int random_matrice();
    int random_base();
    
};

#endif /* ProgrammeLineaire_hpp */
