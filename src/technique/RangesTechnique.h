#ifndef RANGESTECHNIQUE_H
#define RANGESTECHNIQUE_H
#include "ITechnique.h"

class RangesTechnique : public ITechnique {
public:
    std::string name() const override { return "Ranges (C++20)"; }
    std::string description() const override { return "Ranges provide composable views and actions for containers."; }
    std::string codeSample() const override {
        return R"cpp(
#include <ranges>
#include <vector>
#include <iostream>
int main() {
    std::vector<int> v{1,2,3,4};
    for (int i : v | std::ranges::views::filter([](int x){return x%2==0;}))
        std::cout << i << std::endl;
}
)cpp";
    }
};

#endif // RANGESTECHNIQUE_H