cmake_minimum_required(VERSION 3.20)
project(Ruletka VERSION 2.0.0 LANGUAGES CXX)

option(BUILD_TESTS       "Build unit tests"                         ON)
option(ENABLE_CLANG_TIDY "Run clang-tidy during build"              OFF)
option(ENABLE_COVERAGE   "Enable coverage instrumentation"          OFF)
option(BUILD_FUZZERS     "Build libFuzzer harnesses"                OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND NOT MSVC)
    set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND CMAKE_CXX_SIMULATE_ID STREQUAL "MSVC")
    add_compile_options(/EHsc)
    add_compile_options(/Zc:__cplusplus)
endif()

if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy clang-tidy-18 clang-tidy-19 clang-tidy-17
    HINTS
        "$ENV{ProgramFiles}/LLVM/bin"
        "C:/Program Files/LLVM/bin"
        "/usr/bin"
        "/usr/lib/llvm-18/bin"
)
    if(CLANG_TIDY_EXE)
        message(STATUS "Found clang-tidy: ${CLANG_TIDY_EXE}")
        set(CMAKE_CXX_CLANG_TIDY
            "${CLANG_TIDY_EXE}"
            "--extra-arg-before=-fcxx-exceptions"
        )
    else()
        message(WARNING "clang-tidy not found — skipping static analysis.")
    endif()
endif()

find_package(SFML CONFIG REQUIRED COMPONENTS Graphics Window System Audio)
find_package(nlohmann_json CONFIG REQUIRED)

if(WIN32)
    find_package(boost_static_string CONFIG REQUIRED)
else()
    find_package(Boost REQUIRED COMPONENTS static_string)
endif()

if(BUILD_TESTS)
    find_package(GTest CONFIG REQUIRED)
endif()

add_subdirectory(src)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        message(FATAL_ERROR "ENABLE_COVERAGE requires GCC or Clang (not MSVC).")
    endif()
    target_compile_options(RuletkaLib PRIVATE --coverage -O0 -g)
    target_link_options(RuletkaLib PRIVATE --coverage)
    if(BUILD_TESTS)
        target_compile_options(RuletkaTESTS PRIVATE --coverage -O0 -g)
        target_link_options(RuletkaTESTS PRIVATE --coverage)
    endif()
endif()

if(BUILD_FUZZERS)
    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        message(FATAL_ERROR "BUILD_FUZZERS requires Clang (libFuzzer).")
    endif()
    if(NOT EXISTS "${CMAKE_SOURCE_DIR}/fuzz/CMakeLists.txt")
        message(FATAL_ERROR "BUILD_FUZZERS=ON but fuzz/CMakeLists.txt not found.")
    endif()
    add_subdirectory(fuzz)
endif()