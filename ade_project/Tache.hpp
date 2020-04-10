//
//  Tache.hpp
//  ade_project
//
//  Created by Anthony Peres da Cruz on 11/03/2020.
//  Copyright © 2020 Anthony Peres da Cruz. All rights reserved.
//

#ifndef Tache_hpp
#define Tache_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include "Etape.hpp"

class Tache {

public:

    /* Constructeurs et destructeurs */
    Tache();
    Tache(char nom, int duree, std::list<Tache*> predecesseurs);
    ~Tache();

    /* Fonctions */
    void ajouterSuccesseur(Tache *successeur);
    void actualiserSuccesseur();
    void calculMargeTotale();
    void calculTacheCritique();
    void calculMargeLibre();
    void afficherModeGraphique();
    void __toString();
    
    /* Accesseurs */
    char getNom();
    int getDuree();
    int getNiveau();
    int getMargeTotale();
    int getMargeLibre();
    int getDateDebutPlusTot();
    int getDateDebutPlusTard();
    int getDateFinPlusTot();
    int getDateFinPlusTard();
    bool getCritique();
    std::list<Tache*> getPredecesseurs();
    std::list<Tache*> getSuccesseurs();
    Etape* getEtapeDebut();
    Etape* getEtapeFin();
    
    /* Mutateurs */
    void setNom(char nom);
    void setDuree(int duree);
    void setNiveau(int niveau);
    void setMargeTotale(int marge_totale);
    void setMargeLibre(int marge_libre);
    void setDateDebutPlusTot(int date);
    void setDateDebutPlusTard(int date);
    void setDateFinPlusTot(int date);
    void setDateFinPlusTard(int date);
    void setCritique(bool critique);
    void setPredecesseurs(std::list<Tache*> predecesseurs);
    void setSuccesseurs(std::list<Tache*> successeurs);
    void setEtapeDebut(Etape* etape);
    void setEtapeFin(Etape* etape);
    
private:

    /* Variables */
    char _nom;
    int _duree;
    int _niveau;
    int _marge_totale;
    int _marge_libre;
    bool _critique;
    std::list<Tache*> _predecesseurs;
    std::list<Tache*> _successeurs;
    Etape* _etape_debut;
    Etape* _etape_fin;
    
};

#endif /* Tache_hpp */
