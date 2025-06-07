#ifndef MENU_H
#define MENU_H
#include <vector>
#include <memory>
#include <string>
#include "technique/ITechnique.h"

class Menu {
public:
    void run();
private:
    std::vector<std::unique_ptr<ITechnique>> techniques;
    void showMenu();
    void handleInput();
    void loadTechniques();
};

#endif // MENU_H