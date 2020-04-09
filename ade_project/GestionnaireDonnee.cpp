//
//  Donnees.cpp
//  ade_project
//
//  Created by Anthony Peres da Cruz on 19/02/2020.
//  Copyright © 2020 Anthony Peres da Cruz. All rights reserved.
//

#include "GestionnaireDonnee.hpp"

using namespace std;

// Constructeur et destructeur

GestionnaireDonnee::GestionnaireDonnee() {}
GestionnaireDonnee::~GestionnaireDonnee() {}

// Les fonctions

void GestionnaireDonnee::ecrirePLC(vector<ProgrammeLineaire> liste_plc) {
    
    ofstream fichier;
    
    fichier.open ("ade_project/Les programmes linéaires.csv");
    fichier << "Liste des "+ to_string(liste_plc.size()) +" PLC : \n";
    
    int i = 1;
    for (auto& plc : liste_plc) {
        fichier << ";PLC n°" + to_string(i) + "\n";
        fichier << "Nombre de variables de décisions : ;" + to_string(plc.get_nb_variables_decisions()) + "\n";
        fichier << "Nombre de contraintes : ;" + to_string(plc.get_nb_contraintes()) + "\n";
        fichier << "Matrice :\n";
        
        int indice_case = 0, indice_ligne = 0, indice_derniere_ligne = (int) plc.get_matrice().size() - 1;
        for(auto& ligne : plc.get_matrice()) {
            
            if(indice_ligne == indice_derniere_ligne) {
                fichier << "Z : ";
            } else {
                fichier << "e" + to_string(indice_ligne + 1);
            }
            
            for (auto& c : ligne) {
                fichier << ";" + to_string((int) c);
                indice_case++;
            }
            
            fichier << "\n";
            indice_case = 0;
            indice_ligne++;
        }
        
        fichier << "\n\n";
        i++;
    }
    fichier.close();
}

void GestionnaireDonnee::ecrireResultats(vector<ProgrammeLineaire> liste_plc) {
    
    ofstream fichier;
    string ligne;
    
    fichier.open ("ade_project/Resultats.csv");
    fichier << "Nombre variables de decisions;";
    fichier << "Nombre contraintes;";
    fichier << "Temps résolution";
    fichier << "\n";
    
    for(auto& plc : liste_plc) {
        fichier << to_string(plc.get_nb_variables_decisions()) + ";";
        fichier << to_string(plc.get_nb_contraintes()) + ";";
        fichier << to_string(plc.get_temps_resolution());
        fichier << "\n";
    }
    
    fichier.close();
}
