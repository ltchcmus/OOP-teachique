#ifndef SPANTECHNIQUE_H
#define SPANTECHNIQUE_H
#include "ITechnique.h"

class SpanTechnique : public ITechnique {
public:
    std::string name() const override { return "std::span (C++20)"; }
    std::string description() const override { return "std::span is a non-owning view over a contiguous sequence of objects."; }
    std::string codeSample() const override {
        return R"cpp(
#include <span>
#include <vector>
#include <iostream>
void print(std::span<int> s) { for(int i : s) std::cout << i << ' '; }
int main() { std::vector<int> v{1,2,3}; print(v); }
)cpp";
    }
};

#endif // SPANTECHNIQUE_H