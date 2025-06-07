#ifndef PRINTTECHNIQUE_H
#define PRINTTECHNIQUE_H
#include "ITechnique.h"

class PrintTechnique : public ITechnique {
public:
    std::string name() const override { return "std::print (C++23)"; }
    std::string description() const override { return "std::print provides a simple way to print to stdout (like Python's print)."; }
    std::string codeSample() const override {
        return R"cpp(
// #include <print> (C++23)
// std::print("Hello {}!", "world");
)cpp";
    }
};

#endif // PRINTTECHNIQUE_H