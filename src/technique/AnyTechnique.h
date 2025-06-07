#ifndef ANYTECHNIQUE_H
#define ANYTECHNIQUE_H
#include "ITechnique.h"

class AnyTechnique : public ITechnique {
public:
    std::string name() const override { return "std::any (C++17)"; }
    std::string description() const override { return "std::any can hold a value of any type."; }
    std::string codeSample() const override {
        return R"cpp(
#include <any>
#include <iostream>
std::any a = 5;
std::cout << std::any_cast<int>(a) << std::endl;
)cpp";
    }
};

#endif // ANYTECHNIQUE_H