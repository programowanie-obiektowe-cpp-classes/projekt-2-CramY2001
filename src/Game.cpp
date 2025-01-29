#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Game::Game()
    : window(sf::VideoMode(800, 600), "Space Invaders"),
      player(sf::Vector2f(400, 550)),
      score(0),
      isGameOver(false),
      level(1),  // Inicjalizacja poziomu
      enemyShootCooldown(2.0f) // Inicjalizacja cooldownu wrogów
{
    window.setFramerateLimit(60);

    if (!font.loadFromFile("arial.ttf"))
    {
        throw runtime_error("Failed to load font");
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setPosition(10, 10);

    livesText.setFont(font);
    livesText.setCharacterSize(20);
    livesText.setPosition(10, 40);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Game Over");
    gameOverText.setPosition(200, 250);

    spawnEnemies();
    srand(static_cast<unsigned>(std::time(nullptr)));
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        if (!isGameOver)
        {
            update();
        }
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }

    if (!isGameOver)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            player.move(-5);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            player.move(5);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            player.shoot(playerProjectiles);
        }
    }
}

void Game::render()
{
    window.clear();

    if (!isGameOver)
    {
        window.draw(player);
        for (const auto& projectile : playerProjectiles)
        {
            window.draw(projectile);
        }
        for (const auto& enemy : enemies)
        {
            window.draw(enemy);
        }
        for (const auto& bomb : enemyBombs)
        {
            window.draw(bomb);
        }

        scoreText.setString("Score: " + to_string(score));
        window.draw(scoreText);

        livesText.setString("Lives: " + to_string(player.getHealth()));
        window.draw(livesText);
    } else {
        window.draw(gameOverText);
    }

    window.display();
}

void Game::spawnEnemies()
{
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            enemies.emplace_back(sf::Vector2f(100 + i * 120, 50 + j * 60));
        }
    }
    level++;
}

void Game::update()
{
    for (auto& projectile : playerProjectiles)
    {
        projectile.update();
    }

    for (auto& enemy : enemies)
    {
        enemy.update();
        if (rand() % 1000 < level) // Większa szansa na strzał na wyższych poziomach
        {
            enemy.dropBomb(enemyBombs);
        }

        // Sprawdzenie, czy wróg dotarł do dolnej granicy okna
        if (enemy.getBounds().top + enemy.getBounds().height >= window.getSize().y)
        {
            isGameOver = true;  // Koniec gry, jeśli wróg dotknie dolnej granicy
        }
    }

    for (auto& bomb : enemyBombs)
    {
        bomb.update();
    }

    checkCollisions();

    playerProjectiles.erase(remove_if(playerProjectiles.begin(), playerProjectiles.end(), [](const Projectile& p)
    {
        return !p.isInBounds();
    }), playerProjectiles.end());

    enemyBombs.erase(std::remove_if(enemyBombs.begin(), enemyBombs.end(), [](const Projectile& b)
    {
        return !b.isInBounds() || b.isDestroyed();
    }), enemyBombs.end());

    enemies.erase(remove_if(enemies.begin(), enemies.end(), [](const Enemy& e)
    {
        return e.isDestroyed();
    }), enemies.end());

    if (enemies.empty())
    {
        spawnEnemies();
    }

    if (player.getHealth() <= 0)
    {
        isGameOver = true;
    }
}

void Game::checkCollisions()
{
    for (auto& projectile : playerProjectiles)
    {
        for (auto& enemy : enemies)
        {
            if (projectile.getBounds().intersects(enemy.getBounds()))
            {
                enemy.destroy();       // Zniszczenie wroga
                projectile.destroy();  // Zniszczenie pocisku
                score += 10;           // Dodanie punktów za trafienie
            }
        }
    }

    for (auto& bomb : enemyBombs)
    {
        if (bomb.getBounds().intersects(player.getBounds()))
        {
            player.takeDamage();  // Gracz traci życie
            bomb.destroy();       // Bomba zostaje zniszczona po trafieniu gracza
        }
    }

    playerProjectiles.erase(remove_if(playerProjectiles.begin(), playerProjectiles.end(), [](const Projectile& p)
    {
        return !p.isInBounds() || p.isDestroyed();
    }), playerProjectiles.end());

    enemyBombs.erase(std::remove_if(enemyBombs.begin(), enemyBombs.end(), [](const Projectile& b)
    {
        return !b.isInBounds() || b.isDestroyed();
    }), enemyBombs.end());

    enemies.erase(remove_if(enemies.begin(), enemies.end(), [](const Enemy& e)
    {
        return e.isDestroyed();
    }), enemies.end());

    if (enemies.empty())
    {
        spawnEnemies();
    }

    if (player.getHealth() <= 0)
    {
        isGameOver = true;
    }
}
