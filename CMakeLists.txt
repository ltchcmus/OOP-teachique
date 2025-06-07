cmake_minimum_required(VERSION 3.20)
project(cpp_modern_techniques VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(cpp_modern_techniques
    src/main.cpp
    src/menu/Menu.cpp
    src/technique/TechniqueFactory.cpp
    src/technique/StructuredBindings.cpp
    src/technique/IfConstexpr.cpp
    src/utils/InputHelper.cpp
)

target_include_directories(cpp_modern_techniques PRIVATE src) 