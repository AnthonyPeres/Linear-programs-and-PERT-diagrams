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
#include "Tache.hpp"

class Etape {
    
public:
    
    // Constructeur et destructeur
    Etape();
    ~Etape();
    
    // Accesseurs
    int get_numero();
    int get_date_plus_tot();
    int get_date_plus_tard();
    std::list<Tache*> get_taches_entrees();
    std::list<Tache*> get_taches_sorties();
    
    // Mutateurs
    void set_numero(int numero);
    void set_date_plus_tot(int date);
    void set_date_plus_tard(int date);
    void set_taches_entrees(std::list<Tache*> taches);
    void set_taches_sorties(std::list<Tache*> taches);
    
private:
    
    int _numero;
    int _date_plus_tot;
    int _date_plus_tard;
    std::list<Tache*> _taches_entrees;
    std::list<Tache*> _taches_sorties;
    
    
};



#endif /* Etape_hpp */
