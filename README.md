# Ruletka

[![CI](https://github.com/Scarlet002/Ruletka/actions/workflows/ci.yml/badge.svg)](https://github.com/Scarlet002/Ruletka/actions/workflows/ci.yml)
[![codecov](https://codecov.io/gh/Scarlet002/Ruletka/branch/main/graph/badge.svg)](https://codecov.io/gh/Scarlet002/Ruletka)
[![clang-tidy](https://img.shields.io/badge/clang--tidy-enabled-brightgreen.svg)](.clang-tidy)
[![ASan](https://img.shields.io/badge/ASan-enabled-brightgreen.svg)](.github/workflows/ci.yml)
[![UBSan](https://img.shields.io/badge/UBSan-enabled-brightgreen.svg)](.github/workflows/ci.yml)
[![libFuzzer](https://img.shields.io/badge/fuzzing-libFuzzer-orange.svg)](fuzz/)

[![C++23](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](https://en.cppreference.com/w/cpp/23)
[![CMake](https://img.shields.io/badge/CMake-3.20%2B-blue.svg)](https://cmake.org)
[![clang-cl](https://img.shields.io/badge/clang--cl-18%2B-blue.svg)](https://clang.llvm.org/)
[![vcpkg](https://img.shields.io/badge/vcpkg-manifest-blue.svg)](https://vcpkg.io)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![platform](https://img.shields.io/badge/platform-Windows-blue.svg)]()
[![arch](https://img.shields.io/badge/arch-x64-lightgrey.svg)]()

A turn-based game inspired by Buckshot Roulette, featuring a dynamic item system and AI opponents.

## Features

- Turn-based gameplay – Player and Computer take turns performing actions.
- Dynamic Magazine – Randomly generated at the start of each round (2 to 8 bullets, live/blanks).
- Health System – Each player starts with 5 HP.
- Item System – 6 unique items: Saw, Beer, Magnifier, Cellphone, Handcuffs, Inverter.
- AI Opponent – 3 difficulty levels (Easy, Normal, Hard) with separate strategies.
- Dual Interface – Console UI and SFML graphical UI.
- Serialization – Save and load game states in JSON or TXT format.
- Autosave – Asynchronous saves every turn using `std::jthread`.
- Data Validation – Full integrity checks on snapshots during save/load operations.

## Tech Stack

- Language: **C++23**
- Build system: **CMake ≥ 3.20 + Ninja + vcpkg** (manifest mode)
- Compiler: **clang-cl** (LLVM 18+) with MSVC ABI
- Libraries: **SFML 3**, **nlohmann/json**, **Boost.StaticString**
- Testing: **Google Test** + CTest
- Static analysis: **clang-tidy** + **clangd**
- Concurrency: `std::jthread`, `std::atomic`, `std::mutex`
- File system: `std::filesystem`
- Memory management: RAII, smart pointers

## Getting Started

### Quick Start

Download the latest executable (`.exe`) from the Releases tab and run it.

### Build from Source

**Prerequisites:**

- Visual Studio 2022 (MSVC toolchain)
- LLVM/Clang (clang-cl, clang-tidy)
- CMake ≥ 3.20
- Ninja
- vcpkg (clone to `C:/Program Files/Microsoft Visual Studio/2022/Community/VC/vcpkg` or set `VCPKG_ROOT`)

**Build:**

```bash
git clone https://github.com/Scarlet002/Ruletka.git
cd Ruletka
cmake --preset x64-debug-ninja
cmake --build build/x64-debug-ninja --parallel