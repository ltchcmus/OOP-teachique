#include "StructuredBindings.h"

std::string StructuredBindings::name() const {
    return "Structured Bindings (C++17)";
}

std::string StructuredBindings::description() const {
    return "Structured bindings allow you to assign multiple variables at once from tuple, pair, array, ...\n"
           "Helps code be more concise and readable.";
}

std::string StructuredBindings::codeSample() const {
    return R"cpp(
#include <tuple>
#include <iostream>
int main() {
    std::tuple<int, double, std::string> t{1, 3.14, "hello"};
    auto [i, d, s] = t;
    std::cout << i << ", " << d << ", " << s << std::endl;
    return 0;
}
)cpp";
}