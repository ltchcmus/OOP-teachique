#ifndef MENU_H
#define MENU_H
#include "TechniqueManager.h"

class Menu {
private:
    TechniqueManager& manager;
public:
    Menu(TechniqueManager& manager);
    void show();
    void clearTerminal() const;
    void showTechniqueDetail(const Technique& tech);
    void runDemo(const Technique& tech);
};

#endif // MENU_H 