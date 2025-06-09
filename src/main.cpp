#include "technique/Header/TechniqueManager.h"
#include "technique/Header/Menu.h"
#include <iostream>
#include <fstream>

int main() {
    TechniqueManager manager;
    // Try both possible paths
    if (!manager.loadFromJson("../src/technique/techniques.json") &&
        !manager.loadFromJson("src/technique/techniques.json")) {
        std::cerr << "Không thể load file JSON kỹ thuật!\n";
        return 1;
    }
    Menu menu(manager);
    menu.show();
    return 0;
}