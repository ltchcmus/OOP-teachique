#include "../Header/Menu.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>  
#include <string>   
#include <filesystem>
#ifdef _WIN32
#include <windows.h>
#endif

namespace {
    
    const char* CYAN = "\033[36m";
    const char* YELLOW = "\033[33m";
    const char* GREEN = "\033[32m";
    const char* RED = "\033[31m";
    const char* RESET = "\033[0m";
    const char* BOLD = "\033[1m";
    const char* UNDERLINE = "\033[4m";
    const char* MAGENTA = "\033[35m";
    const char* BLUE = "\033[34m";
    void enableVirtualTerminal() {
    #ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut != INVALID_HANDLE_VALUE) {
            DWORD dwMode = 0;
            GetConsoleMode(hOut, &dwMode);
            SetConsoleMode(hOut, dwMode | 0x0004);
        }
    #endif
    }

    std::string getExecutablePath() {
        return std::filesystem::current_path().string();
    }
}

Menu::Menu(TechniqueManager& manager) : manager(manager) {
    enableVirtualTerminal();
}

void Menu::clearTerminal() const {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void Menu::show() {
    while (true) {
        clearTerminal();
        const auto& techniques = manager.getTechniques();
        std::cout << BOLD << CYAN << "==================== MODERN C++ TECHNIQUES ====================" << RESET << "\n";
        for (size_t i = 0; i < techniques.size(); ++i) {
            std::cout << GREEN << (i + 1) << ". " << RESET << techniques[i].getName() << "\n";
        }
        std::cout << YELLOW << "0. Exit" << RESET << "\n";
        std::cout << "\nSelect a technique: ";
        int choice;
        std::cin >> choice;
        if (choice == 0) break;
        if (choice < 1 || choice > (int)techniques.size()) continue;
        showTechniqueDetail(techniques[choice - 1]);
    }
}

void Menu::showTechniqueDetail(const Technique& tech) {
    while (true) {
        clearTerminal();
        std::cout << BOLD << UNDERLINE << YELLOW << "  " << tech.getName() << RESET << "  (" << GREEN << tech.getCppVersion() << RESET << ")\n";
    
        std::cout << BOLD << MAGENTA << " Definition: " << RESET << tech.getDefinition() << "\n";
   
        if (!tech.getUseCases().empty()) {
            std::cout << BOLD << BLUE << " Use Cases:" << RESET << "\n";
            for (const auto& uc : tech.getUseCases()) {
                std::cout << "  - " << RESET << uc << "\n";
            }
        }
      
        std::cout << BOLD << YELLOW << " Syntax: " << RESET << tech.getSyntax() << "\n";
        
        std::cout << BOLD << UNDERLINE << RED << " Code Demo:" << RESET << "\n";
        std::istringstream code_stream(tech.getDemoCode());
        std::string code_line;
        while (std::getline(code_stream, code_line)) {
            std::cout << "  " << RESET << code_line << "\n";
        }
        
        if (!tech.getExpectedOutput().empty()) {
            std::cout << BOLD << GREEN << " Expected Output:" << RESET << "\n";
            std::istringstream out_stream(tech.getExpectedOutput());
            while (std::getline(out_stream, code_line)) {
                std::cout << "  " << RESET << GREEN << code_line << RESET << "\n";
            }
        }
        
        if (!tech.getBestPractices().empty()) {
            std::cout << BOLD << MAGENTA << " Best Practices:" << RESET << "\n";
            for (const auto& bp : tech.getBestPractices()) {
                std::cout << "  - " << RESET << bp << "\n";
            }
        }
        
        if (!tech.getAdvantages().empty()) {
            std::cout << BOLD << YELLOW << " Advantages:" << RESET << "\n";
            for (const auto& adv : tech.getAdvantages()) {
                std::cout << "  - " << RESET << adv << "\n";
            }
        }
        
        if (!tech.getNotes().empty()) {
            std::istringstream notes_stream(tech.getNotes());
            while (std::getline(notes_stream, code_line)) {
                std::cout << BOLD << BLUE << " Note: " << RESET << code_line << "\n";
            }
        }
        
        if (!tech.getDemoNote().empty()) {
            std::istringstream demo_note_stream(tech.getDemoNote());
            while (std::getline(demo_note_stream, code_line)) {
                std::cout << BOLD << UNDERLINE << RED << " [Demo Note] " << RESET << code_line << "\n";
            }
        }
        std::cout << "\n" << GREEN << "1. Run code demo" << RESET << "\n" << YELLOW << "0. Back to menu" << RESET << "\nSelect: ";
        int opt;
        std::cin >> opt;
        if (opt == 0) break;
        if (opt == 1) runDemo(tech);
    }
}

void Menu::runDemo(const Technique& tech) {
    clearTerminal();
    std::string filename = "demo_temp.cpp";
    std::ofstream ofs(filename);
    ofs << tech.getDemoCode();
    ofs.close();
    std::cout << CYAN << "Compiling and running demo..." << RESET << "\n";

    // Tự động chọn chuẩn C++ phù hợp
    std::string std_flag = "-std=c++17";
    std::string code = tech.getDemoCode();
    if (code.find("#include <coroutine>") != std::string::npos ||
        code.find("#include <concepts>") != std::string::npos ||
        code.find("#include <ranges>") != std::string::npos ||
        code.find("<=>") != std::string::npos ||
        code.find("concept ") != std::string::npos) {
        std_flag = "-std=c++20";
    }
    if (code.find("this Self&&") != std::string::npos ||
        code.find("#include <expected>") != std::string::npos ||
        code.find(",") != std::string::npos) { // C++23 features
        std_flag = "-std=c++23";
    }

    int compile = std::system(("g++ " + filename + " " + std_flag + " -o demo_temp.out 2> demo_temp.err").c_str());
    if (compile != 0) {
        std::ifstream err("demo_temp.err");
        std::cout << RED << "[Compilation Error]\n" << err.rdbuf() << RESET << std::endl;
        err.close();
    } else {
        std::cout << GREEN << "[Program Output]" << RESET << "\n";
        std::system("./demo_temp.out");
    }
    std::remove("demo_temp.cpp");
    std::remove("demo_temp.out");
    std::remove("demo_temp.err");
    std::cout << CYAN << "\nPress Enter to continue..." << RESET;
    std::cin.ignore();
    std::cin.get();
} 