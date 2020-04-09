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

    /*  Constructeur et destructeur */
    ProgrammeLineaire();
    ~ProgrammeLineaire();
    
    /* Fonctions */
    void init();
    void simplexe();
    
    /* Les accesseurs */
    float getTempsResolution();
    int getNombreVarDecisions();
    int getNombreContraintes();
    int getIndiceColonnePivot();
    int getIndiceLignePivot();
    int getValeurPivot();
    std::vector<int> getProfit();
    std::vector<std::vector<int>> getMatrice();
    std::vector<int> getComposanteBase();
    
    /* Les mutateurs */
    void setTempsResolution(float t);
    void setNombreVarDecisions(int n);
    void setNombreContraintes(int c);
    void setIndiceColonnePivot(int indice_colonne_pivot);
    void setIndiceLignePivot(int indice_ligne_pivot);
    void setValeurProfit(int valeur_pivot);
    void setProfit(std::vector<int> z);
    void setMatrice(std::vector<std::vector<int>> a);
    void setComposanteBase(std::vector<int> b);
    
private:

    /* Variables */
    float _temps_resolution;
    int _nb_variables_decisions;
    int _nb_contraintes;
    int _indice_colonne_pivot;
    int _indice_ligne_pivot;
    int _valeur_pivot;
    std::vector<int> _vecteur_profit;
    std::vector<std::vector<int>> _matrice;
    std::vector<int> _composantes_base;
    
    /* Fonctions de resolution */
    void modifierMatrice();
    bool solutionOptimale();
    void trouverColonnePivot();
    void trouverPivot();
    void resoudrePivot();
    
    /* Les fonctions d'attribution de valeurs random */
    int randomVariablesDecisions();
    int randomContraintes();
    int randomProfit();
    int randomMatrice();
    int randomBase();
    
};

#endif /* ProgrammeLineaire_hpp */
