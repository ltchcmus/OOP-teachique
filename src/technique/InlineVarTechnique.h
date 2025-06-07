#ifndef INLINEVARTECHNIQUE_H
#define INLINEVARTECHNIQUE_H
#include "ITechnique.h"

class InlineVarTechnique : public ITechnique {
public:
    std::string name() const override { return "Inline Variables (C++17)"; }
    std::string description() const override { return "Inline variables allow definition of variables in header files without violating ODR."; }
    std::string codeSample() const override {
        return R"cpp(
struct S { static inline int x = 5; };
int main() { S s; std::cout << S::x << std::endl; }
)cpp";
    }
};

#endif // INLINEVARTECHNIQUE_H