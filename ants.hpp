#ifndef ANTS_HPP
#define ANTS_HPP

#include <string>
#include <vector>
#include <queue>
#include <map>

class Room {
private:
    int id;
    std::string name;
    int capacity;
    int nb_ants;
public:
    Room(int id_r, const char* n, int cap);
    int getId();
    std::string getName();
    int getCapacity();
    int getNbAnts();
    void add_ant();
    void remove_ant();
};

class Path {
private:
    int id;
    Room* room1;
    Room* room2;
public:
    Path(int id_p, Room* r1, Room* r2);
    Room* getRoom1();
    Room* getRoom2();
    int getId();
};

class Ant {
private:
    int id;
    int position;
    Room* room;
public:
    Ant(int id_a);
    int getId();
    int getPosition();
    void advancePosition();
    int changeRoom(Room* newRoom, Path* paths[], int nbPaths, Room* startRoom);
    Room* getRoom();
};

// Pathfinding function declaration
std::vector<Room*> findPath(Room* start, Room* end, Path* paths[], int nbPaths);

#endif