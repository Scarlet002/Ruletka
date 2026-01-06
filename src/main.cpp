#include "GameConsoleVersion.h"
#include "GameSFMLVersion.h"
#include "SaveTXTManager.h"
#include "LoadTXTManager.h"
#include "SaveJSONManager.h"
#include "LoadJSONManager.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::exception;

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));

    SaveTXTManager saverTXT;
    LoadTXTManager loaderTXT;
    SaveJSONManager saverJSON;
    LoadJSONManager loaderJSON;

    try
    {
        //GameConsoleVersion game(loaderJSON, saverJSON);
		//game.StartGame();

        GameSFMLVersion game(loaderJSON, saverJSON);
        game.Run();
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