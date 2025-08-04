#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class GameObject {   
private:
    GameObject* parent = nullptr;  // Puntatore al padre (opzionale)    
    bool isActive;
    
protected:
    sf::Transformable transform;  // Gestisce posizione/rotazione/scala
    
    virtual void onBoundaryHit();// Callback per eventi
public:
//Costruttore
    GameObject(GameObject* parent=nullptr);

//Distruttore virtuale
    virtual ~GameObject()=default;

//predisposizione per gestire sincronizzazione transform ed eventuali shape
    virtual void syncTransform() = 0;

// Metodi core
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderTarget& target) const = 0;
    virtual sf::FloatRect getGlobalBounds() const = 0;

// Collisioni
    virtual void handleCollision(GameObject& other) = 0;
    virtual bool checkCollision(const GameObject& other) const;

// Gestione bordi
    virtual void handleBoundaries(const sf::FloatRect& bounds);


// Transform
    virtual void setPosition(const sf::Vector2f& position);
    
    virtual void move(const sf::Vector2f& offset);

    sf::Vector2f getPosition() const ;



};

#endif