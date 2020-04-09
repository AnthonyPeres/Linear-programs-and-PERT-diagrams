//
//  Tache.cpp
//  ade_project
//
//  Created by Anthony Peres da Cruz on 11/03/2020.
//  Copyright © 2020 Anthony Peres da Cruz. All rights reserved.
//

#include "Tache.hpp"

using namespace std;

// Constructeurs et destructeurs

Tache::Tache() {
    
}

Tache::Tache(char nom, int duree, std::list<Tache *> antecedants) {
    this->_nom = nom;
    this->_duree = duree;
    this->_antecedants = antecedants;
    this->actualiser_successeurs();
    this->_etape_debut = NULL;
    this->_etape_fin = NULL;
}

Tache::~Tache() {
    
}

// Fonctions

void Tache::ajouter_antecedant(Tache *antecedant) {
    this->_antecedants.push_back(antecedant);
}

void Tache::ajouter_successeur(Tache *successeur) {
    this->_successeurs.push_back(successeur);
}

void Tache::actualiser_successeurs() {
    for(std::list<Tache*>::iterator it = this->_antecedants.begin(); it!=this->_antecedants.end(); ++it) {
        (*it)->ajouter_successeur(this);
    }
}

void Tache::calcul_marge_totale() {
    this->_marge_totale = this->get_date_fin_plus_tard() - this->get_date_debut_plus_tot() - this->get_duree();
}


// Accesseurs

char Tache::get_nom() {
    return this->_nom;
}

int Tache::get_duree() {
    return this->_duree;
}

int Tache::get_niveau() {
    return this->_niveau;
}

int Tache::get_marge_totale() {
    return this->_marge_totale;
}

bool Tache::get_critique() {
    return this->_critique;
}

std::list<Tache*> Tache::get_antecedants() {
    return this->_antecedants;
}

std::list<Tache*> Tache::get_successeurs() {
    return this->_successeurs;
}

Etape* Tache::get_etape_debut() {
    return this->_etape_debut;
}

Etape* Tache::get_etape_fin() {
    return this->_etape_fin;
}

// Mutateurs

void Tache::set_nom(char nom) {
    this->_nom = nom;
}

void Tache::set_duree(int duree) {
    this->_duree = duree;
}

void Tache::set_niveau(int niveau) {
    this->_niveau = niveau;
}

void Tache::set_marge_totale(int marge_totale) {
    this->_marge_totale = marge_totale;
}

void Tache::set_critique(bool critique) {
    this->_critique = critique;
}


void Tache::set_antecedants(std::list<Tache*> antecedants) {
    this->_antecedants = antecedants;
}

void Tache::set_successeurs(std::list<Tache*> successeurs) {
    this->_successeurs = successeurs;
}

void Tache::set_etape_debut(Etape* etape) {
    this->_etape_debut = etape;
}

void Tache::set_etape_fin(Etape* etape) {
    this->_etape_fin = etape;
}

int Tache::get_date_debut_plus_tot() {
    return this->get_etape_debut()->get_date_plus_tot();
}

int Tache::get_date_debut_plus_tard() {
    return this->get_etape_debut()->get_date_plus_tard();
}

int Tache::get_date_fin_plus_tot() {
    return this->get_etape_fin()->get_date_plus_tot();
}

int Tache::get_date_fin_plus_tard() {
    return this->get_etape_fin()->get_date_plus_tard();
}

void Tache::set_date_debut_plus_tot(int date) {
    this->get_etape_debut()->set_date_plus_tot(date);
}

void Tache::set_date_debut_plus_tard(int date) {
    this->get_etape_debut()->set_date_plus_tard(date);
}

void Tache::set_date_fin_plus_tot(int date) {
    this->get_etape_fin()->set_date_plus_tot(date);
}

void Tache::set_date_fin_plus_tard(int date) {
    this->get_etape_fin()->set_date_plus_tard(date);
}

