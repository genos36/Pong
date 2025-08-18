#ifndef BALL_H
#define BALL_H

#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "GameObject.h"

class Ball:public GameObject {   
private:
    static constexpr float MAX_SPEED = 1000.0f;
    static constexpr float BOOST_FACTOR  = 1.05f;
    static constexpr float INITIAL_VELOCITY  = 40.0f;

    sf::CircleShape shape_; //simulatee the ball
    sf::Vector2f velocity_; //handle the speed of movement and the direction
    sf::Vector2f startPosition_;

protected:

    void onBoundaryHit(const BoundaryCheck&)override;
    sf::FloatRect getGlobalBounds() const override;
    void syncTransform() override ;

    public:
    
    Ball(float radius, const sf::Vector2f & position);
    
    
    
    void update(float deltaTime) override;
    void draw(sf::RenderTarget& target) const override;

    

    void handleCollision(GameObject& other) override;
    void handleBoundaries(const BoundaryCheck& bound) override;
/*
    void setPosition(const sf::Vector2f& position)override;
    void move(const sf::Vector2f& offset);
*/
    void reset();
    void bounceX();
    void bounceY();
    void setFillColor(sf::Color color);

    sf::Vector2f getVelocity() const;
    void setVelocity(const sf::Vector2f& velocity);

    float getRadius()const{return shape_.getRadius();}


};

#endif