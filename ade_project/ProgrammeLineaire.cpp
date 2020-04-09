//
//  ProgrammeLineaire.cpp
//  ade_project
//
//  Created by Anthony Peres da Cruz on 19/02/2020.
//  Copyright © 2020 Anthony Peres da Cruz. All rights reserved.
//

#include "ProgrammeLineaire.hpp"

using namespace std;

// Les constantes

const int MAX_VAR_DECISION = 1000;
const int MIN_VAR_DECISION = 100;
const int MAX_CONTRAINTES = 100;
const int MIN_CONTRAINTES = 5;
const int MAX_VALEUR_PROFIT = 50;
const int MIN_VALEUR_PROFIT = 0;
const int MAX_VALEUR_MATRICE = 10;
const int MIN_VALEUR_MATRICE = 0;
const int MAX_VALEUR_BASE = 25;
const int MIN_VALEUR_BASE = 2;

// Constructeur et destructeur

ProgrammeLineaire::ProgrammeLineaire() {
    init();
    simplexe();
}

ProgrammeLineaire::~ProgrammeLineaire() {}

/* Fonctions */

/* Fonction qui crée les PLC **/
void ProgrammeLineaire::init() {
    
    _nb_variables_decisions = randomVariablesDecisions();
    _nb_contraintes = randomContraintes();
    
    for (int i = 0; i < _nb_variables_decisions; ++i) {
        _vecteur_profit.push_back(randomProfit());
    }
    
    for (int j(0); j < _nb_contraintes; ++j) {
        vector<int> ligne;
        
        for (int k(0); k < _nb_variables_decisions ; ++k) {
            ligne.push_back(randomMatrice());
        }
        
        _matrice.push_back(ligne);
        _composantes_base.push_back(randomBase());
    }
}

/* Fonction qui effectue la méthode du simplexe. **/
void ProgrammeLineaire::simplexe() {
    
    // La gestion du temps
    float temps;
    clock_t t1, t2;
    
    // Avant la résolution, on regarde l'heure
    t1 = clock();
    
    modifierMatrice();
    do {
        trouverColonnePivot();
        trouverPivot();
        resoudrePivot();
    } while (solutionOptimale());
    
    // On regarde l'heure apres résolution
    t2 = clock();
    
    // On compare t1 et t2 pour avoir le temps d'execution de la résolution
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    
    // On attribut un temps de résolution au plc choisi
    _temps_resolution = temps;
}

/* Fonction qui modifie la matrice afin de l'adapter pour la méthode du simplexe. **/
void ProgrammeLineaire::modifierMatrice() {
    
    vector<vector<int>> matrice_simplexe;
    vector<int> profit = getProfit();
    
    for (int c(0); c < getNombreContraintes(); ++c) {
        
        vector<int> ligne = getMatrice()[c];
        
        for (int i(0); i < this->getNombreContraintes(); ++i) {
            if(c == i){ ligne.push_back(1); }
            else { ligne.push_back(0); }
        }
        
        ligne.push_back(getComposanteBase()[c]);
        matrice_simplexe.push_back(ligne);
        profit.push_back(0);
    }
    
    profit.push_back(0);
    matrice_simplexe.push_back(profit);
    this->setMatrice(matrice_simplexe);
}

/* Fonction qui verifie si la soluton est optimale. **/
bool ProgrammeLineaire::solutionOptimale() {
    
    vector<int> Z = _matrice[_matrice.size() - 1];
    int val_Z = Z[getIndiceColonnePivot()];
    
    if(val_Z <= 0)
        return true;
    return false;
}

/* Fonction qui trouve la colonne du pivot. **/
void ProgrammeLineaire::trouverColonnePivot() {
    
    int indice_ligne = 0,
        indice_case = 0,
        indice_colonne_pivot = 0,
        plus_grand = 0;
    
    for(auto& ligne : _matrice) {
        if (indice_ligne == (int)_matrice.size() - 1) {
            for(auto& c : ligne) {
                if(c > plus_grand) {
                    plus_grand = c;
                    indice_colonne_pivot = indice_case;
                }
                indice_case++;
            }
        }
        indice_ligne++;
        indice_case = 0;
    }
    
    this->setIndiceColonnePivot(indice_colonne_pivot);
}

/* Fonction qui trouve le pivot. **/
void ProgrammeLineaire::trouverPivot() {
    int x = 1,
        b = 1,
        indice_ligne = 0,
        indice_colonne = 0;
    
    double minimum = 100000;
    
    for(auto& ligne : _matrice) {
        for (auto& c : ligne) {
            if(indice_colonne == this->getIndiceColonnePivot())
                x = c;
            
            if(indice_colonne == (int) ligne.size() - 1)
                b = c;
            
            if(((double)b / (double)x) < minimum) {
                minimum = (double)b / (double)x;
                this->setValeurProfit(x);
                this->setIndiceLignePivot(indice_ligne);
            }
            indice_colonne++;
        }
        indice_colonne = 0;
        indice_ligne++;
    }
}

/* Fonction qui résoud le pivot. **/
void ProgrammeLineaire::resoudrePivot() {
    
    int indice_ligne = 0, indice_case = 0;
    vector<int> ligne_pivot = _matrice[getIndiceLignePivot()];
    
    for(auto& ligne : _matrice) {
        for(auto& c : ligne) {
            if(indice_ligne == this->getIndiceLignePivot()) {
                if(indice_case == this->getIndiceColonnePivot()) {
                    c = 1;
                 } else {
                    c /= this->getValeurPivot();
                 }
                
                
             } else {
                 if(indice_case == this->getIndiceColonnePivot()) {
                     c = 0;
                 } else {
                     int a = ligne[this->getIndiceColonnePivot()];
                     int b = ligne_pivot[indice_case];
                     int p = this->getValeurPivot();
                     c = (a * b) / p;
                 }
             }
            indice_case++;
        }
        indice_ligne++;
        indice_case = 0;
    }
}

/* Les accesseurs */

float ProgrammeLineaire::getTempsResolution() {
    return this->_temps_resolution;
}

int ProgrammeLineaire::getNombreVarDecisions() {
    return this->_nb_variables_decisions;
}

int ProgrammeLineaire::getNombreContraintes() {
    return this->_nb_contraintes;
}

int ProgrammeLineaire::getIndiceColonnePivot() {
    return _indice_colonne_pivot;
}

int ProgrammeLineaire::getIndiceLignePivot() {
    return _indice_ligne_pivot;
}

int ProgrammeLineaire::getValeurPivot() {
    return _valeur_pivot;
}

vector<int> ProgrammeLineaire::getProfit() {
    return this->_vecteur_profit;
}

vector<vector<int> > ProgrammeLineaire::getMatrice() {
    return this->_matrice;
}

vector<int> ProgrammeLineaire::getComposanteBase() {
    return this->_composantes_base;
}

/* Les mutateurs */

void ProgrammeLineaire::setTempsResolution(float t) {
    this->_temps_resolution = t;
}

void ProgrammeLineaire::setNombreVarDecisions(int n) {
    this->_nb_variables_decisions = n;
}

void ProgrammeLineaire::setNombreContraintes(int c) {
    this->_nb_contraintes = c;
}

void ProgrammeLineaire::setIndiceColonnePivot(int indice_colonne_pivot) {
    this->_indice_colonne_pivot = indice_colonne_pivot;
}

void ProgrammeLineaire::setIndiceLignePivot(int indice_ligne_pivot) {
    this->_indice_ligne_pivot = indice_ligne_pivot;
}

void ProgrammeLineaire::setValeurProfit(int valeur_pivot) {
    this->_valeur_pivot = valeur_pivot;
}

void ProgrammeLineaire::setProfit(vector<int> z) {
    this->_vecteur_profit = z;
}

void ProgrammeLineaire::setMatrice(vector<vector<int> > a) {
    this->_matrice = a;
}

void ProgrammeLineaire::setComposanteBase(vector<int> b) {
    this->_composantes_base = b;
}

/* Les fonctions d'attribution de valeurs */

int ProgrammeLineaire::randomVariablesDecisions() {
    return rand()%(MAX_VAR_DECISION-MIN_VAR_DECISION)+MIN_VAR_DECISION;
}

int ProgrammeLineaire::randomContraintes() {
    return rand()%(MAX_CONTRAINTES-MIN_CONTRAINTES)+MIN_CONTRAINTES;
}

int ProgrammeLineaire::randomProfit() {
    return rand()%(MAX_VALEUR_PROFIT-MIN_VALEUR_PROFIT)+MIN_VALEUR_PROFIT;
}

int ProgrammeLineaire::randomMatrice() {
    return rand()%(MAX_VALEUR_MATRICE-MIN_VALEUR_MATRICE)+MIN_VALEUR_MATRICE;
}

int ProgrammeLineaire::randomBase() {
    return rand()%(MAX_VALEUR_BASE-MIN_VALEUR_BASE)+MIN_VALEUR_BASE;
}
