//
//  Etape.cpp
//  ade_project
//
//  Created by Anthony Peres da Cruz on 08/04/2020.
//  Copyright © 2020 Anthony Peres da Cruz. All rights reserved.
//

#include "Etape.hpp"

using namespace std;

// Constructeurs et destructeurs

Etape::Etape() {

}

Etape::Etape(int numero) {
    this->_numero = numero;
}

Etape::~Etape() {

}

// Accesseurs

int Etape::get_numero() {
    return this->_numero;
}

int Etape::get_date_plus_tot() {
    return this->_date_plus_tot;
}

int Etape::get_date_plus_tard() {
    return this->_date_plus_tard;
}

// Mutateurs

void Etape::set_numero(int numero) {
    this->_numero = numero;
}

void Etape::set_date_plus_tot(int date) {
    this->_date_plus_tot = date;
}

void Etape::set_date_plus_tard(int date) {
    this->_date_plus_tard = date;
}
