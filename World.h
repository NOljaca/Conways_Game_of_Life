#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <string>

class World {
private:
    int height, width;
    std::vector<std::vector<int>> grid; // 2D grid for the world
    std::vector<std::vector<int>> nextGrid; // Buffer for the next generation

    void evolve();
    bool is_stable();
    void print();
    int countLiveNeighbors(int x, int y);

public:
    World(int height, int width);
    World(std::string filename);
    void run(int generations, bool printEnabled = true, int delayMs = 500);
    void setCellState(int x, int y, int state);
    int getCellState(int x, int y);
    void load(std::string filename);
    void save(std::string filename);
    void addGlider(int x, int y);
    void addToad(int x, int y);
    void addBeacon(int x, int y);
    void addMethuselah(int x, int y);
};

#endif // WORLD_H
