#include "ants.hpp"
#include <iostream>

Ant::Ant(int id_f) : id(id_f), position(0), room(nullptr) {}

int Ant::getId() { return id; }
int Ant::getPosition() { return position; }
void Ant::advancePosition() { position++; }

int Ant::changeRoom(Room* newRoom, Path* paths[], int nbPaths, Room* startRoom) {
    if (room == nullptr) {
        newRoom->add_ant();
        room = newRoom;
        std::cout << "Fourmi" << id << " placée dans la salle initiale." << std::endl;
        return 1;
    } else {
        bool pathExists = false;
        for (int i = 0; i < nbPaths; ++i) {
            if ((paths[i]->getRoom1() == room && paths[i]->getRoom2() == newRoom) ||
                (paths[i]->getRoom2() == room && paths[i]->getRoom1() == newRoom)) {
                pathExists = true;
                break;
            }
        }
        if (!pathExists) {
            return 0;
        }
        if (newRoom->getNbAnts() >= newRoom->getCapacity()) {
            return 0;
        }
        if (room != nullptr) {
            room->remove_ant();
        }
        std::cout << "f" << id << " - " << room->getName() << " - " << newRoom->getName() << std::endl;
        newRoom->add_ant();
        room = newRoom;
        return 1;
    }
}

Room* Ant::getRoom() { return room; }
