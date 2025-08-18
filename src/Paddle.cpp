#include "Paddle.h"
#include "Game.h"

void Paddle::onBoundaryHit(const BoundaryCheck&) {};

sf::FloatRect Paddle::getGlobalBounds() const{
    return shape_.getGlobalBounds();
}

void Paddle::syncTransform(){
    sf::Transformable tempTransform=getTransform();
    shape_.setPosition(tempTransform.getPosition());
    shape_.setRotation(tempTransform.getRotation());
    shape_.setScale(tempTransform.getScale());
}

Paddle::Paddle(const sf::Vector2f& size, const sf::Vector2f& startPosition) 
    : shape_(size), velocity_(0.0f, 5.0f),startPosition_(startPosition),controller_(nullptr) {
    setPosition(startPosition);
    setFillColor(sf::Color::White);
}



void Paddle::update(float deltaTime) {
        if (controller_) {
            controller_->update(deltaTime, *this);
        }    
    }


void Paddle::draw(sf::RenderTarget& window)const{
    window.draw(shape_);
}

    void Paddle::handleCollision(GameObject& other) {}

    void Paddle::handleBoundaries(const BoundaryCheck& bound) {
        switch(bound){
            
            case BoundaryCheck::BOTTOM:
                setPosition(sf::Vector2f(getPosition().x,getPosition().y-10.f));
                break;
            case BoundaryCheck::TOP:
                setPosition(sf::Vector2f(getPosition().x,getPosition().y+10.f));
                break;
            case BoundaryCheck::RIGHT:
            case BoundaryCheck::LEFT:
            default: return;
        }
    }




void Paddle::moveUp() {
    velocity_.y = -abs(velocity_.y );
}

void Paddle::moveDown() {
    velocity_.y = abs(velocity_.y );
}

void Paddle::stop() {
    velocity_.y = 0.0f;
}


void Paddle::setFillColor(const sf::Color& color) {
    shape_.setFillColor(color);
}

sf::Vector2f Paddle::getSize() const {
    return shape_.getSize();
}

bool Paddle::shouldCollide(const GameObject& other) const {
    return false;
}


    void Paddle::setController(std::unique_ptr<AbstractPlayer> controller) {
        controller_ = std::move(controller);
    }


    void Paddle::reset(){
        setPosition(startPosition_);
        velocity_=sf::Vector2f(0.0f,0.0f);
    }


    const sf::Vector2f& Paddle::getVelocity()const {return velocity_;}