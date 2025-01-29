#include "../include/Projectile.h"

using namespace std;

Projectile::Projectile(sf::Vector2f position, float velocity) : velocity(velocity), destroyed(false)
{
    shape.setRadius(5);  // Ustawienie promienia pocisku
    shape.setFillColor(sf::Color::White);  // Ustawienie koloru pocisku
    shape.setPosition(position);  // Ustawienie początkowej pozycji pocisku
}

void Projectile::update()
{
    shape.move(0, velocity);  // Ruch pocisku w osi Y
}

void Projectile::destroy()
{
    destroyed = true;  // Oznaczenie pocisku jako zniszczonego
}

sf::FloatRect Projectile::getBounds() const
{
    return shape.getGlobalBounds();  // Pobranie granic pocisku (do kolizji)
}

bool Projectile::isInBounds() const
{
    return shape.getPosition().y > 0 && shape.getPosition().y < 600;  // Sprawdzenie, czy pocisk mieści się w granicach okna
}

bool Projectile::isDestroyed() const
{
    return destroyed;  // Sprawdzenie, czy pocisk został zniszczony
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(shape, states);  // Rysowanie pocisku na ekranie
}


