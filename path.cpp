#include "ants.hpp"

Path::Path(int id_p, Room* r1, Room* r2) : id(id_p), room1(r1), room2(r2) {}

Room* Path::getRoom1() { return room1; }
Room* Path::getRoom2() { return room2; }
int Path::getId() { return id; }