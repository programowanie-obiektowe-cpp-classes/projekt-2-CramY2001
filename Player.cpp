#include "Player.h"
#include <chrono>

using namespace std;

Player::Player(sf::Vector2f position) : health(3), shootCooldown(0.1f) // Cooldown strzału
{
    shape.setSize(sf::Vector2f(20, 50));  // Ustawienie rozmiaru gracza
    shape.setFillColor(sf::Color::Green);  // Ustawienie koloru gracza
    shape.setPosition(position);  // Ustawienie początkowej pozycji gracza
    lastShotTime = chrono::steady_clock::now();  // Inicjalizacja czasu ostatniego strzału
}

void Player::move(float dx)
{
    sf::Vector2f position = shape.getPosition();
    if ((dx < 0 && position.x > 0) || (dx > 0 && position.x + shape.getSize().x < 800)) {
        shape.move(dx, 0);
    }
}

void Player::shoot(vector<Projectile>& projectiles)
{
    auto now = chrono::steady_clock::now();
    float elapsedTime = chrono::duration<float>(now - lastShotTime).count();

    if (elapsedTime >= shootCooldown)
    {
        // Dodanie nowego pocisku na górze gracza
        projectiles.emplace_back(shape.getPosition() + sf::Vector2f(shape.getSize().x / 2, -10), -5);
        lastShotTime = now;  // Aktualizacja czasu ostatniego strzału
    }
}

void Player::takeDamage()
{
    --health;  // Zmniejszenie liczby żyć gracza
}

sf::FloatRect Player::getBounds() const
{
    return shape.getGlobalBounds();  // Pobranie granic gracza (do kolizji)
}

int Player::getHealth() const
{
    return health;  // Zwrócenie liczby żyć gracza
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(shape, states);  // Rysowanie gracza na ekranie
}
