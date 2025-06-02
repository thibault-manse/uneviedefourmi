#include "ants.hpp"
#include <vector>
#include <map>

std::vector<Room*> findPath(Room* start, Room* end, Path* paths[], int nbPaths) {
    std::queue<Room*> q;
    std::map<Room*, Room*> previous;
    q.push(start);
    previous[start] = nullptr;

    while (!q.empty()) {
        Room* current = q.front();
        q.pop();

        if (current == end) break;

        for (int i = 0; i < nbPaths; ++i) {
            Room* neighbor = nullptr;
            if (paths[i]->getRoom1() == current)
                neighbor = paths[i]->getRoom2();
            else if (paths[i]->getRoom2() == current)
                neighbor = paths[i]->getRoom1();

            if (neighbor && previous.find(neighbor) == previous.end()) {
                previous[neighbor] = current;
                q.push(neighbor);
            }
        }
    }

    // Rebuild the path
    std::vector<Room*> path;
    Room* current = end;
    while (current && current != start) {
        path.insert(path.begin(), current);
        current = previous[current];
    }
    if (current == start)
        path.insert(path.begin(), start);

    return path;
}