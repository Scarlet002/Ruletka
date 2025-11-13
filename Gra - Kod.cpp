#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::string;
using std::runtime_error;

class IGame;
class IUi;
class IMagazine;
class IShoot;
class IPlayer;
class ISave;
class ILoad;
class Player;
class Magazine;
class Shoot;
class Save;
class Load;
class Ui;
class Game;

class IMagazine
{
public:
	virtual void Load() = 0;
	virtual void ShowBullets() const = 0;
	virtual int ShowBulletCount() const = 0;
	virtual void SetBulletCount(int newBulletCount) = 0;
	virtual void DecreaseBulletCount() = 0;
	virtual bool IsOutOfBullets() const = 0;
	virtual void Reload() = 0;
	virtual bool IsEmptySlot() const = 0;
	virtual bool IsEmpty() const = 0;
	virtual const vector<int>& GetMagazine() const = 0;
	virtual void SetMagazine(const vector<int>& newMagazine) = 0;
	virtual void CountBullets() = 0;
	virtual int ShowFull() const = 0;
	virtual int ShowEmpty() const = 0;
	virtual void DecreaseFullCount() = 0;
	virtual void DecreaseEmptyCount() = 0;

	virtual ~IMagazine() = default;
};

class IShoot
{
public:
	virtual void MakeShot(Player& target, Player& shooter, const int& choice, Magazine& magazine) = 0;
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

class ISave
{
public:
	virtual void SaveGameState(const Player& human, const Player& computer, const int& starting, const Magazine& magazine, const string& fileName) const = 0;
	virtual ~ISave() = default;
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
	virtual void DisplayStats(const Player& human, const Player& computer, const Magazine& magazine) const = 0;
	virtual void ScrollScreen() const = 0;
	virtual void InvalidInput() const = 0;
	virtual void ComputerWin() const = 0;
	virtual void HumanWin() const = 0;
	virtual void Menu() const = 0;
	virtual void InputSave(string& fileName) = 0;
	virtual void InputLoad(string& fileName) = 0;
	virtual void ComputerChoosing() const = 0;
	virtual void ComputerStarts() const = 0;
	virtual void HumanStarts() const = 0;
	virtual void EndOfBullets() const = 0;
	virtual void ThankYou() const = 0;
	virtual void AskContinue() const = 0;
	virtual int MakeDecision(int& choice, const Player& player) const = 0;
	virtual void ShowPointer() const = 0;
	virtual void NewLine() const = 0;

	virtual ~IUi() = default;
};

class IGame
{
public:
	virtual void RandomizeStarter(int& starting, const Ui& ui) = 0;
	virtual void Victory(const Player& human, const Player& computer, const Ui& ui) = 0;
	virtual void NewRound(const Player& human, const Player& computer, const Ui& ui, Magazine& magazine) = 0;
	virtual bool WhoWon(const Player& human, const Player& computer, const Ui& ui) = 0;
	virtual bool WantsToContinue() = 0;
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

	void CountBullets() override
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
		CountBullets();
	}

	void SetFull(int newFull) { full = newFull; }
	void SetEmpty(int newEmpty) { empty = newEmpty; }

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
		CountBullets();
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
};

class Player : public IPlayer
{
private:
	int HP;
	const int maxHP = 3;
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
	void MakeShot(Player& target, Player& shooter, const int& choice, Magazine& magazine) override
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
};

class Save : public ISave
{
public:
	void SaveGameState(const Player& human, const Player& computer, const int& starting, const Magazine& magazine, const string& fileName) const override
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
		cout << "Pomyslnie zapisano stan gry!" << endl;
	}
};

class Load : public ILoad
{
public:
	void LoadGameState(Player& human, Player& computer, int& starting, Magazine& magazine, const string& fileName) const override
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
		magazine.CountBullets();
		cout << "Pomyslnie wczytano stan gry!" << endl;
	}
};

class Ui : public IUi
{
public:
	void DisplayStats(const Player& human, const Player& computer, const Magazine& magazine) const override
	{
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
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
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Twoj wybor: ";
	}

	int MakeDecision(int& choice, const Player& player) const override
	{
		if (player.IsHuman()) cin >> choice;
		else choice = rand() % 2;
		return choice;
	}

	void InputSave(string& fileName) override
	{
		cout << "Podaj nazwe zapisu: ";
		cin >> fileName;
		fileName += ".txt";
	}

	void InputLoad(string& fileName) override
	{
		cout << "Podaj nazwe zapisu do wczytania: ";
		cin >> fileName;
		fileName += ".txt";
	}

	void InvalidInput() const override { cout << "Nieprawidlowy wybor. Straciles ture!" << endl; }
	void ComputerWin() const override { cout << "Komputer wygrywa gre!" << endl; }
	void HumanWin() const override { cout << "Wygrywasz gre!" << endl; }
	void ComputerChoosing() const override { cout << "Wybiera komputer!" << endl; }
	void ComputerStarts() const override { cout << "Zaczyna komputer!" << endl; }
	void HumanStarts() const override { cout << "Zaczynasz ty!" << endl; }
	void EndOfBullets() const override { cout << "Koniec pociskow! Przeladowanie!" << endl; }
	void ThankYou() const override { cout << "Dziekuje za gre! Do zobaczenia!" << endl; }
	void AskContinue() const override { cout << "Czy chcesz kontynuowac gre? (t/n): "; }
	void ShowPointer() const override { cout << "										*" << endl; }
	void NewLine() const override { cout << endl; }
};

class Game : public IGame
{
private:
	int choice = 0;
	int starting = 0;
	string fileName = "";
	Load loader;
	Save saver;
	Shoot shooter;
	Ui ui;
	Magazine magazine;
	Player human;
	Player computer;

public:
	Game(Load loader, Save saver) : human("czlowiek", "czlowiek"), computer("komputer", "komputer"), loader(loader), saver(saver) {}

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

	bool WantsToContinue() override
	{
		char ans;
		ui.AskContinue();
		cin >> ans;
		if (ans == 't' || ans == 'T')
		{
			human.ResetHP();
			computer.ResetHP();
			magazine.Reload();
			ui.ScrollScreen();
			return true;
		}
		ui.ThankYou();
		return false;
	}

	void Victory(const Player& human, const Player& computer, const Ui& ui) override
	{
		if (WantsToContinue()) StartGame();
	}

	void NewRound(const Player& human, const Player& computer, const Ui& ui, Magazine& magazine) override
	{
		ui.EndOfBullets();
		magazine.Reload();
		ui.DisplayStats(human, computer, magazine);
	}

	bool WhoWon(const Player& human, const Player& computer, const Ui& ui) override
	{
		if (!human.isAlive())
		{
			ui.ComputerWin();
			Victory(human, computer, ui);
			return true;
		}
		else if (!computer.isAlive())
		{
			ui.HumanWin();
			Victory(human, computer, ui);
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
		ui.DisplayStats(human, computer, magazine);

		while (true)
		{
			if (starting == 1)
			{
				ui.Menu();
				ui.MakeDecision(choice, human);

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
					ui.InputSave(fileName);
					saver.SaveGameState(human, computer, starting, magazine, fileName);
					ui.DisplayStats(human, computer, magazine);
					ui.ShowPointer();
				}
				else if (choice == 6)
				{
					ui.InputLoad(fileName);
					loader.LoadGameState(human, computer, starting, magazine, fileName);
					ui.DisplayStats(human, computer, magazine);
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
				ui.MakeDecision(choice, computer);

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

			ui.DisplayStats(human, computer, magazine);

			if (WhoWon(human, computer, ui))
				break;

			if (magazine.IsOutOfBullets())
				NewRound(human, computer, ui, magazine);
		}
	}
};

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));

	Save saver;
	Load loader;
	Game game(loader, saver);

	game.StartGame();

	return 0;
}
