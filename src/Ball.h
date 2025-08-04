#ifndef BALL_H
#define BALL_H

#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "GameObject.h"

class Ball:public GameObject {   
private:
    sf::CircleShape shape_;
    sf::Vector2f velocity_;
    sf::Vector2f startPosition_;
    std::list<sf::CircleShape> trail_;
protected:
    void onBoundaryHit()override;

    public:
    
    Ball(float radius, const sf::Vector2f & position, GameObject* parent=nullptr);
    
    void syncTransform() override ;
    
    void update(float deltaTime) override;

    void draw(sf::RenderTarget& target) const override;

    sf::FloatRect getGlobalBounds() const override;

    void handleCollision(GameObject& other) override;

    void setPosition(const sf::Vector2f& position)override;

    void move(const sf::Vector2f& offset);

    void reset();
    void bounceX();
    void bounceY();
    void setFillColor(sf::Color color);

    sf::Vector2f getVelocity() const;




    void setVelocity(const sf::Vector2f& velocity);

    void updateTrail();
};

#endif