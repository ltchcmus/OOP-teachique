#include "Menu.h"
#include "technique/TechniqueFactory.h"
#include "utils/InputHelper.h"
#include <iostream>

void Menu::run() {
    loadTechniques();
    while (true) {
        showMenu();
        handleInput();
    }
}

void Menu::showMenu() {
    std::cout << "\n===== C++ Modern Techniques Menu =====\n";
    for (size_t i = 0; i < techniques.size(); ++i) {
        std::cout << i + 1 << ". " << techniques[i]->name() << "\n";
    }
    std::cout << "0. Exit\n";
}

void Menu::handleInput() {
    int choice = InputHelper::getInt("Select a technique (0 to exit): ");
    if (choice == 0) {
        std::cout << "Goodbye!\n";
        exit(0);
    }
    if (choice > 0 && static_cast<size_t>(choice) <= techniques.size()) {
        techniques[choice - 1]->showInfo();
    } else {
        std::cout << "Invalid choice!\n";
    }
}

void Menu::loadTechniques() {
    techniques = TechniqueFactory::createAll();
}