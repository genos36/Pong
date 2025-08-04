#ifndef PADDLE_H
#define PADDLE_H

#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Paddle :public GameObject{
private:
    sf::RectangleShape shape_;
    sf::Vector2f velocity_;
    sf::Vector2f startPosition_;

public:
    Paddle(const sf::Vector2f& size, const sf::Vector2f& startPosition_,GameObject parent=nullptr);

    void syncTransform()override;

    void update(float deltaTime)override;
    void draw(sf::RenderTarget& target) const override;
    sf::FloatRect getGlobalBounds() const override;
    
    void moveUp();
    void moveDown();
    void stop();
    
    void setSpeed(float speed);
    void setFillColor(const sf::Color& color);
    void setPosition(float x, float y);
    
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;



};

#endif