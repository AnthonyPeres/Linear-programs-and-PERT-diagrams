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

/* Constructeur par défaut d'une Tache. **/
Tache::Tache() {
    
}

/* Constructeur d'une tâche prennant des parametres.
 * @param nom : le nom de la tache.
 * @param duree : la durée de la tache.
 * @param predecesseurs : la liste des predecesseurs de la tache.
 **/
Tache::Tache(char nom, int duree, list<Tache *> predecesseurs) {
    this->_nom = nom;
    this->_duree = duree;
    this->_predecesseurs = predecesseurs;
    this->_etape_debut = NULL;
    this->_etape_fin = NULL;
    this->actualiserSuccesseur();
}

/* Destructeur d'une tâche. **/
Tache::~Tache() {
    
}

/* Fonctions */

/* Fonction permettant d'ajouter des successeurs.
 * @param *successeur : un successeur à ajouter.
 **/
void Tache::ajouterSuccesseur(Tache *successeur) {
    this->_successeurs.push_back(successeur);
}

/* Fonction permettant d'actualiser la liste des successeurs. **/
void Tache::actualiserSuccesseur() {
    for (auto& tache : this->getPredecesseurs()) {
        tache->ajouterSuccesseur(this);
    }
}

/* Fonction permettant de calculer la marge totale. **/
void Tache::calculMargeTotale() {
    this->_marge_totale = (this->getDateFinPlusTard() - this->getDateDebutPlusTot() - this->getDuree());
}

/* Fonction permettant de dire si la tâche est critique ou non. **/
void Tache::calculTacheCritique() {
    if(this->_marge_totale == 0) {
        this->setCritique(true);
    } else {
        this->setCritique(false);
    }
}

/* Fonction permettant de calculer la marge libre d'une tâche **/
void Tache::calculMargeLibre() {
    this->_marge_libre = this->getDateFinPlusTot() - this->getDateDebutPlusTot() - this->getDuree();
}

/* Fonction permettant d'afficher toutes les informations sur la tâche. **/
void Tache::__toString() {
    cout << "Tache " << this->getNom() << "  ---------------" << endl;
    cout << "|" << endl;
    cout << "|--> duree : " << this->getDuree() << endl;
    cout << "|--> marge totale : " << this->getMargeTotale() << endl;
    cout << "|--> marge libre : " << this->getMargeLibre() << endl;
    cout << "|--> critique : " << this->getCritique() << endl;
    cout << "|--> etape de debut : " << this->getEtapeDebut()->getNumero() << endl;
    cout << "|--> etape de fin : " << this->getEtapeFin()->getNumero() << endl;
    cout << "|--> date debut plus tot : " << this->getDateDebutPlusTot() << endl;
    cout << "|--> date debut plus tard : " << this->getDateDebutPlusTard() << endl;
    cout << "|--> date fin plus tot : " << this->getDateFinPlusTot() << endl;
    cout << "|--> date fin plus tard : " << this->getDateFinPlusTard() << endl;
    cout << "|--> Ses predecesseurs : ";
    for(auto& a : this->getPredecesseurs()) {
        cout << a->getNom() << " ";
    }
    cout << endl << "|--> Ses successeurs : ";
    for(auto& s : this->getSuccesseurs()) {
        cout << s->getNom() << "  ";
    }
    
}

/* Accesseurs */

char Tache::getNom() {
    return this->_nom;
}

int Tache::getDuree() {
    return this->_duree;
}

int Tache::getNiveau() {
    return this->_niveau;
}

int Tache::getMargeTotale() {
    return this->_marge_totale;
}

int Tache::getMargeLibre() {
    return this->_marge_libre;
}

int Tache::getDateDebutPlusTot() {
    return this->getEtapeDebut()->getDatePlusTot();
}

int Tache::getDateDebutPlusTard() {
    return this->getEtapeDebut()->getDatePlusTard();
}

int Tache::getDateFinPlusTot() {
    return this->getEtapeFin()->getDatePlusTot();
}

int Tache::getDateFinPlusTard() {
    return this->getEtapeFin()->getDatePlusTard();
}

bool Tache::getCritique() {
    return this->_critique;
}

list<Tache*> Tache::getPredecesseurs() {
    return this->_predecesseurs;
}

list<Tache*> Tache::getSuccesseurs() {
    return this->_successeurs;
}

Etape* Tache::getEtapeDebut() {
    return this->_etape_debut;
}

Etape* Tache::getEtapeFin() {
    return this->_etape_fin;
}

/* Mutateurs */

void Tache::setNom(char nom) {
    this->_nom = nom;
}

void Tache::setDuree(int duree) {
    this->_duree = duree;
}

void Tache::setNiveau(int niveau) {
    this->_niveau = niveau;
}

void Tache::setMargeTotale(int marge_totale) {
    this->_marge_totale = marge_totale;
}

void Tache::setMargeLibre(int marge_libre) {
    this->_marge_libre = marge_libre;
}

void Tache::setDateDebutPlusTot(int date) {
    this->getEtapeDebut()->setDatePlusTot(date);
}

void Tache::setDateDebutPlusTard(int date) {
    this->getEtapeDebut()->setDatePlusTard(date);
}

void Tache::setDateFinPlusTot(int date) {
    this->getEtapeFin()->setDatePlusTot(date);
}

void Tache::setDateFinPlusTard(int date) {
    this->getEtapeFin()->setDatePlusTard(date);
}

void Tache::setCritique(bool critique) {
    this->_critique = critique;
}

void Tache::setPredecesseurs(list<Tache*> predecesseurs) {
    this->_predecesseurs = predecesseurs;
}

void Tache::setSuccesseurs(list<Tache*> successeurs) {
    this->_successeurs = successeurs;
}

void Tache::setEtapeDebut(Etape* etape) {
    this->_etape_debut = etape;
}

void Tache::setEtapeFin(Etape* etape) {
    this->_etape_fin = etape;
}
