#include "../Header/TechniqueManager.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool TechniqueManager::loadFromJson(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    json j;
    file >> j;
    techniques.clear();
    if (!j.contains("cpp_modern_features")) return false;
    auto& features_root = j["cpp_modern_features"];
    for (const auto& version_key : {"cpp17_features", "cpp20_features", "cpp23_features"}) {
        if (!features_root.contains(version_key)) continue;
        const auto& version = features_root[version_key];
        std::string cpp_version = version.value("version", "");
        if (!version.contains("features")) continue;
        for (const auto& item : version["features"]) {
            std::string name = item.value("name", "");
            std::string definition = item.value("definition", "");
            std::string usage;
            if (item.contains("primary_use_cases")) {
                usage = "- " + joinVector(item["primary_use_cases"].get<std::vector<std::string>>(), "\n- ");
            }
            std::string syntax;
            if (item.contains("syntax")) {
                if (item["syntax"].is_object()) {
                    for (auto it = item["syntax"].begin(); it != item["syntax"].end(); ++it) {
                        syntax += it.key() + ": " + it.value().get<std::string>() + "\n";
                    }
                } else if (item["syntax"].is_string()) {
                    syntax = item["syntax"].get<std::string>();
                }
            }
            std::string demo_code;
            std::string expected_output;
            if (item.contains("complete_demo")) {
                if (item["complete_demo"].contains("code"))
                    demo_code = item["complete_demo"]["code"].get<std::string>();
                if (item["complete_demo"].contains("expected_output"))
                    expected_output = item["complete_demo"]["expected_output"].get<std::string>();
            }
            std::string notes;
            if (item.contains("category")) notes += "Category: " + item["category"].get<std::string>() + "\n";
            if (item.contains("complexity_level")) notes += "Level: " + item["complexity_level"].get<std::string>() + "\n";
            if (item.contains("key_improvements")) notes += "Improvements: " + item["key_improvements"].get<std::string>() + "\n";
            std::string demo_note;
            std::vector<std::string> use_cases;
            if (item.contains("primary_use_cases")) use_cases = item["primary_use_cases"].get<std::vector<std::string>>();
            std::vector<std::string> best_practices;
            if (item.contains("best_practices")) best_practices = item["best_practices"].get<std::vector<std::string>>();
            std::vector<std::string> advantages;
            if (item.contains("advantages")) advantages = item["advantages"].get<std::vector<std::string>>();
            techniques.emplace_back(
                name, definition, usage, syntax, demo_code, cpp_version, notes, demo_note,
                use_cases, best_practices, advantages, expected_output
            );
        }
    }
    return true;
}

// Helper function to join vector<string> with separator
std::string TechniqueManager::joinVector(const std::vector<std::string>& vec, const std::string& sep) {
    std::string result;
    for (size_t i = 0; i < vec.size(); ++i) {
        result += vec[i];
        if (i + 1 < vec.size()) result += sep;
    }
    return result;
}

const std::vector<Technique>& TechniqueManager::getTechniques() const {
    return techniques;
} 