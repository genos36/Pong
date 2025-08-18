#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Observer.h"
class Observer;

enum BoundaryCheck{
    NONE=0,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};


class GameObject {   
private:
    bool isActive;
    sf::Transformable transform;  // Gestisce posizione/rotazione/scala
    std::vector<Observer*> observers;
    
protected:
    
    virtual void onBoundaryHit(const BoundaryCheck&);// Callback per eventi
    const sf::Transformable& getTransform() const;
    virtual sf::FloatRect getGlobalBounds() const = 0;
    virtual void syncTransform() = 0;
    virtual bool shouldCollide(const GameObject& other)const;
public:
//Costruttore
    GameObject();

//Distruttore virtuale
    virtual ~GameObject()=default;

//predisposizione per gestire sincronizzazione transform ed eventuali shape



// Metodi core
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderTarget& target) const = 0;

// Collisioni
    bool checkCollision(const GameObject& other) const;
    virtual void handleCollision(GameObject& other) = 0;

// Gestione bordi


    BoundaryCheck checkBoundaries(const sf::FloatRect& bounds)const;
    virtual void handleBoundaries(const BoundaryCheck& bound)=0;


// Transform
    void setPosition(const sf::Vector2f& position);//set position and sync
    
    void move(const sf::Vector2f& offset);//move position and sync

    sf::Vector2f getPosition() const ;

    void addObserver(Observer *);
    void notifyAll();

    BoundaryCheck getCollisionSide(const GameObject& paddle)const ;
};

#endif