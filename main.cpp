#include "ants.hpp"
#include <iostream>
#include <vector>

int main(){
    int ants = 50;
    int n = 1;

    // Création des salles
    Room sv(1, "Sv", 50);
    Room s1(2, "S1", 8);
    Room s2(3, "S2", 4);
    Room s3(4, "S3", 2);
    Room s4(5, "S4", 4);
    Room s5(6, "S5", 2);
    Room s6(7, "S6", 4);
    Room s7(8, "S7", 2);
    Room s8(9, "S8", 5);
    Room s9(10, "S9", 1);
    Room s10(11, "S10", 1);
    Room s11(12, "S11", 1);
    Room s12(13, "S12", 1);
    Room s13(14, "S13", 4);
    Room s14(15, "S14", 2);
    Room sd(16, "Sd", 50);

    // Création des chemins
    Path c1(1, &s1, &s2);
    Path c2(2, &s2, &s3);
    Path c3(3, &s3, &s4);
    Path c4(4, &s4, &sd);
    Path c5(5, &sv, &s1);
    Path c6(6, &s2, &s5);
    Path c7(7, &s5, &s4);
    Path c8(8, &s13, &sd);
    Path c9(9, &s8, &s12);
    Path c10(10, &s12, &s13);
    Path c11(11, &s6, &s7);
    Path c12(12, &s7, &s9);
    Path c13(13, &s9, &s14);
    Path c14(14, &s14, &sd);
    Path c15(15, &s7, &s10);
    Path c16(16, &s10, &s14);
    Path c17(17, &s1, &s6);
    Path c18(18, &s6, &s8);
    Path c19(19, &s8, &s11);
    Path c20(20, &s11, &s13);

    Path* waye[] = { &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8, &c9, &c10,
                          &c11, &c12, &c13, &c14, &c15, &c16, &c17, &c18, &c19, &c20 };

    Ant** antsTab = new Ant*[ants];
    for (int nb = 0; nb < ants; nb++){
        antsTab[nb] = new Ant(nb + 1);
    }

    for (int i = 0; i < ants; i++) {
        antsTab[i]->changeRoom(&sv, waye, 20, &sv);
    }

    // Tableau des étapes à suivre pour chaque fourmi
    std::vector<Room*> courses = findPath(&sv, &sd, waye, 20);

    while (sd.getNbAnts() < ants) {
        std::cout << "+++++Etape" << n << "+++++" << std::endl;
        for (int i = 0; i < ants; i++) {
            // Calculer le chemin optimal depuis la salle actuelle de la fourmi
            std::vector<Room*> courses = findPath(antsTab[i]->getRoom(), &sd, waye, 20);
            if (courses.size() > 1) {
                // Essayer la salle optimale d'abord
                Room* nextRoom = courses[1];
                if (antsTab[i]->changeRoom(nextRoom, waye, 20, &sv) == 1) {
                    antsTab[i]->advancePosition();
                    continue;
                }
                // Sinon, essayer les autres voisines qui rapprochent du dortoir
                Room* actualRoom = antsTab[i]->getRoom();
                for (int j = 0; j < 20; j++) {
                    Room* neighbor = nullptr;
                    if (waye[j]->getRoom1() == actualRoom)
                        neighbor = waye[j]->getRoom2();
                    else if (waye[j]->getRoom2() == actualRoom)
                        neighbor = waye[j]->getRoom1();

                    // Vérifie que le voisin est sur un chemin vers le dortoir et n'est pas la salle actuelle
                    std::vector<Room*> browseNeighbor = findPath(neighbor, &sd, waye, 4);
                    if (neighbor && neighbor != actualRoom && neighbor != &sv && browseNeighbor.size() > 0) {
                        if (antsTab[i]->changeRoom(neighbor, waye, 20, &sv) == 1) {
                            antsTab[i]->advancePosition();
                            break;
                        }
                    }
                }
            }
        }
        n++;
    }

    return 0;
}