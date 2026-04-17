#include "IGameEngine.h"
#include "GameEngine.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

// Zrobic GameState dla Stanu gry i ujednolicić go z GameSnapshot [1]
// Zrefaktoryzowac GameConsoleVersion (ujednolicic metody, rozbic na mniejsze klasy, zmniejszyc zaleznosci)
// Zrefaktoryzowac wersje dla SFML
// Dodac testy
// Poprawic Syntax i poprawnosc konstruktorow, wskaznikow, usunac ostrzeżenia, etc
// Zoptymalizowac objetosc kodu i algorytmy
// Dodać AI obsługę każdego przedmiotu [1]
// Zmienić zmienne na zmienne zajmujące mniej pamięci jeśli się da ( float -> float, unsigned int -> uint8_t, itp)
// Przenieść inicjalizacje zmiennych z konstruktorów do pól prywatnych klas jeśli wartość jest zawsze taka sama
// Pozmieniać std::vector na bardziej optymalne struktury danych jeśli się da
// Upewnić się, że wszystko jest resetowane przy rozpoczęciu nowej gry (w tym log, licznik autozapisu, itp)

//Błędy krytyczne(poważne, mogące powodować crash lub niezdefiniowane zachowanie)
//UB przy magazine[0] w InvertBulletType jeśli magazynek pusty – może crash. [1]
//
//Race condition na saveCounter w AutoSaveManager – UB, może spowodować błędne numery plików. [1]
//
//MagazineManager::DecreaseBulletCount przy niezgodności bulletCount i rozmiaru wektora – potencjalne UB. [1]
//
//Brak sprawdzenia zakresu przy wczytywaniu itemsHuman i bulletCount – może prowadzić do przepełnienia wektora(choć resize w SetMagazine może to złagodzić,
// to w TXT wczytuje najpierw do wektora lokalnego i potem ustawia).
//
//2. Błędy logiczne(średnie, prowadzące do nieprawidłowego działania)
//Podwójne wywołanie AI w HandleInventory – powoduje niespójność decyzji AI.
//
//Brak kopiowania hitProbability – po autozapisie AI może podejmować inne decyzje.
//
//Nadmiarowe ustawienia magazynka przy wczytywaniu JSON / TXT – nie powodują crasha, ale mogą maskować błędy. [1]
//
//GetRandomItem – nieaktualne GetFreeSlots() – potencjalnie może próbować dodać więcej przedmiotów niż slotów(choć w praktyce nie, bo warunek k < maxItemsRand ogranicza).
//
//    Brak resetowania flag stanu przedmiotów w Initialize() – może wpłynąć na nową grę.
//
//    Wyświetlanie starego numeru autozapisu – mylące dla użytkownika.
//
//    3. Problemy z utrzymaniem i bezpieczeństwem(lekkie)
//    system("cls") nieprzenośne – problem tylko przy kompilacji na Linux / macOS.
//
//    Magiczne liczby – utrudniają modyfikację kodu.
//
//    Mieszanie typów – potencjalne ostrzeżenia kompilatora, ryzyko utraty danych.
//
//    Brak ograniczenia rozmiaru loga – przy długiej rozgrywce może urosnąć, ale w konsoli jest czyszczony po każdej turze, więc ryzyko małe.
//
//    rand() zamiast <random> – słaba losowość, ale dla gry nie jest to krytyczne.


//naprawic format .txt

int main()
{
    srand(time(0));
    try
    {
        std::unique_ptr<IGameEngine> game;
		game = std::make_unique<GameEngine>();
		game->Run();
    }
    catch (const std::exception& e)
    {
        std::cout << "Gra zostanie zamknieta." << '\n';
        std::cout << "Powod: " << e.what() << '\n';

#ifdef _WIN32
        system("pause");
#endif
        return 1;
    }
    catch (...)
    {
        std::cout << "Gra zostanie zamknieta." << '\n';

#ifdef _WIN32
        system("pause");
#endif
        return 1;
    }
    return 0;
}