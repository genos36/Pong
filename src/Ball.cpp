#include "Ball.h"
#include <cmath>
#include <typeinfo>



Ball::Ball(float radius, const sf::Vector2f& startPosition)
    :shape_(radius),
    velocity_(INITIAL_VELOCITY,INITIAL_VELOCITY),
    startPosition_(startPosition){
        setPosition(startPosition);
        shape_.setFillColor(sf::Color::Green);  //riempiemento colore

        reset();
    }



void Ball::syncTransform(){
    auto transform=getTransform();
    shape_.setPosition(transform.getPosition());
    shape_.setRotation(transform.getRotation());
    shape_.setScale(transform.getScale());
}


void Ball::update(float deltaTime) {
    move(velocity_ * deltaTime);//aggiorna la posizione partendo dal valore attuale
    }

    
void Ball::draw(sf::RenderTarget& target) const{
        target.draw(shape_);
    }

    void Ball::reset() {
        setPosition(startPosition_);
        
        // Velocità iniziale casuale (sinistra/destra)
        float angle = (rand() % 60 - 30) * 3.14159f / 180.f; // angolo casuale da -30 gradi a +30
        velocity_.x=INITIAL_VELOCITY*std::cos(angle);
        velocity_.y=INITIAL_VELOCITY*std::sin(angle);
    }
    
    
    
    void Ball::bounceX() {
        velocity_.x *= -1.0f;
        if(abs(std::sqrt(velocity_.x*velocity_.x + velocity_.y*velocity_.y)<MAX_SPEED)){
            velocity_*=BOOST_FACTOR;
        }        
        notifyAll(); // Notify observers
    }
    
    void Ball::bounceY() {
        velocity_.y *= -1.0f;
        if(abs(std::sqrt(velocity_.x*velocity_.x + velocity_.y*velocity_.y)<MAX_SPEED)){
            velocity_*=BOOST_FACTOR;
        } 
        notifyAll(); // Notify observers
    }
    
    void Ball::setFillColor(sf::Color color) {
        shape_.setFillColor(color);
    }
    
    sf::Vector2f Ball::getVelocity() const{
        return velocity_;
    }
    
    sf::FloatRect Ball::getGlobalBounds() const {
        return shape_.getGlobalBounds();
    } 
    void Ball::setVelocity(const sf::Vector2f& velocity){
        velocity_=velocity;
    }
    
 void Ball::handleCollision(GameObject& other){
    if(checkCollision(other)){
        switch(getCollisionSide(other)){
            case BoundaryCheck::RIGHT:
            case BoundaryCheck::LEFT:
                bounceX();
                break;
            case BoundaryCheck::BOTTOM:
            case BoundaryCheck::TOP:
                bounceY();
                break;
                
        }
    }
 }


void Ball::onBoundaryHit(const BoundaryCheck& bound){
    notifyAll();

}

void Ball::handleBoundaries(const BoundaryCheck& bound) {
    switch(bound) {
        case BoundaryCheck::LEFT:
        case BoundaryCheck::RIGHT:
            bounceX();
            break;
        case BoundaryCheck::TOP:
        case BoundaryCheck::BOTTOM:
            bounceY();
            break;
        default: break;
    }
    
}


