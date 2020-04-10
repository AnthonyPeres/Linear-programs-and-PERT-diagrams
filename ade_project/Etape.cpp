//
//  Etape.cpp
//  ade_project
//
//  Created by Anthony Peres da Cruz on 08/04/2020.
//  Copyright © 2020 Anthony Peres da Cruz. All rights reserved.
//

#include "Etape.hpp"

using namespace std;

/* Constructeurs et destructeurs */

/* Constructeur par defaut d'une Etape. **/
Etape::Etape() {

}

/* Constructeur d'une étape prennant des parametres.
 * @param numero : le numero de la tache.
 **/
Etape::Etape(int numero) {
    this->_date_plus_tot = -1;
    this->_date_plus_tard = -1;
    this->_numero = numero;
}

/* Destructeur d'une etape. **/
Etape::~Etape() {

}

/* Fonctions */

/* Fonction qui simule l'affichage graphique. **/
void Etape::affichageModeGraphique() {
    if(this->getDatePlusTot() == -1) {
        cout << this->getNumero();
    } else {
        cout << " ";
        if(this->getDatePlusTard() == -1) {
            cout << this->getNumero() << " " << this->getDatePlusTot();
        } else {
            cout << this->getNumero() << " " << this->getDatePlusTot() << "|" << this->getDatePlusTard();
        }
    }
}

/* Accesseurs */

int Etape::getNumero() {
    return this->_numero;
}

int Etape::getDatePlusTot() {
    return this->_date_plus_tot;
}

int Etape::getDatePlusTard() {
    return this->_date_plus_tard;
}

// Mutateurs

void Etape::setNumero(int numero) {
    this->_numero = numero;
}

void Etape::setDatePlusTot(int date) {
    this->_date_plus_tot = date;
}

void Etape::setDatePlusTard(int date) {
    this->_date_plus_tard = date;
}
