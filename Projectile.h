#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>

using namespace std;

class Projectile : public sf::Drawable
{
private:
    sf::CircleShape shape;  // Kształt pocisku
    float velocity;  // Prędkość pocisku (pozytywna lub negatywna w osi Y)
    bool destroyed;  // Flaga oznaczająca, czy pocisk został zniszczony

    // Funkcja rysująca obiekt Projectile na ekranie (wymagane przez sf::Drawable)
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Projectile(sf::Vector2f position, float velocity);  // Konstruktor inicjalizujący pocisk

    void update();  // Aktualizacja pozycji pocisku
    void destroy();  // Oznaczenie pocisku jako zniszczonego

    sf::FloatRect getBounds() const;  // Pobranie granic pocisku (do kolizji)
    bool isInBounds() const;  // Sprawdzenie, czy pocisk jest w granicach okna
    bool isDestroyed() const;  // Sprawdzenie, czy pocisk został zniszczony
};

#endif // PROJECTILE_H

