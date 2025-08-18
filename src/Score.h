#ifndef SCORE_H
#define SCORE_H

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Observer.h"

class Score:public Observer {
private:
    void updateText();

    unsigned int value_;
    sf::Text text_;
    sf::Font font_;


public:
    Score(const sf::Font& font, unsigned int size, const sf::Vector2f& position);
    void update(const GameObject&)override;
    void increase();
    void reset();
    unsigned int getValue() const;
    
    void setPosition(const sf::Vector2f& position);
    void setColor(const sf::Color& color);
    
    void draw(sf::RenderWindow& window) const;
    void setFont(const sf::Font& font);

};

#endif