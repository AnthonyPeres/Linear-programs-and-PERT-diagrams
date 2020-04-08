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

class Tache {

public:

    // Constructeurs et destructeurs
    Tache();
    Tache(char nom, int duree, std::list<Tache*> antecedants);
    ~Tache();
    
    // Fonctions
    void ajouter_antecedant(Tache *antecedant);
    void ajouter_successeur(Tache *successeur);
    
    // Accesseurs
    char get_nom();
    int get_duree();
    int get_niveau();
    int get_marge_totale();
    bool get_niveau_place();
    bool get_critique();
    int get_date_debut_plus_tot();
    int get_date_debut_plus_tard();
    int get_date_fin_plus_tot();
    int get_date_fin_plus_tard();
    std::list<Tache*> get_antecedants();
    std::list<Tache*> get_successeurs();
    
    // Mutateurs
    void set_nom(char nom);
    void set_duree(int duree);
    void set_niveau(int niveau);
    void set_marge_totale(int marge_totale);
    void set_niveau_place(bool niveau_place);
    void set_critique(bool critique);
    void set_date_debut_plus_tot(int date);
    void set_date_debut_plus_tard(int date);
    void set_date_fin_plus_tot(int date);
    void set_date_fin_plus_tard(int date);
    void set_antecedants(std::list<Tache*> antecedants);
    void set_successeurs(std::list<Tache*> successeurs);

private:

    // Variables
    char _nom;
    int _duree;
    int _niveau;
    int _marge_totale;
    bool _niveau_place;
    bool _critique;
    int _date_debut_plus_tot;
    int _date_debut_plus_tard;
    int _date_fin_plus_tot;
    int _date_fin_plus_tard;
    std::list<Tache*> _antecedants;
    std::list<Tache*> _successeurs;
    
};

#endif /* Tache_hpp */
