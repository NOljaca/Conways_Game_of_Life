#include <iostream>
#include <string>
#include  "World.h"

class CLI {
private:
    World* world;
    bool printingEnabled = true;
    int delayMs = 500;

    void createWorld() {
        int height, width;
        std::cout << "Enter world height: ";
        std::cin >> height;
        std::cout << "Enter world width: ";
        std::cin >> width;
        world = new World(height, width);
    }

    void loadWorld() {
        std::string filename;
        std::cout << "Enter filename to load: ";
        std::cin >> filename;
        world = new World(filename);
    }

    void saveWorld() {
        if (!world) {
            std::cout << "No world to save.\n";
            return;
        }
        std::string filename;
        std::cout << "Enter filename to save: ";
        std::cin >> filename;
        world->save(filename);
    }

    void togglePrinting() {
        printingEnabled = !printingEnabled;
        std::cout << "Printing " << (printingEnabled ? "enabled" : "disabled") << ".\n";
    }

    void setDelay() {
        std::cout << "Enter delay in ms: ";
        std::cin >> delayMs;
    }

    void runSimulation() {
        if (!world) {
            std::cout << "No world created or loaded.\n";
            return;
        }
        int generations;
        std::cout << "Enter number of generations to run: ";
        std::cin >> generations;
        world->run(generations, printingEnabled, delayMs);
    }

    void setCell() {
        if (!world) {
            std::cout << "No world created or loaded.\n";
            return;
        }
        int x, y, state;
        std::cout << "Enter cell position (x y) and state (0 or 1): ";
        std::cin >> x >> y >> state;
        world->setCellState(x, y, state);
    }

    void getCell() {
        if (!world) {
            std::cout << "No world created or loaded.\n";
            return;
        }
        int x, y;
        std::cout << "Enter cell position (x, y): ";
        std::cin >> x >> y;
        std::cout << "Cell state: " << world->getCellState(x, y) << std::endl;
    }

    void addFigure() {
        if (!world) {
            std::cout << "No world created or loaded.\n";
            return;
        }
        int x, y;
        std::string figure;
        std::cout << "Enter figure (Glider, Toad, Beacon, Methuselah) and position (x, y): ";
        std::cin >> figure >> x >> y;
        // Assuming World class has these methods to add specific figures
        if (figure == "Glider") {
            world->addGlider(x, y);
        } else if (figure == "Toad") {
            world->addToad(x, y);
        } else if (figure == "Beacon") {
            world->addBeacon(x, y);
        } else if (figure == "Methuselah") {
            world->addMethuselah(x, y);
        } else {
            std::cout << "Invalid figure name.\n";
        }
    }

public:
    void start() {
        int choice = 0;
        do {
            std::cout << "1. Create world\n"
                      << "2. Load world\n"
                      << "3. Save world\n"
                      << "4. Toggle printing\n"
                      << "5. Set delay\n"
                      << "6. Run simulation\n"
                      << "7. Set cell state\n"
                      << "8. Get cell state\n"
                      << "9. Add figure\n"
                      << "0. Exit\n"
                      << "Enter choice: ";
            std::cin >> choice;
            switch (choice) {
                case 1: createWorld(); break;
                case 2: loadWorld(); break;
                case 3: saveWorld(); break;
                case 4: togglePrinting(); break;
                case 5: setDelay(); break;
                case 6: runSimulation(); break;
                case 7: setCell(); break;
                case 8: getCell(); break;
                case 9: addFigure(); break;
                case 0: break;
                default: std::cout << "Invalid choice, try again.\n";
            }
        } while (choice != 0);
        delete world;
    }
};

int main() {
    CLI cli;
    cli.start();
    return 0;
}
