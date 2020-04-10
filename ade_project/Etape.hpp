//
//  Etape.hpp
//  ade_project
//
//  Created by Anthony Peres da Cruz on 08/04/2020.
//  Copyright © 2020 Anthony Peres da Cruz. All rights reserved.
//

#ifndef Etape_hpp
#define Etape_hpp

#include <stdio.h>
#include <iostream>

class Etape {
    
public:
    
    /* Constructeur et destructeur */
    Etape();
    Etape(int numero);
    ~Etape();
    
    /* Fonctions */
    void affichageModeGraphique();
    
    /* Accesseurs */
    int getNumero();
    int getDatePlusTot();
    int getDatePlusTard();
    
    /* Mutateurs */
    void setNumero(int numero);
    void setDatePlusTot(int date);
    void setDatePlusTard(int date);
    
private:
    
    /* Variables */
    int _numero;
    int _date_plus_tot;
    int _date_plus_tard;
    
};

#endif /* Etape_hpp */
