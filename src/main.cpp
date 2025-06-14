#include "technique/Header/TechniqueManager.h"
#include "technique/Header/Menu.h"
#include <iostream>
#include <fstream>
#include <filesystem>

int main() {
    TechniqueManager manager;
    // Try multiple possible paths
    std::vector<std::string> possiblePaths = {
        "src/technique/techniques.json",
        "../src/technique/techniques.json",
        "./src/technique/techniques.json",
        "techniques.json"
    };

    bool loaded = false;
    for (const auto& path : possiblePaths) {
        if (manager.loadFromJson(path)) {
            loaded = true;
            break;
        }
    }

    if (!loaded) {
        std::cerr << "Không thể load file JSON kỹ thuật!\n";
        return 1;
    }

    Menu menu(manager);
    menu.show();
    return 0;
}