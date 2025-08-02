#include "Paddle.h"

Paddle::Paddle(const sf::Vector2f& size, const sf::Vector2f& position) 
    : shape_(size), speed_(500.f) {
    shape_.setPosition(position);
    shape_.setFillColor(sf::Color::White);
    shape_.setOrigin(size.x / 2.f, size.y / 2.f); // Centro come origine
}

void Paddle::update(float deltaTime) {
    shape_.move(velocity_ * deltaTime); //aggiorna la posizione partendo dal valore attuale
    }

void Paddle::draw(sf::RenderWindow& window)const{
    window.draw(shape_);
}

void Paddle::moveUp() {
    velocity_.y = -speed_;
}

void Paddle::moveDown() {
    velocity_.y = speed_;
}

void Paddle::stop() {
    velocity_.y = 0.f;
}

void Paddle::setSpeed(float speed) {
    speed_ = speed;
}

void Paddle::setFillColor(const sf::Color& color) {
    shape_.setFillColor(color);
}

void Paddle::setPosition(float x, float y){
    shape_.setPosition(sf::Vector2f(x,y));
}

sf::Vector2f Paddle::getPosition() const {
    return shape_.getPosition();
}

sf::FloatRect Paddle::getGlobalBounds() const {
    return shape_.getGlobalBounds();
}

sf::Vector2f Paddle::getSize() const {
    return shape_.getSize();
}

