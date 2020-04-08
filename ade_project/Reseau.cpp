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
    construction_graphe_initial();
    ordonnancement_au_plus_tot();
    ordonnancement_au_plus_tard();
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

    for(auto& tache : _liste_taches) {
        tache->set_niveau(-1);
    }
    
    while (!placement_effectue) {
        
        for (auto& tache : _liste_taches) {
            if (tache->get_niveau() == -1) {
                
                if (tache->get_antecedants().size() == 0) {
                    tache->set_niveau(niveau + 1);
                } else {
                    
                    bool a_placer = true;
                    for (auto& antecedant : tache->get_antecedants()) {
                        if(antecedant->get_niveau() == -1) {
                            a_placer = false;
                        } else {
                            niveau = antecedant->get_niveau();
                        }
                    }

                    if(a_placer == true) {
                        tache->set_niveau(niveau + 1);
                    }
                }
            }
        }

        // Pour savoir si on sort de la boucle
        placement_effectue = true;
        for (auto& t : _liste_taches) {
            if(t->get_niveau() == -1) {
                placement_effectue = false;
            }
        }
    }
}

void Reseau::construction_graphe_initial() {
    
    int n = _liste_taches.back()->get_niveau();
    int numero_etape = 0;
            
    /* On creer la premiere tâche et on y accroche toutes les tâches du niveau 1 */
    
    Etape* premiere_etape = new Etape(numero_etape);
    _liste_etapes.push_back(premiere_etape);
    numero_etape++;
    
    for (auto& tache : _liste_taches) {
        if (tache->get_niveau() == 1) {
            
            tache->set_etape_debut(premiere_etape);
        
        }
    }
    
    /* On parcourt chaque tâche, niveau par niveau */
    
    for (int i = 1; i <= n; ++i) {
        for (auto& tache : _liste_taches) {
            if (tache->get_niveau() == i) {
                
                if(tache->get_successeurs().size() != 0) {
            
                    for (auto& successeur : tache->get_successeurs()) {
                        if (successeur->get_antecedants().size() > 1) {
   
                            bool deja_tache_fin = false;
                            
                            for (auto& t : successeur->get_antecedants()) {
                                
                                if (t->get_etape_fin() != NULL) {
                                    tache->set_etape_fin(t->get_etape_fin());
                                    deja_tache_fin = true;
                                    successeur->set_etape_debut(tache->get_etape_fin());
                                }
                            }
                            
                            if (deja_tache_fin == false) {
                                Etape* e = new Etape(numero_etape);
                                _liste_etapes.push_back(e);
                                numero_etape++;
                                tache->set_etape_fin(e);
                                successeur->set_etape_debut(tache->get_etape_fin());
                            }
                            
                        } else {
                            
                            if (tache->get_etape_fin() == NULL) {
                                Etape* e = new Etape(numero_etape);
                                _liste_etapes.push_back(e);
                                numero_etape++;
                                tache->set_etape_fin(e);
                            }
                            
                            successeur->set_etape_debut(tache->get_etape_fin());
                            
                        }
                    }
                } else {
                    
                    // On est a la derniere tache
                    Etape* e = new Etape(numero_etape);
                    _liste_etapes.push_back(e);
                    numero_etape++;
                    tache->set_etape_fin(e);
                }
            }
        }
    }
}

void Reseau::ordonnancement_au_plus_tot() {
    
    // On met toutes les dates au plus tot à -1
    for (auto& etape : _liste_etapes) {
        etape->set_date_plus_tot(-1);
    }
    
    // La premiere tache a une date au plus tot de 0
    _liste_taches.front()->set_date_debut_plus_tot(0);
    
    int nbc = 1;
    
    while (nbc < _liste_taches.size()) {
        
        for (auto& tache : _liste_taches) {
            if (tache->get_date_debut_plus_tot() == -1) {
                
                int plus_grande_val = INT_MIN;
                
                for (auto tache_precedante : tache->get_antecedants()) {
                    if (tache_precedante->get_date_debut_plus_tot() > -1) {
                        
                        int valeur = (tache_precedante->get_date_debut_plus_tot() + tache_precedante->get_duree());
                        
                        if (valeur > plus_grande_val) {
                            plus_grande_val = valeur;
                        }
                        
                        tache->set_date_debut_plus_tot(plus_grande_val);
                    }
                    nbc++;
                }
            }
        }
    }
    
    _liste_taches.back()->set_date_fin_plus_tot(_liste_taches.back()->get_date_debut_plus_tot() + _liste_taches.back()->get_duree());
    
}

void Reseau::ordonnancement_au_plus_tard() {
        
}

