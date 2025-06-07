#ifndef DEDUCINGTHISTECHNIQUE_H
#define DEDUCINGTHISTECHNIQUE_H
#include "ITechnique.h"

class DeducingThisTechnique : public ITechnique {
public:
    std::string name() const override { return "deducing this (C++23)"; }
    std::string description() const override { return "deducing this allows deduction of the type of *this in member functions."; }
    std::string codeSample() const override {
        return R"cpp(
// struct Point {
// void set_x(this Point& self, int x) { self.x = x; }
// };
)cpp";
    }
};

#endif // DEDUCINGTHISTECHNIQUE_H