#ifndef ITECHNIQUE_H
#define ITECHNIQUE_H
#include <string>
#include <iostream>

class ITechnique {
public:
    virtual ~ITechnique() = default;
    virtual std::string name() const = 0;
    virtual std::string description() const = 0;
    virtual std::string codeSample() const = 0;
    virtual void showInfo() const {
        std::cout << "\n--- " << name() << " ---\n";
        std::cout << description() << "\n";
        std::cout << "\nSample code:\n" << codeSample() << "\n";
    }
};

#endif // ITECHNIQUE_H