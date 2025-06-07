#ifndef FORMATTECHNIQUE_H
#define FORMATTECHNIQUE_H
#include "ITechnique.h"

class FormatTechnique : public ITechnique {
public:
    std::string name() const override { return "std::format (C++20)"; }
    std::string description() const override { return "std::format provides Python-like string formatting."; }
    std::string codeSample() const override {
        return R"cpp(
#include <format>
#include <iostream>
int main() {
    std::cout << std::format("Hello {}!", "world") << std::endl;
}
)cpp";
    }
};

#endif // FORMATTECHNIQUE_H