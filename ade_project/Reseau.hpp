//
//  Reseau.hpp
//  ade_project
//
//  Created by Anthony Peres da Cruz on 11/03/2020.
//  Copyright © 2020 Anthony Peres da Cruz. All rights reserved.
//

#ifndef Reseau_hpp
#define Reseau_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include "Etape.hpp"
#include "Tache.hpp"

class Reseau {

public:
    
    // Constructeurs et destructeurs
    Reseau();
    ~Reseau();

private:
    
    // Fonctions
    void init_liste_taches();
    void ajouter_successeurs();
    void afficher_liste_taches();
    void approche_par_suppression();
    void construction_graphe_initial();
    void marges_totales();
    void taches_critiques();
    void chemins_critiques();
    void sous_graphe_critique();
    void marges_libres();
        
    // Les variables
    std::list<Tache*> _liste_taches;
    std::list<Etape*> _liste_etapes;
    std::vector<Tache*> _chemin_critique();

};

#endif /* Reseau_hpp */
