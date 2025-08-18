#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "AbstractPlayer.h"


class HumanPlayer: public AbstractPlayer{
    private:
    sf::Keyboard::Key upKey_, downKey_;
     const float speed_ = 500.f;
    protected:

    public:
    HumanPlayer(sf::Keyboard::Key up, sf::Keyboard::Key down);

    // Handle input/update (called every frame)
    void update(float deltaTime, Paddle& paddle) override;

    // Optional: Handle SFML events
    void handleEvent(const sf::Event& event) override;



};


#endif