#ifndef GAME_H
#define GAME_H
#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"
#include "Score.h"

class Game {
private:
    void processEvents();
    void update(float deltaTime);
    void render();
    void resetRound();

    sf::RenderWindow window_;
    Paddle playerPaddle_;
    Paddle aiPaddle_;
    Ball ball_;
    Score playerScore_;
    Score aiScore_;
    sf::Font font_;
    
    static const sf::Vector2f paddleSize_();
    static const float aiDifficulty_() ; // 0-1
public:
    Game(int width, int height, const std::string& title);
    void run();


};
#endif