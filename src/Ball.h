#ifndef BALL_H
#define BALL_H

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Ball {   
private:
    sf::CircleShape shape_;
    sf::Vector2f velocity_;
    sf::Vector2f startPosition_;
    float speed_;
    std::vector<sf::CircleShape> trail_;
public:
    Ball(float radius, const sf::Vector2f & position);
    


    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void reset();
    void bounceX();
    void bounceY();
    void setFillColor(sf::Color color);

    const sf::Vector2f getPosition() const;
    const sf::Vector2f& getVelocity() const;
    const sf::FloatRect getGlobalBounds() const;

    void setVelocity(const sf::Vector2f& velocity);

    void updateTrail();

};

#endif