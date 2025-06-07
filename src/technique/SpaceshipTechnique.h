#ifndef SPACESHIPTECHNIQUE_H
#define SPACESHIPTECHNIQUE_H
#include "ITechnique.h"

class SpaceshipTechnique : public ITechnique {
public:
    std::string name() const override { return "Three-way comparison (C++20)"; }
    std::string description() const override { return "The <=> operator provides automatic generation of comparison operators."; }
    std::string codeSample() const override {
        return R"cpp(
#include <compare>
struct A { int x; auto operator<=>(const A&) const = default; };
)cpp";
    }
};

#endif // SPACESHIPTECHNIQUE_H