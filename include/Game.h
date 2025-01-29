#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"

using namespace std;

class Game
{
private:
    sf::RenderWindow window;  // Główne okno gry
    Player player;  // Obiekt gracza
    vector<Enemy> enemies;  // Lista wrogów
    vector<Projectile> playerProjectiles;  // Lista pocisków gracza
    vector<Projectile> enemyBombs;  // Lista bomb zrzuconych przez wrogów
    sf::Font font;  // Czcionka używana w grze
    sf::Text scoreText;  // Tekst wyświetlający wynik
    sf::Text livesText;  // Tekst wyświetlający liczbę życ
    sf::Text gameOverText;  // Tekst wyświetlany po zakończeniu gry

    int score;  // Aktualny wynik gracza
    bool isGameOver;  // Flaga oznaczająca koniec gry

    int level;  // Aktualny poziom gry
    float enemyShootCooldown;  // Czas między strzałami wrogów

    void processEvents();  // Przetwarzanie zdarzeń
    void update();  // Aktualizacja logiki gry
    void render();  // Renderowanie grafiki
    void spawnEnemies();  // Tworzenie nowych wrogów
    void checkCollisions();  // Sprawdzanie kolizji

public:
    Game();  // Konstruktor gry
    void run();  // Główna pętla gry
};

#endif // GAME_H
