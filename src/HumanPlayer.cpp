#include "HumanPlayer.h"

    void HumanPlayer::update(float deltaTime, Paddle& paddle)  {
        float direction = 0.f;
        if (sf::Keyboard::isKeyPressed(upKey_)) direction=-1.0f;
        if (sf::Keyboard::isKeyPressed(downKey_)) direction=1.0f;
        
            paddle.move(sf::Vector2f(0.0f,direction* speed_ * deltaTime));
    }


        HumanPlayer::HumanPlayer(sf::Keyboard::Key up, sf::Keyboard::Key down) 
        : upKey_(up), downKey_(down) {}


        void HumanPlayer::handleEvent(const sf::Event& event){}