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
#include "Tache.hpp"
#include "Etape.hpp"
#include "Structures.hpp"

class Reseau {
				
public:
    
    /* Constructeurs et destructeurs */
    Reseau();
    ~Reseau();

private:
    
    /* Fonctions */
    void initListeTaches();
    void approcheParSuppresion();
    void constructionGrapheInitial();
    void ordonnancementPlusTot();
    void ordonnancementPlusTard();
    void executerCalculs();
    void verifierDonnees();
    void testerDonneesTaches(Tache* t, Donnees data);
    
				/* Affichage */
				void afficherResultats();
				void afficherGraphe();
				
    /* Variables */
    std::list<Tache*> _liste_taches;
    std::list<Etape*> _liste_etapes;			
    std::list<Tache*> _liste_taches_chemin_critique;
};

#endif /* Reseau_hpp */
