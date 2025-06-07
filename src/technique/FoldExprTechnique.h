#ifndef FOLDEXPRTECHNIQUE_H
#define FOLDEXPRTECHNIQUE_H
#include "ITechnique.h"

class FoldExprTechnique : public ITechnique {
public:
    std::string name() const override { return "Fold Expressions (C++17)"; }
    std::string description() const override { return "Fold expressions allow easy expansion of parameter packs."; }
    std::string codeSample() const override {
        return R"cpp(
template<typename... Args>
auto sum(Args... args) { return (... + args); }
int main() { std::cout << sum(1,2,3) << std::endl; }
)cpp";
    }
};

#endif // FOLDEXPRTECHNIQUE_H