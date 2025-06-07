#ifndef EXPECTEDTECHNIQUE_H
#define EXPECTEDTECHNIQUE_H
#include "ITechnique.h"

class ExpectedTechnique : public ITechnique {
public:
    std::string name() const override { return "std::expected (C++23)"; }
    std::string description() const override { return "std::expected is for error handling, representing a value or an error."; }
    std::string codeSample() const override {
        return R"cpp(
// #include <expected> (C++23)
// std::expected<int, std::string> f(bool ok) { return ok ? 42 : std::unexpected("error"); }
)cpp";
    }
};

#endif // EXPECTEDTECHNIQUE_H