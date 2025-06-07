#ifndef OPTIONALTECHNIQUE_H
#define OPTIONALTECHNIQUE_H
#include "ITechnique.h"

class OptionalTechnique : public ITechnique {
public:
    std::string name() const override { return "std::optional (C++17)"; }
    std::string description() const override { return "std::optional represents an optional value (may or may not be present)."; }
    std::string codeSample() const override {
        return R"cpp(
#include <optional>
#include <iostream>
std::optional<int> get(bool ok) { return ok ? 42 : std::nullopt; }
int main() {
    auto v = get(true);
    if (v) std::cout << *v << std::endl;
}
)cpp";
    }
};

#endif // OPTIONALTECHNIQUE_H