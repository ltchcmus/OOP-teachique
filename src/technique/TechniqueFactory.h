#ifndef TECHNIQUEFACTORY_H
#define TECHNIQUEFACTORY_H
#include <vector>
#include <memory>
#include "ITechnique.h"

class TechniqueFactory {
public:
    static std::vector<std::unique_ptr<ITechnique>> createAll();
};

#endif // TECHNIQUEFACTORY_H