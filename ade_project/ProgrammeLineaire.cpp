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

const int MAX_VAR_DECISION = 100;
const int MIN_VAR_DECISION = 10;
const int MAX_CONTRAINTES = 10;
const int MIN_CONTRAINTES = 5;
const int MAX_VALEUR_PROFIT = 50;
const int MIN_VALEUR_PROFIT = 0;
const int MAX_VALEUR_MATRICE = 100;
const int MIN_VALEUR_MATRICE = 0;
const int MAX_VALEUR_BASE = 250;
const int MIN_VALEUR_BASE = 25;

// Constructeur et destructeur

ProgrammeLineaire::ProgrammeLineaire() {
    init();
    simplexe();
}

ProgrammeLineaire::~ProgrammeLineaire() {}

// Fonction d'initialisation du PLC

void ProgrammeLineaire::init() {
    
    _nb_variables_decisions = random_variables_decisions();
    _nb_contraintes = random_contraintes();
    
    for (int i = 0; i < _nb_variables_decisions; ++i) {
        _vecteur_profit.push_back(random_profit());
    }
    
    for (int j(0); j < _nb_contraintes; ++j) {
        vector<int> ligne;
        
        for (int k(0); k < _nb_variables_decisions ; ++k) {
            ligne.push_back(random_matrice());
        }
        
        _matrice.push_back(ligne);
        _composantes_base.push_back(random_base());
    }
}

// Fonctions de resolution

void ProgrammeLineaire::simplexe() {
    
    // La gestion du temps
    float temps;
    clock_t t1, t2;
    
    // Avant la résolution, on regarde l'heure
    t1 = clock();
    
    modifier_matrice();
    do {
        trouver_colonne_pivot();
        trouver_pivot();
        resoudre_pivot();
    } while (solution_optimale());
    
    // On regarde l'heure apres résolution
    t2 = clock();
    
    // On compare t1 et t2 pour avoir le temps d'execution de la résolution
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    
    // On attribut un temps de résolution au plc choisi
    _temps_resolution = temps;
}

void ProgrammeLineaire::modifier_matrice() {
    
    vector<vector<int>> matrice_simplexe;
    vector<int> profit = get_profit();
    
    for (int c(0); c < get_nb_contraintes(); ++c) {
        
        vector<int> ligne = get_matrice()[c];
        
        for (int i(0); i < this->get_nb_contraintes(); ++i) {
            if(c == i){ ligne.push_back(1); }
            else { ligne.push_back(0); }
        }
        
        ligne.push_back(get_composantes_base()[c]);
        matrice_simplexe.push_back(ligne);
        profit.push_back(0);
    }
    
    profit.push_back(0);
    matrice_simplexe.push_back(profit);
    this->set_matrice(matrice_simplexe);
}

bool ProgrammeLineaire::solution_optimale() {
    
    vector<int> Z = _matrice[_matrice.size() - 1];
    int val_Z = Z[get_indice_colonne_pivot()];
    
    if(val_Z <= 0)
        return true;
    return false;
}

void ProgrammeLineaire::trouver_colonne_pivot() {
    
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
    
    this->set_indice_colonne_pivot(indice_colonne_pivot);
}

void ProgrammeLineaire::trouver_pivot() {
    
    int x = 1,
        b = 1,
        indice_ligne = 0,
        indice_colonne = 0;
    
    double minimum = 100000;
    
    for(auto& ligne : _matrice) {
        for (auto& c : ligne) {
            if(indice_colonne == this->get_indice_colonne_pivot())
                x = c;
            
            if(indice_colonne == (int) ligne.size() - 1)
                b = c;
            
            if(((double)b / (double)x) < minimum) {
                minimum = (double)b / (double)x;
                this->set_valeur_pivot(x);
                this->set_indice_ligne_pivot(indice_ligne);
            }
            indice_colonne++;
        }
        indice_colonne = 0;
        indice_ligne++;
    }
}

void ProgrammeLineaire::resoudre_pivot() {
    
    int indice_ligne = 0, indice_case = 0;
    vector<int> ligne_pivot = _matrice[get_indice_ligne_pivot()];
    
    for(auto& ligne : _matrice) {
        for(auto& c : ligne) {
            if(indice_ligne == this->get_indice_ligne_pivot()) {
                if(indice_case == this->get_indice_colonne_pivot()) {
                    c = 1;
                 } else {
                    c /= this->get_valeur_pivot();
                 }
                
                
             } else {
                 if(indice_case == this->get_indice_colonne_pivot()) {
                     c = 0;
                 } else {
                     int a = ligne[this->get_indice_colonne_pivot()];
                     int b = ligne_pivot[indice_case];
                     int p = this->get_valeur_pivot();
                     c = (a * b) / p;
                 }
             }
            indice_case++;
        }
        indice_ligne++;
        indice_case = 0;
    }
}

// Les accesseurs

float ProgrammeLineaire::get_temps_resolution() {
    return this->_temps_resolution;
}

int ProgrammeLineaire::get_nb_variables_decisions() {
    return this->_nb_variables_decisions;
}

int ProgrammeLineaire::get_nb_contraintes() {
    return this->_nb_contraintes;
}

int ProgrammeLineaire::get_indice_colonne_pivot() {
    return _indice_colonne_pivot;
}

int ProgrammeLineaire::get_indice_ligne_pivot() {
    return _indice_ligne_pivot;
}

int ProgrammeLineaire::get_valeur_pivot() {
    return _valeur_pivot;
}

std::vector<int> ProgrammeLineaire::get_profit() {
    return this->_vecteur_profit;
}

std::vector<std::vector<int> > ProgrammeLineaire::get_matrice() {
    return this->_matrice;
}

std::vector<int> ProgrammeLineaire::get_composantes_base() {
    return this->_composantes_base;
}

// Les mutateurs

void ProgrammeLineaire::set_temps_resolution(float t) {
    this->_temps_resolution = t;
}

void ProgrammeLineaire::set_nb_variable_decisions(int n) {
    this->_nb_variables_decisions = n;
}

void ProgrammeLineaire::set_nb_contraintes(int c) {
    this->_nb_contraintes = c;
}

void ProgrammeLineaire::set_indice_colonne_pivot(int indice_colonne_pivot) {
    this->_indice_colonne_pivot = indice_colonne_pivot;
}

void ProgrammeLineaire::set_indice_ligne_pivot(int indice_ligne_pivot) {
    this->_indice_ligne_pivot = indice_ligne_pivot;
}

void ProgrammeLineaire::set_valeur_pivot(int valeur_pivot) {
    this->_valeur_pivot = valeur_pivot;
}

void ProgrammeLineaire::set_profit(std::vector<int> z) {
    this->_vecteur_profit = z;
}

void ProgrammeLineaire::set_matrice(std::vector<std::vector<int> > a) {
    this->_matrice = a;
}

void ProgrammeLineaire::set_composantes_base(std::vector<int> b) {
    this->_composantes_base = b;
}

    // Les fonctions d'attribution de valeurs

int ProgrammeLineaire::random_variables_decisions() {
    return rand()%(MAX_VAR_DECISION-MIN_VAR_DECISION)+MIN_VAR_DECISION;
}

int ProgrammeLineaire::random_contraintes() {
    return rand()%(MAX_CONTRAINTES-MIN_CONTRAINTES)+MIN_CONTRAINTES;
}

int ProgrammeLineaire::random_profit() {
    return rand()%(MAX_VALEUR_PROFIT-MIN_VALEUR_PROFIT)+MIN_VALEUR_PROFIT;
}

int ProgrammeLineaire::random_matrice() {
    return rand()%(MAX_VALEUR_MATRICE-MIN_VALEUR_MATRICE)+MIN_VALEUR_MATRICE;
}

int ProgrammeLineaire::random_base() {
    return rand()%(MAX_VALEUR_BASE-MIN_VALEUR_BASE)+MIN_VALEUR_BASE;
}
