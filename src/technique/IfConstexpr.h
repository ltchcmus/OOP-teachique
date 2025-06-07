#ifndef IFCONSTEXPR_H
#define IFCONSTEXPR_H
#include "ITechnique.h"

class IfConstexpr : public ITechnique {
public:
    std::string name() const override;
    std::string description() const override;
    std::string codeSample() const override;
};

#endif // IFCONSTEXPR_H