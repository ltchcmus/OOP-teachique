#ifndef SHAREDMUTEXTECHNIQUE_H
#define SHAREDMUTEXTECHNIQUE_H
#include "ITechnique.h"

class SharedMutexTechnique : public ITechnique {
public:
    std::string name() const override { return "std::shared_mutex (C++17)"; }
    std::string description() const override { return "std::shared_mutex allows multiple readers or one writer at a time."; }
    std::string codeSample() const override {
        return R"cpp(
#include <shared_mutex>
#include <thread>
#include <iostream>
std::shared_mutex mtx;
void reader() { std::shared_lock lock(mtx); }
void writer() { std::unique_lock lock(mtx); }
)cpp";
    }
};

#endif // SHAREDMUTEXTECHNIQUE_H