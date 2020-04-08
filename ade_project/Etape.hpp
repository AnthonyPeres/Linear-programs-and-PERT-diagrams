//
//  Etape.hpp
//  ade_project
//
//  Created by Anthony Peres da Cruz on 11/03/2020.
//  Copyright © 2020 Anthony Peres da Cruz. All rights reserved.
//

#ifndef Etape_hpp
#define Etape_hpp

#include <stdio.h>

class Etape {

public:

    Etape();
    Etape(int numero);
    ~Etape();

private:

    int _numero;
    int _coordonnee_x;
    int _coordonnee_y;
    int _date_plus_tot;
    int _date_plus_tard;
    int _marge;

};

#endif /* Etape_hpp */
