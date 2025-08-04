#include "GameObject.h"

GameObject::GameObject(GameObject* parent=nullptr)
    :parent(parent),isActive(true){}

bool GameObject::checkCollision(const GameObject& other) const {
        return getGlobalBounds().intersects(other.getGlobalBounds());
    }


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


void GameObject::onBoundaryHit(){}