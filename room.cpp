#include "ants.hpp"

Room::Room(int id_s, const char* n, int cap) : id(id_s), name(n), capacity(cap), nb_ants(0) {}

int Room::getId() { return id; }
std::string Room::getName() { return name; }
int Room::getCapacity() { return capacity; }
int Room::getNbAnts() { return nb_ants; }
void Room::add_ant() { nb_ants++; }
void Room::remove_ant() { nb_ants--; }