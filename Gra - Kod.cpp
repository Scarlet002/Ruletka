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

class IGra;
class IInterfejs;
class IMagazynek;
class IStrzal;
class IGracz;
class IZapis;
class IOdczyt;
class Gracz;
class Magazynek;
class Strzal;
class Zapis;
class Odczyt;
class Interfejs;
class Gra;

class IMagazynek
{

private:

public:

	virtual void zaladuj() = 0;
	virtual void pokazPociski() const = 0;
	virtual int pokazLiczbePociskow() const = 0;
	virtual void ustawLiczbePociskow(int noweLiczbaPociskow) = 0;
	virtual void zmniejszLiczbePociskow() = 0;
	virtual bool czyKoniecPociskow() const = 0;
	virtual void przeladuj() = 0;
	virtual bool czyPusta() const = 0;
	virtual bool czyPusty() const = 0;
	virtual const vector<int>& pokazMagazynek() const = 0;
	virtual void ustawMagazynek(const vector<int>& nowyMagazynek) = 0;
	virtual void zliczPociski() = 0;
	virtual int pokazPelne() const = 0;
	virtual int pokazPuste() const = 0;
	virtual void zmniejszLiczbePelnych() = 0;
	virtual void zmniejszLiczbePustych() = 0;

	virtual ~IMagazynek() = default;

};

class IStrzal
{

private:

public:

	virtual void oddajStrzal(Gracz& cel, Gracz& strzelajacy, const int& wybor, Magazynek& magazynek) = 0;

	virtual ~IStrzal() = default;

};

class IGracz
{

private:

public:

	virtual bool czyZyje() const = 0;
	virtual void utrataHP() = 0;
	virtual void odzyskanieHP() = 0;
	virtual void resetHP() = 0;
	virtual int pokazHP() const = 0;
	virtual void ustawHP(int noweHP) = 0;
	virtual bool czyJestCzlowiekiem() const = 0;
	virtual bool czyJestKomputerem() const = 0;

	virtual ~IGracz() = default;

};

class IZapis {

private:

public:

	virtual void zapiszStanGry(const Gracz& czlowiek, const Gracz& komputer, const int& zaczynajacy, const Magazynek& magazynek, const string& nazwaPliku) const = 0;

	virtual ~IZapis() = default;

};

class IOdczyt
{

private:

public:

	virtual void wczytajStanGry(Gracz& czlowiek, Gracz& komputer, int& zaczynajacy, Magazynek& magazynek, const string& nazwaPliku) const = 0;

	virtual ~IOdczyt() = default;

};

class IInterfejs
{

private:

public:

	virtual void wyswietlStatystyki(const Gracz& czlowiek, const Gracz& komputer, const Magazynek& magazynek) const = 0;
	virtual void przewinEkran() const = 0;
	virtual void cinNieprawidowyWybor() const = 0;
	virtual void cinWygranaKomputera() const = 0;
	virtual void cinWygranaCzlowieka() const = 0;
	virtual void menu() const = 0;
	virtual void cinZapis(string& nazwaPliku) = 0;
	virtual void cinOdczyt(string& nazwaPliku) = 0;
	virtual void cinWybieraKomputer() const = 0;
	virtual void cinZaczynaKomputer() const = 0;
	virtual void cinZaczynaCzlowiek() const = 0;
	virtual void cinKoniecPociskow() const = 0;
	virtual void cinPodziekowanie() const = 0;
	virtual void cinCzyKontynuowac() const = 0;
	virtual int podejmijDecyzje(int& wybor, const Gracz& gracz) const = 0;
	virtual void cinWskaznik() const = 0;
	virtual void cinEndl() const = 0;

	virtual ~IInterfejs() = default;

};

class IGra
{

private:

public:

	virtual void losowanieZaczynajacego(int& zaczynajacy, const Interfejs& ui) = 0;
	virtual void wygrana(const Gracz& czlowiek, const Gracz& komputer, const Interfejs& ui) = 0;
	virtual void nowaTura(const Gracz& czlowiek, const Gracz& komputer, const Interfejs& ui, Magazynek& magazynek) = 0;
	virtual bool ktoWygral(const Gracz& czlowiek, const Gracz& komputer, const Interfejs& ui) = 0;
	virtual bool czyChceKontynuowac() = 0;
	virtual void rozpocznijGre() = 0;

	virtual ~IGra() = default;

};

class Magazynek : public IMagazynek
{

private:

	int pelne = 0;
	int puste = 0;
	int liczbaPociskow = 0;
	vector<int> magazynek;

public:

	void zaladuj() override
	{
		liczbaPociskow = rand() % 8 + 1;
		magazynek.resize(liczbaPociskow);

		for (int i = 0; i < liczbaPociskow; i++)
		{
			magazynek[i] = rand() % 2;
		}
	}

	void pokazPociski() const override
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

	void zliczPociski() override
	{

		for (int i = 0; i < liczbaPociskow; i++)
		{
			if (magazynek[i] == 1)
			{
				pelne++;
			}
			else
			{
				puste++;
			}
		}

	}

	int pokazPelne() const override
	{
		return pelne;
	}

	int pokazPuste() const override
	{
		return puste;
	}

	void zmniejszLiczbePelnych() override
	{
		if (pelne > 0)
		{
			pelne--;
		}
	}

	void zmniejszLiczbePustych() override
	{
		if (puste > 0)
		{
			puste--;
		}
	}

	int pokazLiczbePociskow() const override
	{
		return static_cast<int>(magazynek.size());
	}

	void ustawLiczbePociskow(int noweLiczbaPociskow) override
	{
		liczbaPociskow = noweLiczbaPociskow;
		magazynek.resize(liczbaPociskow);
		zliczPociski();
	}

	void ustawPelne(int nowePelne)
	{
		pelne = nowePelne;
	}

	void ustawPuste(int nowePuste)
	{
		puste = nowePuste;
	}

	void zmniejszLiczbePociskow() override
	{

		if (liczbaPociskow == 0)
		{
			return;
		}
		else
		{
			magazynek.erase(magazynek.begin());
			liczbaPociskow = static_cast<int>(magazynek.size());
		}

	}

	bool czyKoniecPociskow() const override
	{

		if (czyPusty())
		{
			return true;
		}
		return false;

	}

	void przeladuj() override
	{
		magazynek.clear();
		liczbaPociskow = 0;
		puste = 0;
		pelne = 0;

		zaladuj();
		zliczPociski();
	}

	bool czyPusta() const override
	{
		if (magazynek.empty())
		{
			throw runtime_error("Magazynek jest pusty!");
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

	bool czyPusty() const override
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

	const vector<int>& pokazMagazynek() const override
	{

		return magazynek;

	}

	void ustawMagazynek(const vector<int>& nowyMagazynek) override
	{

		magazynek = nowyMagazynek;
		liczbaPociskow = static_cast<int>(magazynek.size());

	}

};

class Gracz : public IGracz
{

private:

	int HP;
	const int maxHP = 3;
	string nazwa;
	string typ;


public:

	Gracz(const string& nazwaGracza, const string& typGracza) : HP(maxHP), nazwa(nazwaGracza), typ(typGracza)
	{
		
	}

	bool czyZyje() const override
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

	void utrataHP() override
	{
		if (czyZyje()) {
			HP--;
		}
		else
		{
			return;
		}
	}

	void odzyskanieHP() override
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

	void resetHP() override
	{
		HP = maxHP;
	}

	int pokazHP() const override
	{
		return HP;
	}

	void ustawHP(int noweHP) override
	{
		HP = noweHP;
	}

	bool czyJestCzlowiekiem() const override
	{
		if (typ == "czlowiek" || typ == "Czlowiek")
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	bool czyJestKomputerem() const override
	{

		if (typ == "komputer" || typ == "Komputer")
		{
			return true;
		}
		else
		{
			return false;
		}

	}

};

class Strzal : public IStrzal
{

private:

public:

	void oddajStrzal(Gracz& cel, Gracz& strzelajacy, const int& wybor, Magazynek& magazynek) override
	{
		if (magazynek.czyPusty())
		{
			throw runtime_error("Brak pociskow w magazynku!");
		}
		else
		{
			if (wybor == 1)
			{

				if (magazynek.czyPusta())
				{
					cout << "Pudlo!";
					magazynek.zmniejszLiczbePustych();
				}
				else
				{
					cel.utrataHP();
					magazynek.zmniejszLiczbePelnych();
					cout << "Trafiony!";
				}
			}
			else
			{
				if (magazynek.czyPusta())
				{
					if (strzelajacy.pokazHP() < 3)
					{
						strzelajacy.odzyskanieHP();
						cout << "Udalo sie odzyskac 1 HP!";
					}
					else
					{
						cout << "Masz juz max HP! Nie mozesz odzyskac zdrowia!";
					}
					magazynek.zmniejszLiczbePustych();
				}
				else
				{
					strzelajacy.utrataHP();
					magazynek.zmniejszLiczbePelnych();
					cout << "Nie udalo sie odzyskac HP i straciles 1 HP!";
				}
			}
			magazynek.zmniejszLiczbePociskow();
		}

	}

};

class Zapis : public IZapis
{

private:

public:

	void zapiszStanGry(const Gracz& czlowiek, const Gracz& komputer, const int& zaczynajacy, const Magazynek& magazynek, const string& nazwaPliku) const override {

		string nazwa;
		nazwa = nazwaPliku;

		int hpkomputer = komputer.pokazHP();
		int hpczlowiek = czlowiek.pokazHP();
		int liczbaPociskow = magazynek.pokazLiczbePociskow();
		int pelne = magazynek.pokazPelne();
		int puste = magazynek.pokazPuste();
		int zaczyna = zaczynajacy;

		ofstream saveStanuGry(nazwa);

		if (saveStanuGry.is_open()) {

			if (saveStanuGry.fail()) {

				cout << "Blad podczas zapisu stanu gry!" << endl;

			}
			else {

				saveStanuGry << hpczlowiek << endl;
				saveStanuGry << hpkomputer << endl;	
				saveStanuGry << pelne << endl;
				saveStanuGry << puste << endl;
				saveStanuGry << liczbaPociskow << endl;
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

class Odczyt : public IOdczyt
{

private:

public:

	void wczytajStanGry(Gracz& czlowiek, Gracz& komputer, int& zaczynajacy, Magazynek& magazynek, const string& nazwaPliku) const override {

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
				int pelne;
				int puste;
				int liczbaPociskow;

				saveStanuGry >> hpczlowiek;
				saveStanuGry >> hpkomputer;
				saveStanuGry >> pelne;
				saveStanuGry >> puste;
				saveStanuGry >> liczbaPociskow;
				saveStanuGry >> zaczynajacy;

				czlowiek.ustawHP(hpczlowiek);
				komputer.ustawHP(hpkomputer);
				magazynek.ustawPelne(pelne);
				magazynek.ustawPuste(puste);
				magazynek.ustawLiczbePociskow(liczbaPociskow);

				vector<int> nowyMagazynek;

				for (int i = 0; i < liczbaPociskow; i++)
				{

					saveStanuGry >> pocisk;
					nowyMagazynek.push_back(pocisk);
				}

				magazynek.ustawMagazynek(nowyMagazynek);
				magazynek.zliczPociski();
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

class Interfejs : public IInterfejs
{

private:

public:

	void wyswietlStatystyki(const Gracz& czlowiek, const Gracz& komputer, const Magazynek& magazynek) const override
	{
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Statystyki:" << endl;
		cout << "czlowiek HP: " << czlowiek.pokazHP() << endl;
		cout << "komputer HP: " << komputer.pokazHP() << endl;
		cout << "Pelne pociski w magazynku: " << magazynek.pokazPelne() << endl;
		cout << "Puste pociski w magazynku: " << magazynek.pokazPuste() << endl;
		cout << "Pociski w magazynku: " << magazynek.pokazLiczbePociskow() << endl;
		//magazynek.pokazPociski(); //Do debugowania
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	}

	void przewinEkran() const override
	{
		for (int i = 0; i < 30; i++)
		{
			cout << endl;
		}
	}

	void menu() const override
	{

		cout << "Wybierz co chcesz zrobic:" << endl;
		cout << "0 - Sprobuj odzyskac 1 HP" << endl;
		cout << "1 - Strzel w komputera" << endl;
		cout << "5 - Zapisz gre" << endl;
		cout << "6 - Wczytaj gre" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Twoj wybor: ";

	}

	int podejmijDecyzje(int& wybor, const Gracz& gracz) const override {

		if (gracz.czyJestCzlowiekiem())
		{
			cin >> wybor;
		}

		else
		{
			wybor = rand() % 2;
		}

		return wybor;
	}

	void cinZapis(string& nazwaPliku) override
	{

		cout << "Podaj nazwe zapisu, ktory chcesz zapisac: ";
		cin >> nazwaPliku;
		nazwaPliku += ".txt";

	}

	void cinOdczyt(string& nazwaPliku) override
	{
		cout << "Podaj nazwe zapisu, ktory chcesz wczytac: ";
		cin >> nazwaPliku;
		nazwaPliku += ".txt";
	}

	void cinNieprawidowyWybor() const override
	{
		cout << "Nieprawidlowy wybor. Straciles ture!" << endl;
	}

	void cinWygranaKomputera() const override
	{
		cout << "Komputer wygrywa gre!" << endl;
	}

	void cinWygranaCzlowieka() const override
	{
		cout << "Wygrywasz gre!" << endl;
	}

	void cinWybieraKomputer() const override
	{
		cout << "Wybiera komputer!" << endl;
	}

	void cinZaczynaKomputer() const override
	{
		cout << "Zaczyna komputer!" << endl;
	}

	void cinZaczynaCzlowiek() const override
	{
		cout << "Zaczynasz ty!" << endl;
	}

	void cinKoniecPociskow() const override	
	{
		cout << "Koniec pociskow w magazynku! Przeladowanie!" << endl;
	}

	void cinPodziekowanie() const override
	{
		cout << "Dziekuje za gre! Do zobaczenia!" << endl;
	}

	void cinCzyKontynuowac() const override
	{
		cout << "Czy chcesz kontynuowac gre? (t/n): ";
	}	

	void cinWskaznik() const override
	{
		cout << "										*" << endl;
	}

	void cinEndl() const override
	{
		cout << endl;
	}

};

class Gra : public IGra
{

private:

	int wybor = 0;
	int zaczynajacy = 0;

	string nazwaPliku = "";

	Odczyt odczyt;
	Zapis zapis;
	Strzal strzal;
	Interfejs ui;
	Magazynek magazynek;
	Gracz czlowiek;
	Gracz komputer;

public:

	Gra(Odczyt odczyt, Zapis zapis) : czlowiek("czlowiek", "czlowiek"), komputer("komputer", "komputer"), odczyt(odczyt), zapis(zapis)
	{

	}

	void losowanieZaczynajacego(int& zaczynajacy, const Interfejs& ui) override
	{

		if (rand() % 2 == 1)
		{
			zaczynajacy = 1;
			ui.cinZaczynaCzlowiek();
		}
		else
		{
			zaczynajacy = 0;
			ui.cinZaczynaKomputer();
		}
	}

	bool czyChceKontynuowac() override
	{
		char wybor;
		ui.cinCzyKontynuowac();
		cin >> wybor;
		if (wybor == 't' || wybor == 'T')
		{
			czlowiek.resetHP();
			komputer.resetHP();
			magazynek.przeladuj();
			ui.przewinEkran();
			return true;
		}
		else
		{
			ui.cinPodziekowanie();
			return false;
		}
	}

	void wygrana(const Gracz& czlowiek, const Gracz& komputer, const Interfejs& ui) override
	{

		if (czyChceKontynuowac())
		{
			rozpocznijGre();
		}
		else
		{
			return;
		}

	}

	void nowaTura(const Gracz& czlowiek, const Gracz& komputer, const Interfejs& ui, Magazynek& magazynek) override
	{

		ui.cinKoniecPociskow();
		magazynek.przeladuj();
		ui.wyswietlStatystyki(czlowiek, komputer, magazynek);

	}

	bool ktoWygral(const Gracz& czlowiek, const Gracz& komputer, const Interfejs& ui) override
	{

		if (!czlowiek.czyZyje())
		{
			ui.cinWygranaKomputera();
			wygrana(czlowiek, komputer, ui);
			return true;
		}
		else if (!komputer.czyZyje())
		{
			ui.cinWygranaCzlowieka();
			wygrana(czlowiek, komputer, ui);
			return true;
		}
		return false;

	}

	void rozpocznijGre() override
	{

		czlowiek.resetHP();	
		komputer.resetHP();
		magazynek.przeladuj();
		losowanieZaczynajacego(zaczynajacy, ui);
		ui.wyswietlStatystyki(czlowiek, komputer, magazynek);

		while (true)
		{

			if (zaczynajacy == 1)
			{

				ui.menu();
				ui.podejmijDecyzje(wybor, czlowiek);

				int liczbaPociskow = magazynek.pokazLiczbePociskow();

				if (wybor == 1)
				{

					zaczynajacy = 0;
					strzal.oddajStrzal(komputer, czlowiek, wybor, magazynek);
					ui.cinWskaznik();
				}
				else if (wybor == 0)
				{

					zaczynajacy = 0;
					strzal.oddajStrzal(czlowiek, czlowiek, wybor, magazynek);
					ui.cinWskaznik();

				}
				else if (wybor == 5)
				{

					ui.cinZapis(nazwaPliku);
					zapis.zapiszStanGry(czlowiek, komputer, zaczynajacy, magazynek, nazwaPliku);
					ui.wyswietlStatystyki(czlowiek, komputer, magazynek);
					ui.cinWskaznik();

				}
				else if (wybor == 6)
				{

					ui.cinOdczyt(nazwaPliku);
					odczyt.wczytajStanGry(czlowiek, komputer, zaczynajacy, magazynek, nazwaPliku);
					ui.wyswietlStatystyki(czlowiek, komputer, magazynek);
					ui.cinWskaznik();

				}
				else
				{

					zaczynajacy = 0;
					ui.cinNieprawidowyWybor();
					ui.cinWskaznik();

				}

			}
			else
			{
				zaczynajacy = 1;
				ui.cinWybieraKomputer();
				ui.podejmijDecyzje(wybor, komputer);

				if (wybor == 1)
				{
					strzal.oddajStrzal(czlowiek, komputer, wybor, magazynek);
					ui.cinEndl();
				}
				else
				{
					strzal.oddajStrzal(komputer, komputer, wybor, magazynek);
					ui.cinEndl();
				}
			}
			ui.wyswietlStatystyki(czlowiek, komputer, magazynek);

			if (ktoWygral(czlowiek, komputer, ui))
			{
				break;
			}

			if (magazynek.czyKoniecPociskow())
			{
				nowaTura(czlowiek, komputer, ui, magazynek);
			}

		}

	}

};

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));

	Zapis zapis;
	Odczyt odczyt;
	Gra gra(odczyt, zapis);

	gra.rozpocznijGre();

	return 0;
}
