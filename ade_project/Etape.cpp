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
    this->_numero = numero;
}

/* Destructeur d'une etape. **/
Etape::~Etape() {

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
