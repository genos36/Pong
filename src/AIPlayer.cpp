#include "AIPlayer.h"

AIPlayer::AIPlayer(Ball* ball):targetBall_(ball){}


    void AIPlayer::update(float deltaTime, Paddle& paddle)  {
        // Simple follow-the-ball AI
        if (targetBall_) {
            float ballY = targetBall_->getPosition().y;
            float paddleY = paddle.getPosition().y;
            
            float direction = (ballY > paddleY + 10.f) ? 1.f : 
                            (ballY < paddleY - 10.f) ? -1.f : 0.f;
            
            paddle.move(sf::Vector2f(0, direction * speed_ * deltaTime));
        }
    }


     void AIPlayer::setTargetBall(const Ball* ball) { targetBall_ = ball; }
     void AIPlayer::handleEvent(const sf::Event& event){}