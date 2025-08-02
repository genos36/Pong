#ifndef PADDLE_H
#define PADDLE_H

#pragma once
#include <SFML/Graphics.hpp>

class Paddle {
private:
    sf::RectangleShape shape_;
    sf::Vector2f velocity_;
    float speed_;
public:
    Paddle(const sf::Vector2f& size, const sf::Vector2f& position);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    
    void moveUp();
    void moveDown();
    void stop();
    
    void setSpeed(float speed);
    void setFillColor(const sf::Color& color);
    void setPosition(float x, float y);
    
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getSize() const;



};

#endif