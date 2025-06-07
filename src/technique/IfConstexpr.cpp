#include "IfConstexpr.h"

std::string IfConstexpr::name() const {
    return "if constexpr (C++17)";
}

std::string IfConstexpr::description() const {
    return "if constexpr allows compile-time branching, making generic code more efficient.";
}

std::string IfConstexpr::codeSample() const {
    return R"cpp(
template<typename T>
void printType(const T& value) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << value << " is integral\n";
    } else {
        std::cout << value << " is not integral\n";
    }
}
)cpp";
}