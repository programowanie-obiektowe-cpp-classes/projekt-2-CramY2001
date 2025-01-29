// Enemy.cpp
#include "Enemy.h"

using namespace std;

Enemy::Enemy(sf::Vector2f position) : destroyed(false)

{
    shape.setPointCount(3);  // Kształt trójkąta wymaga 3 punktów
    shape.setPoint(0, sf::Vector2f(0, 0));  // Wierzchołek górny
    shape.setPoint(1, sf::Vector2f(-20, -40));  // Lewy dolny wierzchołek
    shape.setPoint(2, sf::Vector2f(20, -40));  // Prawy dolny wierzchołek
    shape.setFillColor(sf::Color::Red);  // Kolor wroga
    shape.setPosition(position);  // Pozycja startowa
}

void Enemy::update()
{
    shape.move(0, 0.1f);  // Powolny ruch w dół
}

void Enemy::dropBomb(vector<Projectile>& bombs)
{
    // Tworzenie nowego pocisku (bomby) na pozycji wroga
    bombs.emplace_back(shape.getPosition() + sf::Vector2f(0, -40), 4);
}

void Enemy::destroy()
{
    destroyed = true;  // Oznaczenie wroga jako zniszczonego
}

sf::FloatRect Enemy::getBounds() const
{
    return shape.getGlobalBounds();  // Pobranie granic wroga (do kolizji)
}

bool Enemy::isDestroyed() const
{
    return destroyed;  // Sprawdzenie, czy wróg został zniszczony
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(shape, states);  // Rysowanie wroga na ekranie
}

