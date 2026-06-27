# Ruletka

Gra w rosyjską ruletkę inspirowana **Buckshot Roulette**. Dostępna w dwóch interfejsach: konsolowym oraz SFML. System przedmiotów (6 rodzajów) wpływa na dynamikę rozgrywki, a AI oferuje 3 poziomy trudności.

## Funkcjonalności

- Tryb turowy – gracz i komputer naprzemiennie wykonują akcje
- Magazynek – losowo generowany na początku każdej rundy (od 2 do 8 naboi, pełne/puste)
- System punktów życia – każdy gracz ma 5 HP
- Przedmioty – 6 rodzajów: piła, piwo, lupa, telefon, kajdanki, inwerter
- Sztuczna inteligencja – 3 poziomy trudności (Łatwy, Normalny, Trudny)
- Dwa interfejsy – konsolowy (ConsoleUI) oraz graficzny (SFML)
- Serializacja – zapis i odczyt stanu gry w formacie JSON lub TXT
- Autozapis – asynchroniczny zapis co turę (osobny wątek)
- Walidacja danych – pełne sprawdzanie poprawności przy zapisie/odczycie

<<<<<<< Updated upstream
## Technologie
=======
- Turn-based gameplay – Player and Computer take turns performing actions.
- Dynamic Magazine – Randomly generated at the start of each round (2 to 8 bullets, live/blanks).
- Health System – Each player starts with 5 HP.
- Item System – 6 unique items: Saw, Beer, Magnifier, Cellphone, Handcuffs, Inverter.
- AI Opponent – 3 difficulty levels (Easy, Normal, Hard).
- Dual Interface – Console UI and SFML graphical UI.
- Serialization – Save and load game states in JSON or TXT format.
- Autosave – Asynchronous saves every turn using a separate thread (std::async).
- Data Validation – Full integrity checks during save/load operations.
>>>>>>> Stashed changes

- C++17
- SFML
- nlohmann/json
- std::async, std::atomic, std::mutex
- std::filesystem
- RAII, smart pointers

## Uruchomienie

### Szybki start

Pobierz plik `.exe` z zakładki **Releases** i uruchom.

### Kompilacja (Visual Studio)

<<<<<<< Updated upstream
1. Pobierz SFML: https://www.sfml-dev.org/
2. Pobierz nlohmann/json (header-only): https://github.com/nlohmann/json/releases
3. Otwórz plik `.sln` w Visual Studio
4. Skonfiguruj ścieżki do SFML (include, lib) w ustawieniach projektu
5. Skopiuj pliki DLL z SFML do folderu z `.exe`
6. Uruchom
=======
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
6. Build and run the project.
>>>>>>> Stashed changes

Po uruchomieniu gra zapyta o:
- Nazwę gracza
- Wybór interfejsu (1 – konsola, 2 – SFML)
- Format serializacji (JSON/TXT)
- Poziom trudności AI (Normalny, Łatwy, Trudny)

## Zapis gry

- `data/saves/` – zapisy ręczne
- `data/saves/autosaves/` – autozapisy

Formaty: `.json` lub `.txt`.

## Wzorce projektowe

<<<<<<< Updated upstream
- **Strategy** – strategie AI (EasyAI, NormalAI, HardAI) oraz formaty serializacji (JSON, TXT)
- **Command** – wszystkie akcje w grze (Heal, Shoot, UseItem, SaveGame, LoadGame, AutoSave, Restart, Exit)
- **Observer** – system logowania (Logger + UI jako obserwator)
- **State** – zarządzanie stanem gry i turami (TurnManager)
- **Dependency Injection** – wszystkie zależności wstrzykiwane przez konstruktor
=======
Example format:
![Console Interface](screenshots/Console.png)
![SFML Interface](screenshots/SFML.png)

## Architecture & Design Patterns

The project is built using a modular, object-oriented architecture, leveraging multiple design patterns:

- Strategy – AI behavior (AIManager) and serialization formats (SerializationManager).
- Command – All game actions (Heal, Shoot, UseItem, Exit, etc).
- Observer – Logging system (Logger + UI are observers of game events).
- State – GameState.
- Dependency Injection – All dependencies are injected via constructors, making unit testing easier.

## Testing

Unit tests are located in the RuletkaTESTS folder and are built using the Google Test framework. 
To run the tests, simply open the solution in Visual Studio and select Test > Run All Tests (or use vstest.console.exe).

## Future Plans

- Add a local multiplayer mode.
- Improve the SFML and console UI.
- Migrate the build system to CMake for cross-platform support.

## License

This project is licensed under the MIT License – see the LICENSE file for details.
>>>>>>> Stashed changes
