//
//  Reseau.cpp
//  ade_project
//
//  Created by Anthony Peres da Cruz on 11/03/2020.
//  Copyright © 2020 Anthony Peres da Cruz. All rights reserved.
//

#include "Reseau.hpp"

using namespace std;


Reseau::Reseau() {
    init_liste_taches();
    approche_par_suppression();
    ordonnancement_au_plus_tot();
}

Reseau::~Reseau() {
    
}

// Les fonctions

void Reseau::init_liste_taches() {
    
    ifstream fichier("ade_project/ListeTaches.csv");
    if(fichier) {
        
        string ligne;
        
        while(getline(fichier, ligne)) {

            char nom = '\0';
            int duree = '\0';
            list<Tache*> antecedants;
            
            for (int i = 0; i < (int) ligne.size() ; ++i) {
                if(i == 0) {
                    nom = ligne[i];
                    
                } else if(i == 2) {
                    char stTemp[2];
                    sprintf(stTemp,"%c", ligne[i]);
                    duree = atoi(stTemp);
                    
                } else if(i >= 4) {
                    for (auto &tache : _liste_taches) {
                        if(ligne[i] == tache->get_nom()) {
                            antecedants.push_back(tache);
                        }
                    }
                }
            }
            
            // On creer et on ajoute la tache a la liste
            Tache *t = new Tache(nom, duree, antecedants);
            this->_liste_taches.push_back(t);
        }
        
        fichier.close();
        
    } else {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }
}

void Reseau::approche_par_suppression() {
    int niveau = 0;
    bool placement_effectue = false;

    while (!placement_effectue) {
        
        for (auto& tache : _liste_taches) {
            if (!tache->get_niveau_place()) {
                
                if (tache->get_antecedants().size() == 0) {
                    
                    tache->set_niveau(niveau + 1);
                    tache->set_niveau_place(true);
                } else {
                    
                    bool a_placer = true;
                    for (auto& antecedant : tache->get_antecedants()) {
                        if(!antecedant->get_niveau_place()) {
                            a_placer = false;
                        } else {
                            niveau = antecedant->get_niveau();
                        }
                    }

                    if(a_placer == true) {
                        tache->set_niveau(niveau + 1);
                        tache->set_niveau_place(true);
                    }
                }
            }
        }

        // Pour savoir si on sort de la boucle
        placement_effectue = true;
        for (auto& t : _liste_taches) {
            if(t->get_niveau_place() == false) {
                placement_effectue = false;
            }
        }
    }
}



// Permet le calcul des plus loongs chemins (en utilisant la programmation dynamique)
void Reseau::ordonnancement_au_plus_tot() {
    
    // On met toutes les dates au plus tot à -1
    for(auto& tache : _liste_taches) {
        tache->set_date_debut_plus_tot(-1);
        tache->set_date_fin_plus_tard(-1);
    }
    
    // La premiere tache a une date au plus tot de 0
    _liste_taches.front()->set_date_debut_plus_tot(0);
    _liste_taches.front()->set_date_fin_plus_tot(0 + _liste_taches.front()->get_duree());
    
    for (auto& tache : _liste_taches) {
        
        int date_plus_tot = 0;
            
        for (auto& predecesseur : tache->get_antecedants()) {
        
            if (tache->get_date_debut_plus_tot() == -1 && predecesseur->get_date_debut_plus_tot() > -1) {
                if ((predecesseur->get_date_debut_plus_tot() + predecesseur->get_duree()) > date_plus_tot) {
                    date_plus_tot = predecesseur->get_date_debut_plus_tot() + predecesseur->get_duree();
                }
            }
        }
            
        tache->set_date_debut_plus_tot(date_plus_tot);
        tache->set_date_fin_plus_tot((int) (tache->get_date_debut_plus_tot() + tache->get_duree()));
    
    }
    
}

void Reseau::ordonnancement_au_plus_tard() {
    
    // On met toutes les dates au plus tard au max
    for (auto& tache : _liste_taches) {
        tache->set_date_debut_plus_tard(INT_MAX);
    }
    
    // La derniere tâche :
    
    
}
