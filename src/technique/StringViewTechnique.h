#ifndef STRINGVIEWTECHNIQUE_H
#define STRINGVIEWTECHNIQUE_H
#include "ITechnique.h"

class StringViewTechnique : public ITechnique {
public:
    std::string name() const override { return "std::string_view (C++17)"; }
    std::string description() const override { return "std::string_view is a lightweight, non-owning view of a string."; }
    std::string codeSample() const override {
        return R"cpp(
#include <string_view>
#include <iostream>
void print(std::string_view sv) { std::cout << sv << std::endl; }
int main() { print("hello"sv); }
)cpp";
    }
};

#endif // STRINGVIEWTECHNIQUE_H