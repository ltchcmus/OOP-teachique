#include "../Header/Technique.h"

Technique::Technique(const std::string& name, const std::string& definition,
                     const std::string& usage, const std::string& syntax,
                     const std::string& demo_code, const std::string& cpp_version,
                     const std::string& notes, const std::string& demo_note,
                     const std::vector<std::string>& use_cases,
                     const std::vector<std::string>& best_practices,
                     const std::vector<std::string>& advantages,
                     const std::string& expected_output)
    : name(name), definition(definition), usage(usage), syntax(syntax), demo_code(demo_code),
      cpp_version(cpp_version), notes(notes), demo_note(demo_note),
      use_cases(use_cases), best_practices(best_practices), advantages(advantages),
      expected_output(expected_output) {}

const std::string& Technique::getName() const {
    return name;
}
const std::string& Technique::getDefinition() const {
    return definition;
}
const std::string& Technique::getUsage() const {
    return usage;
}
const std::string& Technique::getSyntax() const {
    return syntax;
}
const std::string& Technique::getDemoCode() const {
    return demo_code;
}
const std::string& Technique::getCppVersion() const {
    return cpp_version;
}
const std::string& Technique::getNotes() const {
    return notes;
}
const std::string& Technique::getDemoNote() const {
    return demo_note;
}
const std::vector<std::string>& Technique::getUseCases() const {
    return use_cases;
}
const std::vector<std::string>& Technique::getBestPractices() const {
    return best_practices;
}
const std::vector<std::string>& Technique::getAdvantages() const {
    return advantages;
}
const std::string& Technique::getExpectedOutput() const {
    return expected_output;
} 