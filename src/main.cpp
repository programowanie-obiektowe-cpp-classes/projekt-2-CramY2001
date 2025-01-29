#include "Game.h"
#include <iostream>
#include <exception>
using namespace std;
int main()
{
    try
    {
        Game game;      // Tworzymy instancję gry
        game.run();     // Uruchamiamy główną pętlę gry
    }
    catch (const exception& e)
    {
        // Obsługa wyjątków
        cerr << "Wystapil blad: " << e.what() << endl;
        return EXIT_FAILURE;
    }
    catch (...)
    {
        // Obsługa innych, nieoczekiwanych wyjątków
        cerr << "Wystapil nieznany blad" << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS; // Zakończenie programu bez błędów
}
