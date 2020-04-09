//
//  Donnees.hpp
//  ade_project
//
//  Created by Anthony Peres da Cruz on 19/02/2020.
//  Copyright © 2020 Anthony Peres da Cruz. All rights reserved.
//

#ifndef Donnees_hpp
#define Donnees_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include "ProgrammeLineaire.hpp"


class GestionnaireDonnee {
    
public:
    
//  Constructeur et destructeur
    GestionnaireDonnee();
    ~GestionnaireDonnee();

//  Les fonctions
    void ecrirePLC(std::vector<ProgrammeLineaire> liste_plc);
    void ecrireResultats(std::vector<ProgrammeLineaire> liste_plc);
    
};

#endif /* Donnees_hpp */
