//
//  Reseau.cpp
//  ade_project
//
//  Created by Anthony Peres da Cruz on 11/03/2020.
//  Copyright © 2020 Anthony Peres da Cruz. All rights reserved.
//

#include "Reseau.hpp"

using namespace std;

/* Constructeur et destructeur */

Reseau::Reseau() {
    init_liste_taches();
    approche_par_suppression();
    construction_graphe_initial();
    ordonnancement_au_plus_tot();
    ordonnancement_au_plus_tard();
    faire_calculs();
    calcul_chemin_critique();
    construction_sous_graphe_critique();
    afficher_resultats();
    verifier_donnees_attendus();
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


/* AU LIEU DE FAIRE PLACEMENT_EFFECTUE FAIRE NBC COMME DANS ORDONNANCEMENT**/

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
                
                for (auto& tache_precedante : tache->get_antecedants()) {
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

/* Pour l'ordonnancement au plus tard, nous utilisons pas une variable nbc en tant que condition d'arret mais nous allons checker à chaque fois si il
 y a une tache qui manque de date au plus tard, ceci est dû au fait que nous attribuons des fois une nouvelle valeur a une étape donc nbc s'incremente
 2 fois pour une meme étape. */
void Reseau::ordonnancement_au_plus_tard() {
        
    for (auto& tache : _liste_taches) {
        tache->set_date_debut_plus_tard(INT_MAX);
    }
    
    _liste_taches.back()->set_date_fin_plus_tard(_liste_taches.back()->get_date_fin_plus_tot());
    _liste_taches.back()->set_date_debut_plus_tard(_liste_taches.back()->get_date_fin_plus_tard() - _liste_taches.back()->get_duree());
    
    bool place = false;
    
    while (place == false) {
        
        for (auto& tache : _liste_taches) {
            if(tache->get_date_debut_plus_tard() == INT_MAX) {
                
                int numero_etape_debut = tache->get_etape_debut()->get_numero();
                int date = INT_MAX;
                
                for(auto& voisin : _liste_taches) {
                    if(numero_etape_debut == voisin->get_etape_debut()->get_numero()) {
                        for (auto& successeur: voisin->get_successeurs()) {
                            if(successeur->get_date_debut_plus_tard() < INT_MAX) {
                                if(date > successeur->get_date_debut_plus_tard() - voisin->get_duree()) {
                                    date = successeur->get_date_debut_plus_tard() - voisin->get_duree();
                                }
                            }
                        }
                    }
                }
                
                if(date != INT_MAX) {
                    tache->set_date_debut_plus_tard(date);
                }
            }
        }
            
        place = true;
        for(auto& t : _liste_taches) {
            if (t->get_date_debut_plus_tard() == INT_MAX) {
                place = false;
            }
        }
    }
}


/* Les calculs des dates et taches/chemins critiques */

void Reseau::faire_calculs() {
    for(auto& tache : _liste_taches) {
        tache->calcul_marge_totale();
        tache->calcul_marge_libre();
        tache->calcul_tache_critique();
    }
}

void Reseau::calcul_chemin_critique() {
    for(auto& tache : _liste_taches) {
        if(tache->get_critique() == true) {
            
            if(tache->get_antecedants().size() == 0) {
                if(tache->get_date_debut_plus_tot() + tache->get_duree() == tache->get_date_fin_plus_tard()) {
                    this->_liste_taches_chemin_critique.push_back(tache);
                }
            } else {
                for(auto& antecedant : tache->get_antecedants()) {
                    if(tache->get_date_debut_plus_tot() == antecedant->get_date_debut_plus_tot() + antecedant->get_duree()) {
                        this->_liste_taches_chemin_critique.push_back(tache);
                    }
                }
            }
        }
    }
}


/* Fonctions d'affichage des résultats et des tests */

void Reseau::afficher_resultats() {
    for(auto& t : _liste_taches) {
        t->__tostring();
        cout << endl << endl;
    }
}

void Reseau::verifier_donnees_attendus() {
    
    Donnees data;
    int i = 0;
    
    for(auto t : _liste_taches) {
        switch (i) {
            case 0:
                data = {'A', {4,1,3,0,0,0,1,0,0,4,7}};
                break;
            case 1:
                data = {'B', {8,1,0,0,1,0,2,0,0,8,8}};
                break;
            case 2:
                data = {'C', {1,1,13,0,0,0,3,0,0,1,14}};
                break;
            case 3:
                data = {'D', {1,2,13,0,0,3,4,1,14,2,15}};
                break;
            case 4:
                data = {'E', {6,2,3,3,0,1,5,4,7,13,13}};
                break;
            case 5:
                data = {'F', {3,2,6,6,0,1,5,4,7,13,13}};
                break;
            case 6:
                data = {'G', {5,2,0,0,1,2,5,8,8,13,13}};
                break;
            case 7:
                data = {'H', {3,3,0,0,1,5,6,13,13,16,16}};
                break;
            case 8:
                data = {'I', {1,3,13,0,0,4,7,2,15,3,16}};
                break;
            case 9:
                data = {'J', {2,4,13,13,0,7,8,3,16,18,18}};
                break;
            case 10:
                data = {'K', {2,4,0,0,1,6,8,16,16,18,18}};
                break;
            case 11:
                data = {'L', {5,5,0,0,1,8,9,18,18,23,23}};
                break;
            default:
                break;
        }
        test_pertinance_tache(t, data);
        i++;
    }
}

void Reseau::test_pertinance_tache(Tache* t, Donnees data) {
    bool erreur = false;
    
    cout << "- erreur Tache : " << t->get_nom() << " : ";
    
    if(t->get_nom() != data.nom) {
        cout << " nom : attendu : " << data.nom << ", obtenu : " << t->get_nom() << "   ";
    }
    if(t->get_duree() != data.valeurs[0]) {
        cout << " duree : attendu : " << data.valeurs[0] << ", obtenu : " << t->get_duree() << "   ";
    }
    if(t->get_niveau() != data.valeurs[1]) {
        cout << " niveau : attendu : " << data.valeurs[1] << ", obtenu : " << t->get_niveau() << "   ";
    }
    if(t->get_marge_totale() != data.valeurs[2]) {
        cout << " MT : attendu : " << data.valeurs[2] << ", obtenu : " << t->get_marge_totale() << "   ";
    }
    if(t->get_marge_libre() != data.valeurs[3]) {
        cout << " ML : attendu : " << data.valeurs[3] << ", obtenu : " << t->get_marge_libre() << "   ";
    }
    if(t->get_critique() != data.valeurs[4]) {
        cout << " critique : attendu : " << data.valeurs[4] << ", obtenu : " << t->get_critique() << "   ";
    }
    if(t->get_etape_debut()->get_numero() != data.valeurs[5]) {
        cout << " etape debut : attendu : " << data.valeurs[5] << ", obtenu : " << t->get_etape_debut()->get_numero() << "   ";
    }
    if(t->get_etape_fin()->get_numero()  != data.valeurs[6]) {
        cout << " etape fin : attendu : " << data.valeurs[6] << ", obtenu : " << t->get_etape_fin()->get_numero() << "   ";
    }
    if(t->get_date_debut_plus_tot() != data.valeurs[7]) {
        cout << " date debut plus tot : attendu : " << data.valeurs[7] << ", obtenu : " << t->get_date_debut_plus_tot() << "   ";
    }
    if(t->get_date_debut_plus_tard() != data.valeurs[8]) {
        cout << " date debut plus tard : attendu : " << data.valeurs[8] << ", obtenu : " << t->get_date_debut_plus_tard() << "   ";
    }
    if(t->get_date_fin_plus_tot() != data.valeurs[9]) {
        cout << " date fin plus tot : attendu : " << data.valeurs[9] << ", obtenu : " << t->get_date_fin_plus_tot() << "   ";
    }
    if(t->get_date_fin_plus_tard() != data.valeurs[10]) {
        cout << " date fin plus tard : attendu : " << data.valeurs[10] << ", obtenu : " << t->get_date_fin_plus_tard() << "   ";
    }
    
    if(erreur == false) {
        cout << "Aucune erreur !";
    }
    cout << endl;
}

void Reseau::construction_sous_graphe_critique() { 
    int n = _liste_taches_chemin_critique.back()->get_niveau();
    int numero_etape = 0;
    
    /* On creer la premiere tâche et on y accroche toutes les tâches du niveau 1 */
    
    Etape* premiere_etape = new Etape(numero_etape);
    _liste_etapes_graphe_critique.push_back(premiere_etape);
    numero_etape++;
    
    for (auto& tache : _liste_taches_chemin_critique) {
        if (tache->get_niveau() == 1) {
            tache->set_etape_debut(premiere_etape);
        }
    }
    
    for (int i = 1; i <= n; ++i) {
        for (auto& tache : _liste_taches_chemin_critique) {
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
                                _liste_etapes_graphe_critique.push_back(e);
                                numero_etape++;
                                tache->set_etape_fin(e);
                                successeur->set_etape_debut(tache->get_etape_fin());
                            }
                            
                        } else {
                            
                            if (tache->get_etape_fin() == NULL) {
                                Etape* e = new Etape(numero_etape);
                                _liste_etapes_graphe_critique.push_back(e);
                                numero_etape++;
                                tache->set_etape_fin(e);
                            }
                            
                            successeur->set_etape_debut(tache->get_etape_fin());
                            
                        }
                    }
                } else {
                    
                        // On est a la derniere tache
                    Etape* e = new Etape(numero_etape);
                    _liste_etapes_graphe_critique.push_back(e);
                    numero_etape++;
                    tache->set_etape_fin(e);
                }
            }
        }
    }
}

