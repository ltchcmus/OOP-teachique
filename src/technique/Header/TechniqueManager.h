#ifndef TECHNIQUEMANAGER_H
#define TECHNIQUEMANAGER_H
#include <vector>
#include <string>
#include "Technique.h"

class TechniqueManager {
private:
    std::vector<Technique> techniques;
public:
    bool loadFromJson(const std::string& filename);
    const std::vector<Technique>& getTechniques() const;
    static std::string joinVector(const std::vector<std::string>& vec, const std::string& sep);
};

#endif // TECHNIQUEMANAGER_H 