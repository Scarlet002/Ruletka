#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <algorithm>
#include <regex>
#include <numeric>
#include <future>
#include <chrono>
#include <thread>
#include <memory>
#include <stdexcept>
#include "include/nlohmann/json.hpp"

using json = nlohmann::json;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::string;
using std::runtime_error;
using std::exception;
using std::regex;
using std::stoi;
using std::min;
using std::any_of;
using std::count;
using std::async;
using std::launch;
using std::to_string;
using std::future;

class Player;
class Magazine;
class Ui;

class IMagazine
{
public:
    virtual void Load() = 0;
    virtual void ShowBullets() const = 0;
    virtual bool CheckBulletType() const = 0;
    virtual void CheckBullets() = 0;
    virtual int ShowFull() const = 0;
    virtual int ShowEmpty() const = 0;
    virtual void SetFull(int newFull) = 0;
    virtual void SetEmpty(int newEmpty) = 0;
    virtual void DecreaseFullCount() = 0;
    virtual void DecreaseEmptyCount() = 0;
    virtual int ShowBulletCount() const = 0;
    virtual void SetBulletCount(int newBulletCount) = 0;
    virtual void DecreaseBulletCount() = 0;
    virtual bool IsOutOfBullets() const = 0;
    virtual void Reload() = 0;
    virtual bool IsEmptySlot() const = 0;
    virtual bool IsEmpty() const = 0;
    virtual const vector<int>& GetMagazine() const = 0;
    virtual void SetMagazine(const vector<int>& newMagazine) = 0;
    virtual double CalculateHitProbability() const = 0;
    virtual bool HasEmptyBullets() const = 0;

    virtual ~IMagazine() = default;
};

class IShoot
{
public:
    virtual void MakeShot(Player& target, Player& shooter, int choice, Magazine& magazine) = 0;
    virtual ~IShoot() = default;
};

class IPlayer
{
public:
    virtual bool isAlive() const = 0;
    virtual void LoseHP() = 0;
    virtual void RegainHP() = 0;
    virtual void ResetHP() = 0;
    virtual int GetHP() const = 0;
    virtual void SetHP(int newHP) = 0;
    virtual bool IsHuman() const = 0;
    virtual bool IsComputer() const = 0;

    virtual ~IPlayer() = default;
};

class ISaveSync
{
public:
    virtual void SaveGameState(const Player& human, const Player& computer, int starting, const Magazine& magazine, const string& fileName) const = 0;
    virtual ~ISaveSync() = default;
};

class ISaveAsync
{
public:
    virtual void SaveGameStateAsync(const Player& human, const Player& computer, int starting, const Magazine& magazine, string& autoSaveFileName) = 0;
    virtual bool IsSaving() const = 0;
    virtual ~ISaveAsync() = default;
};

class ILoad
{
public:
    virtual void LoadGameState(Player& human, Player& computer, int& starting, Magazine& magazine, const string& fileName) const = 0;
    virtual ~ILoad() = default;
};

class IUi
{
public:
    virtual void DisplayStats(int difficulty, const Player& human, const Player& computer, const Magazine& magazine) const = 0;
    virtual void ScrollScreen() const = 0;
    virtual void Menu() const = 0;
    virtual void DifficultyMenu() const = 0;
    virtual void ShowAIDifficulty(int difficulty) const = 0;
    virtual void EasyAI(int& choice) const = 0;
    virtual void NormalAI(int& choice, const Magazine& magazine) const = 0;
    virtual void HardAI(int& choice, const Magazine& magazine) const = 0;
    virtual int MakeDecision(int& choice, int& difficulty, const Player& player, const Magazine& magazine) const = 0;
    virtual void InputSaveTXT(string& fileName) = 0;
    virtual void InputLoadTXT(string& fileName) = 0;
    virtual void InputSaveJSON(string& fileName) = 0;
    virtual void InputLoadJSON(string& fileName) = 0;
    virtual void InputdifficultyLevel(int& difficulty) = 0;
    virtual bool WantsToContinue(Player& human, Player& computer, Magazine& magazine) = 0;
    virtual void ComputerChoosing() const = 0;
    virtual void ComputerStarts() const = 0;
    virtual void HumanStarts() const = 0;
    virtual void ShowPointer() const = 0;
    virtual void NewLine() const = 0;
    virtual void AutoSaveDone() const = 0;
    virtual void ShowAutoSaveName(string& autoSaveFileName) const = 0;
    virtual void SavingSucces() const = 0;
    virtual void LoadingSucces() const = 0;
    virtual void InvalidInput() const = 0;
    virtual void ComputerWin() const = 0;
    virtual void HumanWin() const = 0;
    virtual void EndOfBullets() const = 0;
    virtual void ThankYou() const = 0;

    virtual ~IUi() = default;
};

class IGame
{
public:
    virtual void RandomizeStarter(int& starting, const Ui& ui) = 0;
    virtual void NewRound(const Player& human, const Player& computer, const Ui& ui, Magazine& magazine) = 0;
    virtual bool WhoWon(const Player& human, const Player& computer, const Ui& ui) = 0;
    virtual void StartGame() = 0;

    virtual ~IGame() = default;
};

class Magazine : public IMagazine
{
private:
    int full = 0;
    int empty = 0;
    int bulletCount = 0;
    vector<int> magazine;

public:
    void Load() override
    {
        bulletCount = rand() % 8 + 1;
        magazine.resize(bulletCount);

        for (int i = 0; i < bulletCount; i++)
        {
            magazine[i] = rand() % 2;
        }
    }

    void ShowBullets() const override
    {
        for (int i = 0; i < bulletCount; i++)
        {
            if (magazine[i] == 1)
                cout << "Pelna - 1" << endl;
            else
                cout << "Pusta - 0" << endl;
        }
    }

    bool CheckBulletType() const override
    {
        return magazine[0] == 1;
    }

    void CheckBullets() override
    {
        for (int i = 0; i < bulletCount; i++)
        {
            if (magazine[i] == 1)
                full++;
            else
                empty++;
        }
    }

    int ShowFull() const override { return full; }
    int ShowEmpty() const override { return empty; }

    void DecreaseFullCount() override { if (full > 0) full--; }
    void DecreaseEmptyCount() override { if (empty > 0) empty--; }

    int ShowBulletCount() const override { return static_cast<int>(magazine.size()); }

    void SetBulletCount(int newBulletCount) override
    {
        bulletCount = newBulletCount;
        magazine.resize(bulletCount);
    }

    void SetFull(int newFull) override { full = newFull; }
    void SetEmpty(int newEmpty) override { empty = newEmpty; }

    void DecreaseBulletCount() override
    {
        if (bulletCount == 0) return;
        magazine.erase(magazine.begin());
        bulletCount = static_cast<int>(magazine.size());
    }

    bool IsOutOfBullets() const override { return IsEmpty(); }

    void Reload() override
    {
        magazine.clear();
        bulletCount = 0;
        empty = 0;
        full = 0;
        Load();
        CheckBullets();
    }

    bool IsEmptySlot() const override
    {
        if (magazine.empty()) throw runtime_error("Magazynek jest pusty!");
        return magazine[0] == 0;
    }

    bool IsEmpty() const override { return bulletCount == 0; }

    const vector<int>& GetMagazine() const override { return magazine; }

    void SetMagazine(const vector<int>& newMagazine) override
    {
        magazine = newMagazine;
        bulletCount = static_cast<int>(magazine.size());
    }

    double CalculateHitProbability() const override
    {
        if (magazine.empty()) return 0.0;
        return static_cast<double>(full) / bulletCount;
    }

    bool HasEmptyBullets() const override
    {
        return any_of(magazine.begin(), magazine.end(), [](int bullet) { return bullet == 0; });
    }
};

class Player : public IPlayer
{
private:
    const int maxHP = 3;
    int HP = maxHP;
    string name;
    string type;

public:
    Player(const string& playerName, const string& playerType) : HP(maxHP), name(playerName), type(playerType) {}

    bool isAlive() const override { return HP > 0; }

    void LoseHP() override { if (isAlive()) HP--; }

    void RegainHP() override
    {
        if (isAlive() && HP < maxHP)
            HP++;
    }

    void ResetHP() override { HP = maxHP; }

    int GetHP() const override { return HP; }

    void SetHP(int newHP) override { HP = newHP; }

    bool IsHuman() const override { return type == "czlowiek" || type == "Czlowiek"; }

    bool IsComputer() const override { return type == "komputer" || type == "Komputer"; }
};

class Shoot : public IShoot
{
public:
    void MakeShot(Player& target, Player& shooter, int choice, Magazine& magazine) override
    {
        try
        {
            if (magazine.IsEmpty()) throw runtime_error("Brak pociskow w magazynku!");

            if (choice == 1)
            {
                if (magazine.IsEmptySlot())
                {
                    cout << "Pudlo!";
                    magazine.DecreaseEmptyCount();
                }
                else
                {
                    target.LoseHP();
                    magazine.DecreaseFullCount();
                    cout << "Trafiony!";
                }
            }
            else
            {
                if (magazine.IsEmptySlot())
                {
                    if (shooter.GetHP() < 3)
                    {
                        shooter.RegainHP();
                        cout << "Udalo sie odzyskac 1 HP!";
                    }
                    else
                        cout << "Masz juz max HP! Nie mozesz odzyskac zdrowia!";
                    magazine.DecreaseEmptyCount();
                }
                else
                {
                    shooter.LoseHP();
                    magazine.DecreaseFullCount();
                    cout << "Nie udalo sie odzyskac HP i straciles 1 HP!";
                }
            }
            magazine.DecreaseBulletCount();
        }
        catch (const exception& e)
        {
            cout << "Blad strzalu: " << e.what() << endl;
            magazine.Reload();
        }
    }
};

class InputValidator
{
public:
    static bool IsValidFileName(const string& fileName) {
        regex pattern("^[a-zA-Z0-9_-]{1,30}$");
        return regex_match(fileName, pattern);
    }

    static bool IsValidMenuChoice(const string& input) {
        regex pattern("^[0-7]$");
        return regex_match(input, pattern);
    }

    static bool IsValidYesNo(const string& input) {
        regex pattern("^[tTnN]$");
        return regex_match(input, pattern);
    }

    static bool IsValidDifficultyChoice(const string& input) {
        regex pattern("^[0-2]$");
        return regex_match(input, pattern);
    }

    static string GetValidatedInput(const string& prompt, bool (*validator)(const string&)) {
        string input;
        while (true) {
            cout << prompt;
            cin >> input;

            if (validator(input)) {
                return input;
            }
            cout << "Nieprawidlowe dane! Sprobuj ponownie." << endl;
        }
    }
};

class SaveTXT : public ISaveSync
{
public:
    void SaveGameState(const Player& human, const Player& computer, int starting, const Magazine& magazine, const string& fileName) const override
    {
        try
        {
            ofstream gameSave(fileName);
            if (!gameSave.is_open())
            {
                cout << "Nie mozna otworzyc pliku podczas zapisu!" << endl;
                return;
            }
            if (gameSave.fail())
            {
                cout << "Blad podczas zapisu stanu gry!" << endl;
                return;
            }
            gameSave << human.GetHP() << endl;
            gameSave << computer.GetHP() << endl;
            gameSave << magazine.ShowFull() << endl;
            gameSave << magazine.ShowEmpty() << endl;
            gameSave << magazine.ShowBulletCount() << endl;
            gameSave << starting << endl;

            for (int i : magazine.GetMagazine())
                gameSave << i << endl;

            gameSave.close();
        }
        catch (const exception& e)
        {
            cout << "Blad zapisywania: " << e.what() << endl;
        }
    }
};

class SaveJSON : public ISaveSync
{
public:
    void SaveGameState(const Player& human, const Player& computer, int starting, const Magazine& magazine, const string& fileName) const override
    {
        try
        {
            json data;
            data["human_HP"] = human.GetHP();
            data["computer_HP"] = computer.GetHP();
            data["magazine_full"] = magazine.ShowFull();
            data["magazine_empty"] = magazine.ShowEmpty();
            data["magazine_bullet_count"] = magazine.ShowBulletCount();
            data["starting"] = starting;
            for (int i : magazine.GetMagazine())
                data["magazine"].push_back(i);

            ofstream gameSave(fileName);
            if (!gameSave.is_open())
            {
                cout << "Nie mozna otworzyc pliku podczas zapisu!" << endl;
                return;
            }
            if (gameSave.fail())
            {
                cout << "Blad podczas zapisu stanu gry!" << endl;
                return;
            }
            gameSave << data.dump(4);
            gameSave.close();
        }
        catch (const json::exception& e)
        {
            cout << "Blad pliku JSON: " << e.what() << endl;
        }
        catch (const exception& e)
        {
            cout << "Blad zapisywania: " << e.what() << endl;
        }
    }
};

class LoadTXT : public ILoad
{
public:
    void LoadGameState(Player& human, Player& computer, int& starting, Magazine& magazine, const string& fileName) const override
    {
        try
        {
            ifstream gameSave(fileName);
            if (!gameSave.is_open())
            {
                cout << "Nie mozna otworzyc pliku podczas wczytywania!" << endl;
                return;
            }

            int bullet, hpHuman, hpComputer, full, empty, bulletCount;
            gameSave >> hpHuman >> hpComputer >> full >> empty >> bulletCount >> starting;

            human.SetHP(hpHuman);
            computer.SetHP(hpComputer);
            magazine.SetFull(full);
            magazine.SetEmpty(empty);
            magazine.SetBulletCount(bulletCount);

            vector<int> newMagazine;
            for (int i = 0; i < bulletCount; i++)
            {
                gameSave >> bullet;
                newMagazine.push_back(bullet);
            }

            magazine.SetMagazine(newMagazine);

        }
        catch (const exception& e)
        {
            cout << "Blad wczytywania: " << e.what() << endl;
        }
    }
};

class LoadJSON : public ILoad
{
public:
    void LoadGameState(Player& human, Player& computer, int& starting, Magazine& magazine, const string& fileName) const override
    {
        try
        {
            ifstream gameSave(fileName);
            if (!gameSave.is_open())
            {
                cout << "Nie mozna otworzyc pliku podczas wczytywania!" << endl;
                return;
            }
            json data = json::parse(gameSave);

            int hpHuman = data["human_HP"];
            int hpComputer = data["computer_HP"];
            int full = data["magazine_full"];
            int empty = data["magazine_empty"];
            int bulletCount = data["magazine_bullet_count"];
            starting = data["starting"];

            human.SetHP(hpHuman);
            computer.SetHP(hpComputer);
            magazine.SetFull(full);
            magazine.SetEmpty(empty);
            magazine.SetBulletCount(bulletCount);

            vector<int> newMagazine;
            for (int i = 0; i < bulletCount; i++)
            {
                newMagazine.push_back(data["magazine"][i]);
            }

            magazine.SetMagazine(newMagazine);

        }
        catch (const json::exception& e)
        {
            cout << "Blad pliku JSON: " << e.what() << endl;
        }
        catch (const exception& e)
        {
            cout << "Blad wczytywania: " << e.what() << endl;
        }
    }
};

class Ui : public IUi
{
public:
    void DisplayStats(int difficulty, const Player& human, const Player& computer, const Magazine& magazine) const override
    {
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Poziom trudnosci: ";
        ShowAIDifficulty(difficulty);
        cout << endl;
        cout << "Statystyki:" << endl;
        cout << "czlowiek HP: " << human.GetHP() << endl;
        cout << "komputer HP: " << computer.GetHP() << endl;
        cout << "Pelne pociski: " << magazine.ShowFull() << endl;
        cout << "Puste pociski: " << magazine.ShowEmpty() << endl;
        cout << "Liczba pociskow: " << magazine.ShowBulletCount() << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    }

    void ScrollScreen() const override { for (int i = 0; i < 30; i++) cout << endl; }

    void Menu() const override
    {
        cout << "Wybierz co chcesz zrobic:" << endl;
        cout << "0 - Sprobuj odzyskac 1 HP" << endl;
        cout << "1 - Strzel w komputera" << endl;
        cout << "5 - Zapisz gre" << endl;
        cout << "6 - Wczytaj gre" << endl;
        cout << "7 - Wybierz poziom trudnosci" << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    }

    void DifficultyMenu() const override
    {
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Wybierz poziom trudnosci:" << endl;
        cout << "0 - latwy" << endl;
        cout << "1 - normalny" << endl;
        cout << "2 - trudny" << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    }

    void ShowAIDifficulty(int difficulty) const override
    {
        if (difficulty == 0)
        {
            cout << "latwy";
        }
        else if (difficulty == 1)
        {
            cout << "normalny";
        }
        else
        {
            cout << "trudny";
        }
    }

    void EasyAI(int& choice) const override
    {
        choice = rand() % 2;
    }

    void NormalAI(int& choice, const Magazine& magazine) const override
    {
        double hitChance = magazine.CalculateHitProbability();
        if (hitChance != 0.0)
        {
            choice = 1;
        }
        else if (hitChance == 0.0)
        {
            choice = 0;
        }
    }

    void HardAI(int& choice, const Magazine& magazine) const override
    {
        if (magazine.CheckBulletType())
        {
            choice = 1;
        }
        else if (!magazine.CheckBulletType())
        {
            choice = 0;
        }
    }

    int MakeDecision(int& choice, int& difficulty, const Player& player, const Magazine& magazine) const override
    {
        if (player.IsHuman())
        {
            string input = InputValidator::GetValidatedInput("Twoj wybor (0 - 7): ", InputValidator::IsValidMenuChoice);
            choice = stoi(input);
        }
        else
        {
            if (difficulty == 0)
            {
                EasyAI(choice);
            }
            else if (difficulty == 1)
            {
                NormalAI(choice, magazine);
            }
            else
            {
                HardAI(choice, magazine);
            }
        }
        return choice;
    }

    void InputSaveTXT(string& fileName) override
    {
        fileName = InputValidator::GetValidatedInput("Podaj nazwe zapisu: ", InputValidator::IsValidFileName);
        fileName += ".txt";
    }

    void InputLoadTXT(string& fileName) override
    {
        fileName = InputValidator::GetValidatedInput("Podaj nazwe zapisu do wczytania: ", InputValidator::IsValidFileName);
        fileName += ".txt";
    }

    void InputSaveJSON(string& fileName) override
    {
        fileName = InputValidator::GetValidatedInput("Podaj nazwe zapisu: ", InputValidator::IsValidFileName);
        fileName += ".json";
    }

    void InputLoadJSON(string& fileName) override
    {
        fileName = InputValidator::GetValidatedInput("Podaj nazwe zapisu do wczytania: ", InputValidator::IsValidFileName);
        fileName += ".json";
    }

    void InputdifficultyLevel(int& difficulty) override
    {
        string input = InputValidator::GetValidatedInput("Twoj wybor (0 - 2): ", InputValidator::IsValidDifficultyChoice);
        difficulty = stoi(input);
    }

    bool WantsToContinue(Player& human, Player& computer, Magazine& magazine) override
    {
        string ans = InputValidator::GetValidatedInput("Czy chcesz kontynuowac gre? (t/n): ", InputValidator::IsValidYesNo);
        if (ans == "t" || ans == "T")
        {
            human.ResetHP();
            computer.ResetHP();
            magazine.Reload();
            ScrollScreen();
            return true;
        }
        else
        {
            ScrollScreen();
            ThankYou();
            return false;
        }
    }

    void ComputerChoosing() const override { cout << "Wybiera komputer!" << endl; }
    void ComputerStarts() const override { cout << "Zaczyna komputer!" << endl; }
    void HumanStarts() const override { cout << "Zaczynasz ty!" << endl; }
    void ShowPointer() const override { cout << "										*" << endl; }
    void NewLine() const override { cout << endl; }
    void AutoSaveDone() const override { cout << "Zapis automatyczny zakonczony: "; }
    void ShowAutoSaveName(string& autoSaveFileName) const override { cout << autoSaveFileName; }
    void SavingSucces() const override { cout << "Pomyslnie zapisano stan gry!" << endl; }
    void LoadingSucces() const override { cout << "Pomyslnie wczytano stan gry!" << endl; }
    void InvalidInput() const override { cout << "Nieprawidlowy wybor. Straciles ture!" << endl; }
    void ComputerWin() const override { cout << "Komputer wygrywa gre!" << endl; }
    void HumanWin() const override { cout << "Wygrywasz gre!" << endl; }
    void EndOfBullets() const override { cout << "Koniec pociskow! Przeladowanie!" << endl; }
    void ThankYou() const override { cout << "Dziekuje za gre! Do zobaczenia!" << endl; }
};

class AutoSave : public ISaveAsync {
private:
    future<void> saveFuture;
    bool isSaving = false;
    int saveCounter = 0;
    SaveJSON& saver;

public:
    AutoSave(SaveJSON& saverRef) : saver(saverRef) {}

    void SaveGameStateAsync(const Player& human, const Player& computer, int starting,
        const Magazine& magazine, string& autoSaveFileName) override
    {
        isSaving = true;
        saveCounter++;
        autoSaveFileName = "autosave" + to_string(saveCounter) + ".json";
        Player humanCopy("czlowiek", "czlowiek");
        humanCopy.SetHP(human.GetHP());

        Player computerCopy("komputer", "komputer");
        computerCopy.SetHP(computer.GetHP());

        Magazine magazineCopy;
        magazineCopy.SetMagazine(magazine.GetMagazine());
        magazineCopy.SetFull(magazine.ShowFull());
        magazineCopy.SetEmpty(magazine.ShowEmpty());
        int startingCopy = starting;

        saveFuture = async(launch::async, [this, autoSaveFileName, humanCopy, computerCopy, startingCopy, magazineCopy]()
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                saver.SaveGameState(humanCopy, computerCopy, startingCopy, magazineCopy, autoSaveFileName);
                isSaving = false;
            }
        );
    }

    bool IsSaving() const override
    {
        return isSaving;
    }
};

class Game : public IGame
{
private:
    int difficulty = 1;
    int choice = 0;
    int starting = 0;
    AutoSave* asyncSaver;
    string fileName = "";
    string autoSaveFileName = "";
    LoadJSON loaderJSON;
    SaveJSON saverJSON;
    LoadTXT loaderTXT;
    SaveTXT saverTXT;
    Shoot shooter;
    Ui ui;
    Magazine magazine;
    Player human;
    Player computer;

public:
    Game(LoadJSON& loaderJSON, SaveJSON& saverJSON) : human("czlowiek", "czlowiek"), computer("komputer", "komputer"), loaderJSON(loaderJSON), saverJSON(saverJSON)
    {
        asyncSaver = new AutoSave(saverJSON);
    }

    ~Game() {
        delete asyncSaver;
    }

    void RandomizeStarter(int& starting, const Ui& ui) override
    {
        if (rand() % 2 == 1)
        {
            starting = 1;
            ui.HumanStarts();
        }
        else
        {
            starting = 0;
            ui.ComputerStarts();
        }
    }

    void NewRound(const Player& human, const Player& computer, const Ui& ui, Magazine& magazine) override
    {
        ui.EndOfBullets();
        magazine.Reload();
        ui.DisplayStats(difficulty, human, computer, magazine);
    }

    bool WhoWon(const Player& human, const Player& computer, const Ui& ui) override
    {
        if (!human.isAlive())
        {
            ui.ComputerWin();
            return true;
        }
        else if (!computer.isAlive())
        {
            ui.HumanWin();
            return true;
        }
        return false;
    }

    void StartGame() override
    {
        human.ResetHP();
        computer.ResetHP();
        magazine.Reload();
        RandomizeStarter(starting, ui);
        ui.DisplayStats(difficulty, human, computer, magazine);

        while (true)
        {
            if (starting == 1)
            {
                asyncSaver->SaveGameStateAsync(human, computer, starting, magazine, autoSaveFileName);
                ui.AutoSaveDone();
                ui.ShowAutoSaveName(autoSaveFileName);
                ui.NewLine();
                ui.Menu();
                ui.MakeDecision(choice, difficulty, human, magazine);

                if (choice == 1)
                {
                    starting = 0;
                    shooter.MakeShot(computer, human, choice, magazine);
                    ui.ShowPointer();
                }
                else if (choice == 0)
                {
                    starting = 0;
                    shooter.MakeShot(human, human, choice, magazine);
                    ui.ShowPointer();
                }
                else if (choice == 5)
                {
                    ui.InputSaveJSON(fileName);
                    saverJSON.SaveGameState(human, computer, starting, magazine, fileName);
                    ui.DisplayStats(difficulty, human, computer, magazine);
                    ui.SavingSucces();
                    ui.ShowPointer();
                }
                else if (choice == 6)
                {
                    ui.InputLoadJSON(fileName);
                    loaderJSON.LoadGameState(human, computer, starting, magazine, fileName);
                    ui.LoadingSucces();
                    ui.DisplayStats(difficulty, human, computer, magazine);
                    ui.ShowPointer();

                }
                else if (choice == 7)
                {
                    ui.DifficultyMenu();
                    ui.InputdifficultyLevel(difficulty);
                    ui.DisplayStats(difficulty, human, computer, magazine);
                    ui.ShowPointer();
                }
                else
                {
                    starting = 0;
                    ui.InvalidInput();
                    ui.ShowPointer();
                }
            }
            else
            {
                starting = 1;
                ui.ComputerChoosing();
                ui.MakeDecision(choice, difficulty, computer, magazine);

                if (choice == 1)
                {
                    shooter.MakeShot(human, computer, choice, magazine);
                    ui.NewLine();
                }
                else
                {
                    shooter.MakeShot(computer, computer, choice, magazine);
                    ui.NewLine();
                }
            }

            ui.DisplayStats(difficulty, human, computer, magazine);

            if (WhoWon(human, computer, ui)) {
                if (!ui.WantsToContinue(human, computer, magazine))
                    break;
            }

            if (magazine.IsOutOfBullets())
                NewRound(human, computer, ui, magazine);
        }
    }
};

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));

    SaveTXT saverTXT;
    LoadTXT loaderTXT;
    SaveJSON saverJSON;
    LoadJSON loaderJSON;

    Game game(loaderJSON, saverJSON);

    try
    {
        game.StartGame();
    }
    catch (const exception& e)
    {
        cout << "KRYTYCZNY BLAD GRY!" << endl;
        cout << "Powod: " << e.what() << endl;
        cout << "Gra zostanie zamknieta." << endl;

#ifdef _WIN32
        system("pause");
#endif

        return 1;
    }
    catch (...)
    {
        cout << "NIEZNANY KRYTYCZNY BLAD!" << endl;
        cout << "Gra zostanie zamknieta." << endl;

#ifdef _WIN32
        system("pause");
#endif

        return 1;
    }

    return 0;
}
