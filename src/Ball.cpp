#include "Ball.h"
#include <cmath>
#include <typeinfo>

Ball::Ball(float radius, const sf::Vector2f& startPosition, GameObject* parent=nullptr)
    :GameObject(parent),
    shape_(radius),
    velocity_(),
    startPosition_(startPosition){
        setPosition(startPosition);
        shape_.setFillColor(sf::Color::White);  //riempiemento colore
        shape_.setOrigin(radius,radius);        //centra l'origine
        reset();
    }



void Ball::syncTransform(){
    shape_.setPosition(transform.getPosition());
    shape_.setRotation(transform.getRotation());
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
        velocity_.x*=std::cos(angle);
        velocity_.y*=std::sin(angle);
    }
    
    
    
    void Ball::bounceX() {
        velocity_.x *= -1;
        // Aumenta leggermente la velocità dopo ogni rimbalzo
        velocity_ *= 1.05f; 
    }
    
    void Ball::bounceY() {
        velocity_.y *= -1;
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
        bounceY();
    }
 }

void Ball::setPosition(const sf::Vector2f& position){
    GameObject::setPosition(position);
    shape_.setPosition(position);
}
    
void Ball::move(const sf::Vector2f& offset){
    GameObject::move(offset);
    shape_.move(offset);
}

void Ball::updateTrail() {
    sf::CircleShape trailDot = shape_;
    trailDot.setRadius(shape_.getRadius() * 0.7f);
    trail_.push_back(trailDot);
    if (trail_.size() > 5) trail_.erase(trail_.begin());
}


void Ball::onBoundaryHit(){
    bounceX();
}