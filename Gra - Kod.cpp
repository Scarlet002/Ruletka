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
using std::unique_ptr;

class Gracz;
class Komputer;
class Magazynek;
class Strzal;
class IZapis;
class IOdczyt;
class Zapis;
class Odczyt;
class Interfejs;
class Gra;

class Magazynek
{

private:

	int liczbaPociskow = 0;
	vector<int> magazynek;

public:

	void zaladuj()
	{
		liczbaPociskow = rand() % 8 + 1;
		magazynek.resize(liczbaPociskow);

		for (int i = 0; i < liczbaPociskow; i++)
		{
			magazynek[i] = rand() % 2;
		}
	}

	void pokazPociski() const
	{
		for (int i = 0; i < liczbaPociskow; i++)
		{
			if (magazynek[i] == 1)
			{
				cout << "Pelna - 1" << endl;
			}
			else
			{
				cout << "Pusta - 0" << endl;
			}
		}
	}

	int pokazLiczbePociskow() const
	{
		return magazynek.size();
	}

	void ustawLiczbePociskow(int noweLiczbaPociskow)
	{
		liczbaPociskow = noweLiczbaPociskow;
	}

	void zmniejszLiczbePociskow() {

		if (liczbaPociskow == 0)
		{
			return;
		}
		else
		{
			liczbaPociskow--;
			magazynek.erase(magazynek.begin());
		}

	}

	void przeladuj()
	{
		magazynek.clear();
		liczbaPociskow = 0;

		zaladuj();
	}

	bool sprawdzLuske() const
	{
		if (magazynek.empty())
		{
			return false;
		}
		else
		{
			if (magazynek[0] == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	bool czyPusty() const
	{
		if (liczbaPociskow == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	const vector<int>& pokazMagazynek() const
	{

		return magazynek;

	}

	void ustawMagazynek(const vector<int>& nowyMagazynek) 
	{

		magazynek = nowyMagazynek;
		liczbaPociskow = magazynek.size();

	}

};

class Strzal
{

private:

public:

	void oddajStrzal(Gracz& wybor, int wyborDoIfa, Magazynek& magazynek);

};

class Gracz
{

private:

	int HP;
	const int maxHP = 3;

public:

	Gracz() : HP(maxHP)
	{
		HP = maxHP;
	}

	bool czyZyje() const
	{
		if (HP > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void utrataHP()
	{
		if (czyZyje()) {
			HP--;
		}
		else
		{
			return;
		}
	}

	void odzyskanieHP()
	{
		if (czyZyje())
		{

			if (HP < maxHP)
			{
				HP++;
			}
		}
		else
		{
			return;
		}
	}

	void resetHP()
	{
		HP = maxHP;
	}

	int pokazHP() const
	{
		return HP;
	}

	void ustawHP(int noweHP)
	{
		HP = noweHP;
	}

	void wykonajRuch(Gracz& czlowiek, Komputer& komputer, int& wybor, Magazynek& magazynek, int& zaczynajacy, Strzal& strzal, IZapis* zapis, IOdczyt* odczyt, Interfejs& ui, string& nazwaPliku);

};

class Komputer : public Gracz
{

private:

public:

	void wykonajRuch(Gracz& cel, int& wybor, Magazynek& magazynek, int& zaczynajacy, Strzal& strzal);

};

class IZapis {

private:

public:

	virtual void zapiszStanGry(Gracz& czlowiek, Komputer& komputer, int& liczbaPociskow, int& zaczynajacy, Magazynek& magazynek, string& nazwaPliku) = 0;

	virtual ~IZapis() = default;

};

class Zapis : public IZapis
{

private:

public:

	void zapiszStanGry(Gracz& czlowiek, Komputer& komputer, int& liczbaPociskow, int& zaczynajacy, Magazynek& magazynek, string& nazwaPliku) override {

		string nazwa;
		nazwa = nazwaPliku;

		ofstream saveStanuGry(nazwa);

		if (saveStanuGry.is_open()) {

			if (saveStanuGry.fail()) {

				cout << "Blad podczas zapisu stanu gry!" << endl;

			}
			else {

				saveStanuGry << czlowiek.pokazHP() << endl;
				saveStanuGry << komputer.pokazHP() << endl;
				saveStanuGry << magazynek.pokazLiczbePociskow() << endl;
				saveStanuGry << zaczynajacy << endl;

				for (int i = 0; i < magazynek.pokazLiczbePociskow(); i++)
				{

					saveStanuGry << magazynek.pokazMagazynek()[i] << endl;

				}

				saveStanuGry.close();

			}

			cout << "Pomyslnie zapisano stan gry!" << endl;

		}
		else
		{

			cout << "Nie mozna otworzyc pliku podczas zapisu!" << endl;

		}

	}


};

class IOdczyt
{

private:

public:

	virtual void wczytajStanGry(Gracz& czlowiek, Komputer& komputer, int& liczbaPociskow, int& zaczynajacy, Magazynek& magazynek, string& nazwaPliku) = 0;

	virtual ~IOdczyt() = default;

};

class Odczyt : public IOdczyt
{

private:

public:

	void wczytajStanGry(Gracz& czlowiek, Komputer& komputer, int& liczbaPociskow, int& zaczynajacy, Magazynek& magazynek, string& nazwaPliku) override {

		string nazwa;
		nazwa = nazwaPliku;

		ifstream saveStanuGry(nazwa);

		if (saveStanuGry.is_open())
		{

			if (saveStanuGry.fail())
			{
				cout << "Blad podczas wczytywania stanu gry!" << endl;
			}
			else
			{

				int pocisk;
				int hpczlowiek;
				int hpkomputer;
				int liczbaPociskowMagazynek;

				saveStanuGry >> hpczlowiek;
				saveStanuGry >> hpkomputer;
				saveStanuGry >> liczbaPociskowMagazynek;
				saveStanuGry >> zaczynajacy;

				czlowiek.ustawHP(hpczlowiek);
				komputer.ustawHP(hpkomputer);

				vector<int> nowyMagazynek;

				for (int i = 0; i < liczbaPociskowMagazynek; i++)
				{

					saveStanuGry >> pocisk;
					nowyMagazynek.push_back(pocisk);
				}

				magazynek.ustawMagazynek(nowyMagazynek);
				saveStanuGry.close();

			}

			cout << "Pomyslnie wczytano stan gry!" << endl;

		}
		else
		{
			cout << "Nie mozna otworzyc pliku podczas wczytywania!" << endl;
		}

	}


};

class Interfejs
{

private:

public:

	void wyswietlStatystyki(const Gracz& czlowiek, const Komputer& komputer, const Magazynek& magazynek) const
	{
		cout << "--------------------------------------------------------------------------" << endl;
		cout << "Statystyki:" << endl;
		cout << "czlowiek HP: " << czlowiek.pokazHP() << endl;
		cout << "komputer HP: " << komputer.pokazHP() << endl;
		cout << "Pociski w magazynku: " << magazynek.pokazLiczbePociskow() << endl;
		magazynek.pokazPociski();
		cout << "--------------------------------------------------------------------------" << endl;
	}

	void przewinEkran() const
	{
		for (int i = 0; i < 30; i++)
		{
			cout << endl;
		}
	}

	bool czyChceKontynuowac(Gracz& czlowiek, Komputer& komputer)
	{
		char wybor;
		cout << "Czy chcesz kontynuowac gre? (t/n): ";
		cin >> wybor;
		if (wybor == 't' || wybor == 'T')
		{
			czlowiek.resetHP();
			komputer.resetHP();
			przewinEkran();
			return true;
		}
		else
		{
			cout << "Dziekuje za gre!" << endl;
			return false;
		}
	}

	void menu(int& wybor)
	{

		cout << "Wybierz co chcesz zrobic:" << endl;
		cout << "0 - Sprobuj odzyskac 1 HP" << endl;
		cout << "1 - Strzel w komputera" << endl;
		cout << "5 - Zapisz gre" << endl;
		cout << "6 - Wczytaj gre" << endl;
		cout << "--------------------------------------------------------------------------" << endl;
		cout << "Twoj wybor: ";

		cin >> wybor;

	}

	void cinZapis(string& nazwaPliku)
	{

		cout << "Podaj nazwe zapisu, ktory chcesz zapisac: ";
		cin >> nazwaPliku;
		nazwaPliku += ".txt";

	}

	void cinOdczyt(string& nazwaPliku)
	{
		cout << "Podaj nazwe zapisu, ktory chcesz wczytac: ";
		cin >> nazwaPliku;
		nazwaPliku += ".txt";
	}

	void cinNieprawidowyWybor() const
	{
		cout << "Nieprawidlowy wybor. Straciles ture!" << endl;
	}

	void cinWygranaKomputera() const
	{
		cout << "Komputer wygral!" << endl;
	}

	void cinWygranaCzlowieka() const
	{
		cout << "Czlowiek wygral!" << endl;
	}


};

void Gracz::wykonajRuch(Gracz& czlowiek, Komputer& komputer, int& wybor, Magazynek& magazynek, int& zaczynajacy, Strzal& strzal, IZapis* zapis, IOdczyt* odczyt, Interfejs& ui, string& nazwaPliku)
{

	int liczbaPociskow = magazynek.pokazLiczbePociskow();

	if (wybor == 1)
	{

		zaczynajacy = 0;
		strzal.oddajStrzal(komputer, 1, magazynek);

	}
	else if (wybor == 0)
	{

		zaczynajacy = 0;
		strzal.oddajStrzal(czlowiek, 0, magazynek);

	}
	else if (wybor == 5)
	{

		ui.cinZapis(nazwaPliku);
		zapis->zapiszStanGry(czlowiek, komputer, liczbaPociskow, zaczynajacy, magazynek, nazwaPliku);
		ui.wyswietlStatystyki(czlowiek, komputer, magazynek);
		ui.menu(wybor);

	}
	else if (wybor == 6)
	{

		ui.cinOdczyt(nazwaPliku);
		odczyt->wczytajStanGry(czlowiek, komputer, liczbaPociskow, zaczynajacy, magazynek, nazwaPliku);
		ui.wyswietlStatystyki(czlowiek, komputer, magazynek);
		ui.menu(wybor);

	}
	else
	{

		zaczynajacy = 0;
		ui.cinNieprawidowyWybor();

	}

}

void Komputer::wykonajRuch(Gracz& cel, int& wybor, Magazynek& magazynek, int& zaczynajacy, Strzal& strzal)
{

	zaczynajacy = 1;
	cout << "Wybiera komputer!" << endl;
	wybor = rand() % 2;
	if (wybor == 1)
	{
		strzal.oddajStrzal(cel, 1, magazynek);
	}
	else
	{
		strzal.oddajStrzal(cel, 0, magazynek);
	}

}

void Strzal::oddajStrzal(Gracz& wybor, int wyborDoIfa, Magazynek& magazynek)
{
	if (wyborDoIfa == 1)
	{
		if (magazynek.sprawdzLuske())
		{
			cout << "Pudlo!" << endl;
		}
		else
		{
			wybor.utrataHP();
			cout << "Trafiony!" << endl;
		}
	}
	else
	{
		if (magazynek.sprawdzLuske())
		{
			if (wybor.pokazHP() < 3)
			{
				wybor.odzyskanieHP();
				cout << "Udalo sie odzyskac 1 HP!" << endl;
			}
			else
			{
				cout << "Masz juz max HP! Nie mozesz odzyskac zdrowia!" << endl;
			}
		}
		else
		{
			wybor.utrataHP();
			cout << "Nie udalo sie odzyskac HP i straciles 1 HP!" << endl;
		}
	}
	magazynek.zmniejszLiczbePociskow();
}

class Gra
{

private:

	int wybor;
	int zaczynajacy;

	string nazwaPliku;

	Strzal strzal;
	Interfejs ui;
	IZapis* zapis;
	IOdczyt* odczyt;
	Magazynek magazynek;
	Gracz czlowiek;
	Komputer komputer;

public:

	Gra(IZapis* _zapis, IOdczyt* _odczyt) : wybor(0), zaczynajacy(0), zapis(_zapis), odczyt(_odczyt) {

	}

	void losowanieZaczynajacego()
	{
		if (rand() % 2 == 1)
		{
			zaczynajacy = 1;
			cout << "Zaczyna czlowiek!" << endl;
		}
		else
		{
			zaczynajacy = 0;
			cout << "Zaczyna komputer!" << endl;
		}
	}

	void wygrana() {

		if (ui.czyChceKontynuowac(czlowiek, komputer))
		{
			rozpocznijGre();
		}
		else
		{
			return;
		}

	}

	void nowaTura() {

		cout << "Koniec pociskow! Przeladownie!" << endl;
		magazynek.przeladuj();
		ui.wyswietlStatystyki(czlowiek, komputer, magazynek);

	}

	bool ktoWygral() {

		if (!czlowiek.czyZyje())
		{
			ui.cinWygranaKomputera();
			wygrana();
			return true;
		}
		else if (!komputer.czyZyje())
		{
			ui.cinWygranaCzlowieka();
			wygrana();
			return true;
		}
		return false;

	}

	bool czyKoniecPociskow() const {

		if (magazynek.czyPusty())
		{
			return true;
		}
		return false;

	}

	void rozpocznijGre()
	{
		magazynek.zaladuj();
		losowanieZaczynajacego();
		ui.wyswietlStatystyki(czlowiek, komputer, magazynek);

		while (true)
		{

			if (zaczynajacy == 1)
			{

				ui.menu(wybor);

				while (zaczynajacy == 1)
				{
					czlowiek.wykonajRuch(czlowiek, komputer, wybor, magazynek, zaczynajacy, strzal, zapis, odczyt, ui, nazwaPliku);
				}

			}
			else
			{
				komputer.wykonajRuch(czlowiek, wybor, magazynek, zaczynajacy, strzal);
			}
			ui.wyswietlStatystyki(czlowiek, komputer, magazynek);

			if (ktoWygral())
			{
				break;
			}

			if (czyKoniecPociskow())
			{
				nowaTura();
			}

		}

	}

};

int main()
{
	srand(time(NULL));

	Zapis zapis;
	Odczyt odczyt;
	Gra gra(&zapis, &odczyt);

	gra.rozpocznijGre();

	return 0;
}
