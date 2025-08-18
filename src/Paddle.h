#ifndef PADDLE_H
#define PADDLE_H

#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "AbstractPlayer.h"
class AbstractPlayer;

class Paddle :public GameObject{
private:
    sf::RectangleShape shape_;
    sf::Vector2f velocity_;
    sf::Vector2f startPosition_;
    std::unique_ptr<AbstractPlayer> controller_;

protected:
    void onBoundaryHit(const BoundaryCheck&) override;// Callback per eventi
    virtual sf::FloatRect getGlobalBounds() const override;
    virtual void syncTransform() override;
    bool shouldCollide(const GameObject& other) const override;
 

public:
    Paddle(const sf::Vector2f& size, const sf::Vector2f& startPosition);

    void update(float deltaTime)override;
    void draw(sf::RenderTarget& window) const override;

    void handleCollision(GameObject& other) override;
    void handleBoundaries(const BoundaryCheck& bound) override;

    void moveUp();
    void moveDown();
    void stop();

    void reset();

    const sf::Vector2f& getVelocity()const ;


void setFillColor(const sf::Color& color); 

    sf::Vector2f getSize() const;
    void setController(std::unique_ptr<AbstractPlayer> controller) ;
};

#endif