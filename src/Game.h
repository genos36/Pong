#ifndef GAME_H
#define GAME_H
#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"
#include "Score.h"
#include "HumanPlayer.h"



#ifndef test

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
    sf::Font font_;
    Score playerScore_;
    Score aiScore_;
    sf::FloatRect gameArea_;

    void initializeWindow() ;
void initializeFont();
void initializeGameObjects();


public:
    static  constexpr float  PADDLE_SIZE_X=10.0f;
    static  constexpr float  PADDLE_SIZE_Y=100.0f;
    static  constexpr float  PADDLE_START_POS_X=100.0f;
    static  constexpr float  PADDLE_START_POS_Y=400.0f;


    static  constexpr float  BALL_RADIUS=15.0f;

    unsigned int width() const;
    unsigned int height() const;



    Game(int width, int height, const std::string& title);
    void run();


};

#endif

#ifdef test
/*
class Game {
private:
    sf::RenderWindow window_;
    Ball ball_;


public:
    Game(int width, int height, const std::string& title);
    void run();


};
*/
#endif



#endif