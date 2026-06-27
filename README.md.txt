# Ruletka

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![C++](https://img.shields.io/badge/C++-17-blue)

A turn-based game inspired by Buckshot Roulette, featuring a dynamic item system and AI opponents. 
This project was developed to demonstrate modern C++17 techniques, software design patterns, and multi-threading.

## Features

- Turn-based gameplay – Player and Computer take turns performing actions.
- Dynamic Magazine – Randomly generated at the start of each round (2 to 8 bullets, live/blanks).
- Health System – Each player starts with 5 HP.
- Item System – 6 unique items: Saw, Beer, Magnifying Glass, Phone, Handcuffs, Inverter.
- AI Opponent – 3 difficulty levels (Easy, Normal, Hard).
- Dual Interface – Console UI and SFML graphical UI.
- Serialization – Save and load game states in JSON or TXT format.
- Autosave – Asynchronous saves every turn using a separate thread (std::async).
- Data Validation – Full integrity checks during save/load operations.

## Tech Stack

- Language: C++17
- Libraries: SFML, nlohmann/json (header-only)
- Concurrency: std::async, std::atomic, std::mutex
- File System: std::filesystem
- Memory Management: RAII, Smart Pointers

## Getting Started

### Quick Start
Download the latest executable (.exe) from the Releases tab and run it.

### Build from Source (Visual Studio)

1. Clone the repository:
   git clone https://github.com/Scarlet002/Ruletka.git
2. Open the .sln file in Visual Studio.
3. Download and configure dependencies:
   - SFML: Download from sfml-dev.org
   - nlohmann/json: Download the single_include header from GitHub
4. Configure the project properties:
   - Add the include paths to the project settings.
   - Add the lib paths to the linker settings.
5. Copy the SFML .dll files into the same folder as the generated .exe.
6. Build and run the project (Ctrl + F5).

Note: On launch, the application will prompt you for:
- Player name
- Interface type (1 for Console, 2 for SFML)
- Serialization format (JSON/TXT)
- AI difficulty (Normal, Easy, Hard)

## Save System

- data/saves/ – Manual saves
- data/saves/autosaves/ – Autosaves

Supported formats: .json and .txt.

## Screenshots

Example format:
![Console Interface](screenshots/Console.png)
![SFML Interface](screenshots/SFML.png)

## Architecture & Design Patterns

The project is built using a modular, object-oriented architecture, leveraging multiple design patterns:

- Strategy – AI behavior (EasyAI, NormalAI, HardAI) and serialization formats (JSONStrategy, TXTStrategy).
- Command – All game actions (Heal, Shoot, UseItem, SaveGame, LoadGame, AutoSave, Restart, Exit).
- Observer – Logging system (Logger + UI are observers of game events).
- State – Game state and turn management (TurnManager).
- Dependency Injection – All dependencies are injected via constructors, making unit testing easier.

## Testing

Unit tests are located in the RuletkaTESTS folder and are built using the Google Test framework. 
To run the tests, simply open the solution in Visual Studio and select Test > Run All Tests (or use vstest.console.exe).

## Future Plans

- Add a local multiplayer mode.
- Improve the AI logic on the Hard difficulty.
- Migrate the build system to CMake for cross-platform support.
- Add more items and event cards for increased replayability.

## License

This project is licensed under the MIT License – see the LICENSE file for details.