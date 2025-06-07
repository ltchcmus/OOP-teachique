#ifndef CONCEPTSTECHNIQUE_H
#define CONCEPTSTECHNIQUE_H
#include "ITechnique.h"

class ConceptsTechnique : public ITechnique {
public:
    std::string name() const override { return "Concepts (C++20)"; }
    std::string description() const override { return "Concepts allow constraining template parameters."; }
    std::string codeSample() const override {
        return R"cpp(
template<typename T> concept Addable = requires(T a, T b) { a + b; };
void add(Addable auto a, Addable auto b) { std::cout << a + b << std::endl; }
)cpp";
    }
};

#endif // CONCEPTSTECHNIQUE_H