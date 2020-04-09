//
//  main.cpp
//  ade_project
//
//  Created by Anthony Peres da Cruz on 19/02/2020.
//  Copyright © 2020 Anthony Peres da Cruz. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include "ProgrammeLineaire.hpp"
#include "GestionnaireDonnee.hpp"
#include "Reseau.hpp"

using namespace std;

/* Les fonctions */

void resolution_programmes_lineaires();
void methode_pert();

int main(int argc, const char * argv[]) {
    int choix = 0;
    
    while (choix != 3) {
        cout << "Que souhaitez-vous ?\n";
        cout << "  1 - Résolution de Programme Linéaires.\n";
        cout << "  2 - Appliquer la méthode PERT.\n";
        cout << "  3 - Quitter le programme.\n";
        cout << "Choix : ";
        cin >> choix;
        
        switch (choix) {
            case 1:
                resolution_programmes_lineaires();
                break;
                
            case 2:
                methode_pert();
                break;
        }
    }
    
    return 0;
}

/* Fonctions */

/* La résolution de programmes linéaires */
void resolution_programmes_lineaires() {
    
    cout << "Lancement de la résolution de programmes linéaires\n";
    
    // Création des PLC
    vector<ProgrammeLineaire> plc(rand()%(200-50)+50);
    
    // On écrit les PLC et les résultats dans deux fichiers.csv différents
    GestionnaireDonnee gestionnaireDonnee;
    gestionnaireDonnee.ecrirePLC(plc);
    gestionnaireDonnee.ecrireResultats(plc);
    
    cout << "Fin de la résolution de programmes linéaires\n";
}

/* La méthode PERT */
void methode_pert() {
    
    cout << "Lancement de la méthode PERT\n" << endl;
    
    Reseau reseau;
    
    cout << endl << "Fin de la méthode PERT\n" << endl;
}
