// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Projectile.h"
#include <chrono>

using namespace std;

class Player : public sf::Drawable {
private:
    sf::RectangleShape shape;  // Kształt gracza
    int health;  // Liczba żyć gracza

    float shootCooldown;  // Minimalny czas między strzałami (w sekundach)
    chrono::steady_clock::time_point lastShotTime;  // Czas ostatniego strzału

    // Funkcja rysująca obiekt Player na ekranie (wymagane przez sf::Drawable)
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Player(sf::Vector2f position);  // Konstruktor inicjalizujący gracza na podanej pozycji

    void move(float dx);  // Poruszanie gracza w poziomie
    void shoot(vector<Projectile>& projectiles);  // Strzał pociskiem
    void takeDamage();  // Odejmowanie punktu życia

    sf::FloatRect getBounds() const;  // Pobranie granic gracza (do kolizji)
    int getHealth() const;  // Pobranie liczby żyć gracza
};

#endif // PLAYER_H
