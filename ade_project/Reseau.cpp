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
    initListeTaches();
    approcheParSuppresion();
    constructionGrapheInitial();
    ordonnancementPlusTot();
    ordonnancementPlusTard();
    executerCalculs();
    afficherResultats();
    verifierDonnees();
}

Reseau::~Reseau() {
    
}

/* Fonctions */

/* Fonction qui recupere la liste des tâches dans le fichier csv. **/
void Reseau::initListeTaches() {
    
    ifstream fichier("ade_project/ListeTaches.csv");
    if(fichier) {
        
        string ligne;
        
        while(getline(fichier, ligne)) {

            char nom = '\0';
            int duree = '\0';
            list<Tache*> predecesseurs;
            
            for (int i = 0; i < (int) ligne.size() ; ++i) {
                if(i == 0) {
                    nom = ligne[i];
                    
                } else if(i == 2) {
                    char stTemp[2];
                    sprintf(stTemp,"%c", ligne[i]);
                    duree = atoi(stTemp);
                    
                } else if(i >= 4) {
                    for (auto &tache : _liste_taches) {
                        if(ligne[i] == tache->getNom()) {
                            predecesseurs.push_back(tache);
                        }
                    }
                }
            }
            
            // On creer et on ajoute la tache a la liste
            Tache *t = new Tache(nom, duree, predecesseurs);
            this->_liste_taches.push_back(t);
        }
        
        fichier.close();
        
    } else {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }
}

/* Fonction donnant des niveaux aux tâches grace à l'approche par suppression. **/
void Reseau::approcheParSuppresion() {
    int niveau = 0;
    bool placement_effectue = false;

    for(auto& tache : _liste_taches) {
        tache->setNiveau(-1);
    }
    
    while (!placement_effectue) {
        
        for (auto& tache : _liste_taches) {
            if (tache->getNiveau() == -1) {
                
                if (tache->getPredecesseurs().size() == 0) {
                    tache->setNiveau(niveau + 1);
                } else {
                    
                    bool a_placer = true;
                    for (auto& antecedant : tache->getPredecesseurs()) {
                        if(antecedant->getNiveau() == -1) {
                            a_placer = false;
                        } else {
                            niveau = antecedant->getNiveau();
                        }
                    }

                    if(a_placer == true) {
                        tache->setNiveau(niveau + 1);
                    }
                }
            }
        }

        // Pour savoir si on sort de la boucle
        placement_effectue = true;
        for (auto& t : _liste_taches) {
            if(t->getNiveau() == -1) {
                placement_effectue = false;
            }
        }
    }
}

/* Fonction qui construit le graphe initial. **/
void Reseau::constructionGrapheInitial() {
    
    int n = _liste_taches.back()->getNiveau();
    int numero_etape = 0;
            
    /* On creer la premiere tâche et on y accroche toutes les tâches du niveau 1 */
    
    Etape* premiere_etape = new Etape(numero_etape);
    _liste_etapes.push_back(premiere_etape);
    numero_etape++;
    
    for (auto& tache : _liste_taches) {
        if (tache->getNiveau() == 1) {
            tache->setEtapeDebut(premiere_etape);
        }
    }
        
    for (int i = 1; i <= n; ++i) {
        for (auto& tache : _liste_taches) {
            if (tache->getNiveau() == i) {
                
                if(tache->getSuccesseurs().size() != 0) {
            
                    for (auto& successeur : tache->getSuccesseurs()) {
                        if (successeur->getPredecesseurs().size() > 1) {
   
                            bool deja_tache_fin = false;
                            
                            for (auto& t : successeur->getPredecesseurs()) {
                                
                                if (t->getEtapeFin() != NULL) {
                                    tache->setEtapeFin(t->getEtapeFin());
                                    deja_tache_fin = true;
                                    successeur->setEtapeDebut(tache->getEtapeFin());
                                }
                            }
                            
                            if (deja_tache_fin == false) {
                                Etape* e = new Etape(numero_etape);
                                _liste_etapes.push_back(e);
                                numero_etape++;
                                tache->setEtapeFin(e);
                                successeur->setEtapeDebut(tache->getEtapeFin());
                            }
                            
                        } else {
                            if (tache->getEtapeFin() == NULL) {
                                Etape* e = new Etape(numero_etape);
                                _liste_etapes.push_back(e);
                                numero_etape++;
                                tache->setEtapeFin(e);
                            }
                            successeur->setEtapeDebut(tache->getEtapeFin());
                        }
                    }
                } else {
                    
                    // On est a la derniere tache
                    Etape* e = new Etape(numero_etape);
                    _liste_etapes.push_back(e);
                    numero_etape++;
                    tache->setEtapeFin(e);
                }
            }
        }
    }
}

/* Fonction calculant les dates au plus tot. **/
void Reseau::ordonnancementPlusTot() {
    
    // On met toutes les dates au plus tot à -1
    for (auto& etape : _liste_etapes) {
        etape->setDatePlusTot(-1);
    }
    
    // La premiere tache a une date au plus tot de 0
    _liste_taches.front()->setDateDebutPlusTot(0);
    
    int nbc = 1;
    
    while (nbc < _liste_taches.size()) {
        
        for (auto& tache : _liste_taches) {
            if (tache->getDateDebutPlusTot() == -1) {
                
                int plus_grande_val = INT_MIN;
                
                for (auto& tache_precedante : tache->getPredecesseurs()) {
                    if (tache_precedante->getDateDebutPlusTot() > -1) {
                        
                        int valeur = (tache_precedante->getDateDebutPlusTot() + tache_precedante->getDuree());
                        
                        if (valeur > plus_grande_val) {
                            plus_grande_val = valeur;
                        }
                        
                        tache->setDateDebutPlusTot(plus_grande_val);
                    }
                    nbc++;
                }
            }
        }
    }
    
    _liste_taches.back()->setDateFinPlusTot(_liste_taches.back()->getDateDebutPlusTot() + _liste_taches.back()->getDuree());
    
}

/* Fonction calculant les tâches au plus tard. */
void Reseau::ordonnancementPlusTard() {
        
    for (auto& tache : _liste_taches) {
        tache->setDateDebutPlusTard(INT_MAX);
    }
    
    _liste_taches.back()->setDateFinPlusTard(_liste_taches.back()->getDateFinPlusTot());
    _liste_taches.back()->setDateDebutPlusTard(_liste_taches.back()->getDateFinPlusTard() - _liste_taches.back()->getDuree());
    
    bool place = false;
    
    while (place == false) {
        
        for (auto& tache : _liste_taches) {
            if(tache->getDateDebutPlusTard() == INT_MAX) {
                
                int numero_etape_debut = tache->getEtapeDebut()->getNumero();
                int date = INT_MAX;
                
                for(auto& voisin : _liste_taches) {
                    if(numero_etape_debut == voisin->getEtapeDebut()->getNumero()) {
                        for (auto& successeur: voisin->getSuccesseurs()) {
                            if(successeur->getDateDebutPlusTard() < INT_MAX) {
                                if(date > successeur->getDateDebutPlusTard() - voisin->getDuree()) {
                                    date = successeur->getDateDebutPlusTard() - voisin->getDuree();
                                }
                            }
                        }
                    }
                }
                
                if(date != INT_MAX) {
                    tache->setDateDebutPlusTard(date);
                }
            }
        }
            
        place = true;
        for(auto& t : _liste_taches) {
            if (t->getDateDebutPlusTard() == INT_MAX) {
                place = false;
            }
        }
    }
}


/* Les calculs des dates et taches, chemins et sous graphe critique. */
void Reseau::executerCalculs() {
    for(auto& tache : _liste_taches) {
        tache->calculMargeTotale();
        tache->calculMargeLibre();
        tache->calculTacheCritique();
        
        if(tache->getCritique() == true) {
            
            if(tache->getPredecesseurs().size() == 0) {
                if(tache->getDateDebutPlusTot() + tache->getDuree() == tache->getDateFinPlusTard()) {
                    this->_liste_taches_chemin_critique.push_back(tache);
                }
            } else {
                for(auto& antecedant : tache->getPredecesseurs()) {
                    if(tache->getDateDebutPlusTot() == antecedant->getDateDebutPlusTot() + antecedant->getDuree()) {
                        this->_liste_taches_chemin_critique.push_back(tache);
                    }
                }
            }
        }
    }
}


/* Fonctions d'affichage des résultats et des tests */
void Reseau::afficherResultats() {
    for(auto& t : _liste_taches) {
        t->__toString();
        cout << endl << endl;
    }
}

/* Fonction ou on insere les données que l'on attend. **/
void Reseau::verifierDonnees() {
    
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
        testerDonneesTaches(t, data);
        i++;
    }
}

/* Fonction qui verifie que les données inserées precedemment correspondent. **/
void Reseau::testerDonneesTaches(Tache* t, Donnees data) {
    bool erreur = false;
    
    cout << "- Tache : " << t->getNom() << " : ";
    
    if(t->getNom() != data.nom) {
        cout << " nom : attendu : " << data.nom << ", obtenu : " << t->getNom() << "   ";
    }
    if(t->getDuree() != data.valeurs[0]) {
        cout << " duree : attendu : " << data.valeurs[0] << ", obtenu : " << t->getDuree() << "   ";
    }
    if(t->getNiveau() != data.valeurs[1]) {
        cout << " niveau : attendu : " << data.valeurs[1] << ", obtenu : " << t->getNiveau() << "   ";
    }
    if(t->getMargeTotale() != data.valeurs[2]) {
        cout << " MT : attendu : " << data.valeurs[2] << ", obtenu : " << t->getMargeTotale() << "   ";
    }
    if(t->getMargeLibre() != data.valeurs[3]) {
        cout << " ML : attendu : " << data.valeurs[3] << ", obtenu : " << t->getMargeLibre() << "   ";
    }
    if(t->getCritique() != data.valeurs[4]) {
        cout << " critique : attendu : " << data.valeurs[4] << ", obtenu : " << t->getCritique() << "   ";
    }
    if(t->getEtapeDebut()->getNumero() != data.valeurs[5]) {
        cout << " etape debut : attendu : " << data.valeurs[5] << ", obtenu : " << t->getEtapeDebut()->getNumero() << "   ";
    }
    if(t->getEtapeFin()->getNumero()  != data.valeurs[6]) {
        cout << " etape fin : attendu : " << data.valeurs[6] << ", obtenu : " << t->getEtapeFin()->getNumero() << "   ";
    }
    if(t->getDateDebutPlusTot() != data.valeurs[7]) {
        cout << " date debut plus tot : attendu : " << data.valeurs[7] << ", obtenu : " << t->getDateDebutPlusTot() << "   ";
    }
    if(t->getDateDebutPlusTard() != data.valeurs[8]) {
        cout << " date debut plus tard : attendu : " << data.valeurs[8] << ", obtenu : " << t->getDateDebutPlusTard() << "   ";
    }
    if(t->getDateFinPlusTot() != data.valeurs[9]) {
        cout << " date fin plus tot : attendu : " << data.valeurs[9] << ", obtenu : " << t->getDateFinPlusTot() << "   ";
    }
    if(t->getDateFinPlusTard() != data.valeurs[10]) {
        cout << " date fin plus tard : attendu : " << data.valeurs[10] << ", obtenu : " << t->getDateFinPlusTard() << "   ";
    }
    
    if(erreur == false) {
        cout << " --> Aucune erreur !";
    }
    cout << endl;
}
