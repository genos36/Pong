#ifndef ABSTRACTPLAYER_H
#define ABSTRACTPLAYER_H

#include "Paddle.h"
#include "Ball.h"
class Paddle;
class AbstractPlayer{
    private:
    Paddle* paddle;
    protected:

    public:
    virtual ~AbstractPlayer() = default;

    // Handle input/update (called every frame)
    virtual void update(float deltaTime, Paddle& paddle) = 0;

    // Optional: Handle SFML events
    virtual void handleEvent(const sf::Event& event) =0;



};


#endif