#include "Ball.h"
#include <cmath>
Ball::Ball(float radius, const sf::Vector2f & position)
    :shape_(radius),velocity_(),startPosition_(position),speed_(400.f){

        shape_.setFillColor(sf::Color::White);  //riempiemento colore
        shape_.setOrigin(radius,radius);        //centra l'origine
        reset();
    }

void Ball::update(float deltaTime) {
    shape_.move(velocity_ * deltaTime); //aggiorna la posizione partendo dal valore attuale
    }

void Ball::draw(sf::RenderWindow& window) {
    window.draw(shape_);
}

void Ball::reset() {
    shape_.setPosition(startPosition_);
    
    // Velocità iniziale casuale (sinistra/destra)
    float angle = (rand() % 60 - 30) * 3.14159f / 180.f; // -30° to +30°
    velocity_.x = speed_ * std::cos(angle);
    velocity_.y = speed_ * std::sin(angle);
    
    // Direzione casuale
    if (rand() % 2 == 0) 
        velocity_.x *= -1;
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

const sf::Vector2f Ball::getPosition() const {
    return shape_.getPosition();
}

const sf::Vector2f& Ball::getVelocity() const{
    return velocity_;
}

const sf::FloatRect Ball::getGlobalBounds() const {
    return shape_.getGlobalBounds();
}

void Ball::setVelocity(const sf::Vector2f& velocity){
    velocity_=velocity;
}

void Ball::updateTrail() {
    sf::CircleShape trailDot = shape_;
    trailDot.setRadius(shape_.getRadius() * 0.7f);
    trail_.push_back(trailDot);
    if (trail_.size() > 5) trail_.erase(trail_.begin());
}