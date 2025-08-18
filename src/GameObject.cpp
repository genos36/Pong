#include "GameObject.h"




void GameObject::onBoundaryHit(const BoundaryCheck&){}

bool GameObject::shouldCollide(const GameObject& other)const{return true;}


const sf::Transformable& GameObject::getTransform()const{
    return transform;
}

GameObject::GameObject()
    :isActive(true),transform(){}

bool GameObject::checkCollision(const GameObject& other) const {
    // 1. Perform AABB check (common for all objects)
    bool colliding = getGlobalBounds().intersects(other.getGlobalBounds());
    
    // 2. Let subclass decide if this counts as collision
    if (colliding) {
        return shouldCollide(other); // Virtual method
    }
    return false;
    }




/*
void GameObject::handleBoundaries(const sf::FloatRect& bounds) {

    auto objBounds=getGlobalBounds();
        if (objBounds.left < bounds.left) {
            setPosition(sf::Vector2f(bounds.left, getPosition().y));
            onBoundaryHit();
        }

        if (objBounds.left+objBounds.width> bounds.left+bounds.width) {
            setPosition(sf::Vector2f(bounds.left+bounds.width- objBounds.width, getPosition().y));
            onBoundaryHit();
        }
        
        if (objBounds.top< bounds.top) {
            setPosition(sf::Vector2f( getPosition().x,bounds.top));
            onBoundaryHit();
        }
        
        if (objBounds.top+objBounds.height> bounds.top+bounds.height) {
            setPosition(sf::Vector2f( getPosition().x,bounds.top+bounds.height- objBounds.height));
            onBoundaryHit();
        }

    }

*/

BoundaryCheck GameObject::checkBoundaries(const sf::FloatRect& bounds) const {
    auto objBounds = getGlobalBounds();
    if (objBounds.left < bounds.left) return BoundaryCheck::LEFT;
    if (objBounds.left + objBounds.width > bounds.left + bounds.width) return BoundaryCheck::RIGHT;
    if (objBounds.top< bounds.top) return BoundaryCheck::TOP;
    if (objBounds.top+objBounds.height> bounds.top+bounds.height) return BoundaryCheck::BOTTOM;

    return BoundaryCheck::NONE;
}




void GameObject::setPosition(const  sf::Vector2f& position) { 
    transform.setPosition(position); 
    syncTransform();
    }

void GameObject::move(const  sf::Vector2f& offset) { 
    transform.move(offset); 
    syncTransform();
    }


sf::Vector2f GameObject::getPosition() const { 
        return transform.getPosition(); 
    }




void GameObject::addObserver(Observer * observer){
    observers.push_back(observer);
}

void GameObject::notifyAll(){
    for(auto it=observers.begin();it!=observers.end();++it){
        (*it)->update(*this);
    }
}




BoundaryCheck GameObject::getCollisionSide(const GameObject& paddle) const {
    sf::FloatRect ballBounds = getGlobalBounds();
    sf::FloatRect paddleBounds = paddle.getGlobalBounds();
    
    // Calculate overlap on each side
    float overlapLeft = ballBounds.left + ballBounds.width - paddleBounds.left;
    float overlapRight = paddleBounds.left + paddleBounds.width - ballBounds.left;
    float overlapTop = ballBounds.top + ballBounds.height - paddleBounds.top;
    float overlapBottom = paddleBounds.top + paddleBounds.height - ballBounds.top;
    
    // Find smallest overlap (side with deepest penetration)
    bool fromLeft = overlapLeft < overlapRight;
    bool fromTop = overlapTop < overlapBottom;
    float minOverlapX = fromLeft ? overlapLeft : overlapRight;
    float minOverlapY = fromTop ? overlapTop : overlapBottom;
    
    if (minOverlapX < minOverlapY) {
        return fromLeft ? BoundaryCheck::LEFT : BoundaryCheck::RIGHT;
    } else {
        return fromTop ? BoundaryCheck::TOP : BoundaryCheck::BOTTOM;
    }
}