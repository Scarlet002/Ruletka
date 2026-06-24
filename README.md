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

## Technologie

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

1. Pobierz SFML: https://www.sfml-dev.org/
2. Pobierz nlohmann/json (header-only): https://github.com/nlohmann/json/releases
3. Otwórz plik `.sln` w Visual Studio
4. Skonfiguruj ścieżki do SFML (include, lib) w ustawieniach projektu
5. Skopiuj pliki DLL z SFML do folderu z `.exe`
6. Uruchom

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

- **Strategy** – strategie AI (EasyAI, NormalAI, HardAI) oraz formaty serializacji (JSON, TXT)
- **Command** – wszystkie akcje w grze (Heal, Shoot, UseItem, SaveGame, LoadGame, AutoSave, Restart, Exit)
- **Observer** – system logowania (Logger + UI jako obserwator)
- **State** – zarządzanie stanem gry i turami (TurnManager)
- **Dependency Injection** – wszystkie zależności wstrzykiwane przez konstruktor