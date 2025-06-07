#ifndef COROUTINESTECHNIQUE_H
#define COROUTINESTECHNIQUE_H
#include "ITechnique.h"

class CoroutinesTechnique : public ITechnique {
public:
    std::string name() const override { return "Coroutines (C++20)"; }
    std::string description() const override { return "Coroutines allow writing asynchronous code in a synchronous style."; }
    std::string codeSample() const override {
        return R"cpp(
#include <coroutine>
// ... coroutine code ...
)cpp";
    }
};

#endif // COROUTINESTECHNIQUE_H