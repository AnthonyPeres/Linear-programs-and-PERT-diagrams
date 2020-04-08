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
    ajouter_successeurs();
    approche_par_suppression();
    afficher_liste_taches();
    construction_graphe_initial();
}

Reseau::~Reseau() {
    
}

// Les fonctions

void Reseau::init_liste_taches() {
    
    // On recupere le tableau des taches dans le fichier ListeTaches.csv
    ifstream fichier("ade_project/ListeTaches.csv");
    if(fichier) {
        string ligne;
        
        while(getline(fichier, ligne)) {

            char nom = '\0';
            int duree = '\0';
            list<Tache*> antecedants;
            
            for (int i = 0; i < (int) ligne.size() ; ++i) {
                if(i == 0) {
                    // Premiere colonne : Le nom
                    nom = ligne[i];
                    
                } else if(i == 2) {
                    // Deuxieme colonne : La durée
                    char stTemp[2];
                    sprintf(stTemp,"%c", ligne[i]);
                    duree = atoi(stTemp);
                    
                } else if(i >= 4) {
                    // Ensuite : Les antecedants
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
//    int niveau = 0;
//    bool placement_effectue = false;
//
//    while (!placement_effectue) {
//        for (auto& tache : _liste_taches) {
//            if (!tache.get_niveau_place()) {
//
//                /* Dans le cas ou la tâche n'a pas d'antecedants */
//                if (tache.get_antecedants().size() == 0) {
//                    tache.set_niveau(niveau + 1);
//                    tache.set_niveau_place(true);
//
//
//                }
//
//                /* Dans le cas ou elle a des antecedants */
//                else {
//                    bool a_placer = true;
//                    for (auto&& antecedant : tache.get_antecedants()) {
//                        for (auto&& t : _liste_taches) {
//
//                            if(t.get_nom() == antecedant.get_nom()) {
//                                if(!t.get_niveau_place()) {
//                                    a_placer = false;
//                                }
//                                niveau = t.get_niveau();
//                            }
//                        }
//                    }
//
//                    if(a_placer == true) {
//                        tache.set_niveau(niveau + 1);
//                        tache.set_niveau_place(true);
//                    }
//                }
//
//                this->niveau_max = niveau + 1;
//            }
//        }
//
//        // Pour savoir si on sort de la boucle
//        placement_effectue = true;
//        for (auto& t : _liste_taches) {
//            if(t.get_niveau_place() == false) {
//                placement_effectue = false;
//            }
//        }
//    }
}


void Reseau::afficher_liste_taches() {
//    for (auto& tache : _liste_taches) {
//        cout << tache.get_nom() << " a une durée de : " << tache.get_duree();
//        cout << "   son niveau : " << tache.get_niveau();
//        cout << "   ces antecedants : ";
//        for (auto& a : tache.get_antecedants()) {
//            cout << a.get_nom() << "   ";
//        }
//        cout << "\n";
//
//    }
}

void Reseau::ajouter_successeurs() {
//    for(auto& tache : _liste_taches) {
//        for(auto& antecedant : tache.get_antecedants()) {
//            for(auto& t : _liste_taches) {
//                if(antecedant.get_nom() == t.get_nom()) {
//                    t.ajouter_successeur(tache);
//                }
//            }
//        }
//    }
}




void Reseau::construction_graphe_initial() {
    
    
    
//    
//    // Pour chaque niveaux
//    for(int i(1); i <= niveau_max; ++i) {
//        
//        for(auto& tache : _liste_taches) {
//            if(tache.get_niveau() == i) {
//             
//                
//            }
//        }
//    }
}

void Reseau::marges_totales() {
    
}

void Reseau::taches_critiques() {
    
}

void Reseau::chemins_critiques() {
    
}

void Reseau::sous_graphe_critique() {
    
}

void Reseau::marges_libres() {
    
}






