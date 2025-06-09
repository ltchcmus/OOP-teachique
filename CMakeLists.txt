cmake_minimum_required(VERSION 3.20)
project(cpp_modern_techniques VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(cpp_modern_techniques
    src/main.cpp
    src/technique/Impl/Menu.cpp
    src/technique/Impl/TechniqueManager.cpp
    src/technique/Impl/Technique.cpp
)

target_include_directories(cpp_modern_techniques PRIVATE src)
# nlohmann_json is header-only, you can install it via package manager or add json.hpp to your project
find_package(nlohmann_json 3.2.0 REQUIRED)
target_link_libraries(cpp_modern_techniques PRIVATE nlohmann_json::nlohmann_json) 