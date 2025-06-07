#ifndef STRUCTUREDBINDINGS_H
#define STRUCTUREDBINDINGS_H
#include "ITechnique.h"

class StructuredBindings : public ITechnique {
public:
    std::string name() const override;
    std::string description() const override;
    std::string codeSample() const override;
};

#endif // STRUCTUREDBINDINGS_H