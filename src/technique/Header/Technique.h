#ifndef TECHNIQUE_H
#define TECHNIQUE_H
#include <string>
#include <vector>

class Technique {
private:
    std::string name;
    std::string definition;
    std::string usage;
    std::string syntax;
    std::string demo_code;
    std::string cpp_version;
    std::string notes;
    std::string demo_note;
    std::vector<std::string> use_cases;
    std::vector<std::string> best_practices;
    std::vector<std::string> advantages;
    std::string expected_output;
public:
    Technique(const std::string& name, const std::string& definition,
              const std::string& usage, const std::string& syntax,
              const std::string& demo_code, const std::string& cpp_version = "",
              const std::string& notes = "", const std::string& demo_note = "",
              const std::vector<std::string>& use_cases = {},
              const std::vector<std::string>& best_practices = {},
              const std::vector<std::string>& advantages = {},
              const std::string& expected_output = "");
    const std::string& getName() const;
    const std::string& getDefinition() const;
    const std::string& getUsage() const;
    const std::string& getSyntax() const;
    const std::string& getDemoCode() const;
    const std::string& getCppVersion() const;
    const std::string& getNotes() const;
    const std::string& getDemoNote() const;
    const std::vector<std::string>& getUseCases() const;
    const std::vector<std::string>& getBestPractices() const;
    const std::vector<std::string>& getAdvantages() const;
    const std::string& getExpectedOutput() const;
};
#endif // TECHNIQUE_H 