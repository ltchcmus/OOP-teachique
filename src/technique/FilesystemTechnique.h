#ifndef FILESYSTEMTECHNIQUE_H
#define FILESYSTEMTECHNIQUE_H
#include "ITechnique.h"

class FilesystemTechnique : public ITechnique {
public:
    std::string name() const override { return "std::filesystem (C++17)"; }
    std::string description() const override { return "std::filesystem provides facilities for performing operations on file systems and their components."; }
    std::string codeSample() const override {
        return R"cpp(
#include <filesystem>
#include <iostream>
int main() {
    for (auto& p : std::filesystem::directory_iterator("."))
        std::cout << p.path() << std::endl;
}
)cpp";
    }
};

#endif // FILESYSTEMTECHNIQUE_H