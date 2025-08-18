#ifndef AIPLAYER_H
#define AIPLAYER_H
// AIPlayer.h

#include "Ball.h"
#include "AbstractPlayer.h"

class AIPlayer : public AbstractPlayer {
    
private:
        const Ball* targetBall_ = nullptr;
        const float speed_ = 400.f; // Slightly slower than human




public:

    AIPlayer(Ball* ball);
    void update(float deltaTime, Paddle& paddle) override;
    
    void setTargetBall(const Ball* ball) ;
    void handleEvent(const sf::Event& event) override;




};


#endif