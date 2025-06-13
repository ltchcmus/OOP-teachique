#include "../Header/Menu.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#ifdef _WIN32
#include <windows.h>
#endif

namespace {
    // ANSI color codes
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
}

Menu::Menu(TechniqueManager& manager) : manager(manager) {
    enableVirtualTerminal();
}

void Menu::clearTerminal() const {
    std::system("clear");
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
        const std::string line = "════════════════════════════════════════════════════════════════════════════════════════════════";
        const std::string thick_top = "╔" + line + "╗";
        const std::string thick_mid = "╟" + line + "╢";
        const std::string thick_sep = "╠" + line + "╣";
        const std::string thick_bot = "╚" + line + "╝";
        std::cout << CYAN << thick_top << RESET << "\n";
        
        std::cout << CYAN << "║" << RESET << BOLD << UNDERLINE << YELLOW << "  " << tech.getName() << RESET << "  (" << GREEN << tech.getCppVersion() << RESET << ")";
        size_t pad = line.size() - (tech.getName().size() + tech.getCppVersion().size() + 10);
        for (size_t i = 0; i < pad; ++i) std::cout << ' ';
        std::cout << CYAN << "║\n" << thick_mid << RESET << "\n";
    
        std::cout << CYAN << "║" << RESET << BOLD << MAGENTA << " Definition: " << RESET << tech.getDefinition();
        pad = line.size() - std::string(" Definition: ").size() - tech.getDefinition().size();
        for (size_t i = 0; i < pad; ++i) std::cout << ' ';
        std::cout << CYAN << "║\n";
   
        if (!tech.getUseCases().empty()) {
            std::cout << CYAN << "║" << RESET << BOLD << BLUE << " Use Cases:" << RESET;
            pad = line.size() - 11;
            for (size_t i = 0; i < pad; ++i) std::cout << ' ';
            std::cout << CYAN << "║\n";
            for (const auto& uc : tech.getUseCases()) {
                std::cout << CYAN << "║   - " << RESET << uc;
                pad = line.size() - 6 - uc.size();
                for (size_t i = 0; i < pad; ++i) std::cout << ' ';
                std::cout << CYAN << "║\n";
            }
        }
      
        std::cout << CYAN << "║" << RESET << BOLD << YELLOW << " Syntax: " << RESET << tech.getSyntax();
        pad = line.size() - std::string(" Syntax: ").size() - tech.getSyntax().size();
        for (size_t i = 0; i < pad; ++i) std::cout << ' ';
        std::cout << CYAN << "║\n";
        std::cout << CYAN << thick_sep << RESET << "\n";
        
        std::cout << CYAN << "║" << RESET << BOLD << UNDERLINE << RED << " Code Demo:" << RESET;
        pad = line.size() - 11;
        for (size_t i = 0; i < pad; ++i) std::cout << ' ';
        std::cout << CYAN << "║\n";
        std::istringstream code_stream(tech.getDemoCode());
        std::string code_line;
        while (std::getline(code_stream, code_line)) {
            std::cout << CYAN << "║   " << RESET << code_line;
            pad = line.size() - 3 - code_line.size();
            for (size_t i = 0; i < pad; ++i) std::cout << ' ';
            std::cout << CYAN << "║\n";
        }
        
        if (!tech.getExpectedOutput().empty()) {
            std::cout << CYAN << "║" << RESET << BOLD << GREEN << " Expected Output:" << RESET;
            pad = line.size() - 17;
            for (size_t i = 0; i < pad; ++i) std::cout << ' ';
            std::cout << CYAN << "║\n";
            std::istringstream out_stream(tech.getExpectedOutput());
            while (std::getline(out_stream, code_line)) {
                std::cout << CYAN << "║   " << RESET << GREEN << code_line << RESET;
                pad = line.size() - 3 - code_line.size();
                for (size_t i = 0; i < pad; ++i) std::cout << ' ';
                std::cout << CYAN << "║\n";
            }
        }
        
        if (!tech.getBestPractices().empty()) {
            std::cout << CYAN << "║" << RESET << BOLD << MAGENTA << " Best Practices:" << RESET;
            pad = line.size() - 16;
            for (size_t i = 0; i < pad; ++i) std::cout << ' ';
            std::cout << CYAN << "║\n";
            for (const auto& bp : tech.getBestPractices()) {
                std::cout << CYAN << "║   - " << RESET << bp;
                pad = line.size() - 6 - bp.size();
                for (size_t i = 0; i < pad; ++i) std::cout << ' ';
                std::cout << CYAN << "║\n";
            }
        }
        
        if (!tech.getAdvantages().empty()) {
            std::cout << CYAN << "║" << RESET << BOLD << YELLOW << " Advantages:" << RESET;
            pad = line.size() - 12;
            for (size_t i = 0; i < pad; ++i) std::cout << ' ';
            std::cout << CYAN << "║\n";
            for (const auto& adv : tech.getAdvantages()) {
                std::cout << CYAN << "║   - " << RESET << adv;
                pad = line.size() - 6 - adv.size();
                for (size_t i = 0; i < pad; ++i) std::cout << ' ';
                std::cout << CYAN << "║\n";
            }
        }
        
        if (!tech.getNotes().empty()) {
            std::istringstream notes_stream(tech.getNotes());
            while (std::getline(notes_stream, code_line)) {
                std::cout << CYAN << "║" << RESET << BOLD << BLUE << " Note: " << RESET << code_line;
                pad = line.size() - 7 - code_line.size();
                for (size_t i = 0; i < pad; ++i) std::cout << ' ';
                std::cout << CYAN << "║\n";
            }
        }
        
        if (!tech.getDemoNote().empty()) {
            std::istringstream demo_note_stream(tech.getDemoNote());
            while (std::getline(demo_note_stream, code_line)) {
                std::cout << CYAN << "║" << RESET << BOLD << UNDERLINE << RED << " [Demo Note] " << RESET << code_line;
                pad = line.size() - 13 - code_line.size();
                for (size_t i = 0; i < pad; ++i) std::cout << ' ';
                std::cout << CYAN << "║\n";
            }
        }
        std::cout << CYAN << thick_bot << RESET << "\n";
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
    int compile = std::system(("g++ " + filename + " -o demo_temp.out 2> demo_temp.err").c_str());
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