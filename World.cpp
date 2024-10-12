#include "World.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

World::World(int height, int width) : height(height), width(width) {
    grid.resize(height, std::vector<int>(width, 0));
    nextGrid.resize(height, std::vector<int>(width, 0));
}

World::World(std::string filename) {
    load(filename);
}

void World::evolve() {
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            int liveNeighbors = countLiveNeighbors(x, y);
            if (grid[x][y] == 1 && (liveNeighbors == 2 || liveNeighbors == 3)) {
                nextGrid[x][y] = 1; // Cell stays alive
            } else if (grid[x][y] == 0 && liveNeighbors == 3) {
                nextGrid[x][y] = 1; // Cell becomes alive
            } else {
                nextGrid[x][y] = 0; // Cell dies
            }
        }
    }
    grid.swap(nextGrid);
}

bool World::is_stable() {
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            if (grid[x][y] != nextGrid[x][y])
                return false;
        }
    }
    return true;
}

void World::print() {
    for (const auto& row : grid) {
        for (int cell : row) {
            std::cout << (cell ? 'X' : '.') << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void World::load(std::string filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> height >> width;
        grid.resize(height, std::vector<int>(width));
        nextGrid.resize(height, std::vector<int>(width));
        for (int x = 0; x < height; x++) {
            for (int y = 0; y < width; y++) {
                file >> grid[x][y];
            }
        }
    }
}

void World::save(std::string filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << height << " " << width << "\n";
        for (const auto& row : grid) {
            for (int cell : row) {
                file << cell << " ";
            }
            file << "\n";
        }
    }
}

int World::countLiveNeighbors(int x, int y) {
    int count = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0)
                continue;
            int nx = (x + dx + height) % height;
            int ny = (y + dy + width) % width;
            count += grid[nx][ny];
        }
    }
    return count;
}

void World::run(int generations, bool printEnabled, int delayMs) {
    using namespace std::chrono;  // For easier access to chrono functions

    auto start = high_resolution_clock::now();  // Start time

    while (generations-- > 0) {
        evolve();  // Update the state of the world
        if (printEnabled) {
            print();  // Output the current state
        }
        if (is_stable()) {
            std::cout << "Stable configuration reached." << std::endl;
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));  // Pause for delayMs
    }

    auto end = high_resolution_clock::now();  // End time
    auto duration = duration_cast<milliseconds>(end - start);  // Duration in milliseconds

    std::cout << "Simulation ran for " << duration.count() << " milliseconds." << std::endl;
}
void World::setCellState(int x, int y, int state) {
    if (x >= 0 && x < height && y >= 0 && y < width) {
        grid[x][y] = state;
    }
    else {
        std::cout << "Attempt to set cell state outside of grid boundaries ignored." << std::endl;
    }
}

int World::getCellState(int x, int y) {
    if (x >= 0 && x < height && y >= 0 && y < width) {
        return grid[x][y];
    }
    return -1; // Invalid position
}

void World::addGlider(int x, int y) {
    setCellState(x, y, 1);
    setCellState(x+1, y-1, 1);
    setCellState(x-1, y, 1);
    setCellState(x-1, y-1, 1);
    setCellState(x-1, y-2, 1);

}

void World::addToad(int x, int y) {
    setCellState(x, y, 1);
    setCellState(x+1, y+1, 1);
    setCellState(x+1, y-1, 1);
    setCellState(x, y-1, 1);
    setCellState(x, y-2, 1);
    
}

void World::addBeacon(int x, int y) {
    setCellState(x, y, 1);
    setCellState(x-1, y, 1);
    setCellState(x, y+1, 1);
    setCellState(x-3, y+3, 1);
    setCellState(x-3, y+2, 1);
    setCellState(x-2, y+3, 1);
}

void World::addMethuselah(int x, int y) {
    setCellState(x, y, 1);
    setCellState(x, y-1, 1);
    setCellState(x, y+1, 1);
    setCellState(x+3, y, 1);
    setCellState(x+2, y-1, 1);
    setCellState(x+2, y+1, 1);
    setCellState(x+1, y-4, 1);
    setCellState(x+2, y-4, 1);
    setCellState(x+1, y-5, 1);
    setCellState(x+2, y-5, 1);
}

