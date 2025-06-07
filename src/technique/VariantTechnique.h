#ifndef VARIANTTECHNIQUE_H
#define VARIANTTECHNIQUE_H
#include "ITechnique.h"

class VariantTechnique : public ITechnique {
public:
    std::string name() const override { return "std::variant (C++17)"; }
    std::string description() const override { return "std::variant is a type-safe union, can hold one of several types."; }
    std::string codeSample() const override {
        return R"cpp(
#include <variant>
#include <iostream>
std::variant<int, double> v = 12.5;
std::visit([](auto&& arg){ std::cout << arg << std::endl; }, v);
)cpp";
    }
};

#endif // VARIANTTECHNIQUE_H