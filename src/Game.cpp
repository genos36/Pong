#include "Game.h"
#include <iostream>



const sf::Vector2f Game::paddleSize_(){
    return sf::Vector2f(20.f, 100.f);
    }
const float Game::aiDifficulty_(){
    return 0.8f; // 0-1
}



Game::Game(int width, int height, const std::string& title)
    : window_(sf::VideoMode(width, height), title),
      playerPaddle_(paddleSize_(), sf::Vector2f(50.f, height/2.f)),
      aiPaddle_(paddleSize_(), sf::Vector2f(width - 50.f, height/2.f)),
      ball_(10.f, sf::Vector2f(width/2.f, height/2.f)),
      playerScore_(font_, 48, sf::Vector2f(width/4.f, 30.f)),
      aiScore_(font_, 48, sf::Vector2f(3*width/4.f, 30.f)){
    
    // Setup finestra
    window_.setVerticalSyncEnabled(true);
    
    // Caricamento font
    if (!font_.loadFromFile("../assets/Roboto_Condensed-BlackItalic.ttf")) {
        std::cerr << "Failed to load font! Using default." << std::endl;
        // Fallback a font generato
        font_.loadFromMemory("../assets/Roboto_Condensed-BlackItalic.ttf", 30);
    }
    

    // Personalizzazione
    playerPaddle_.setFillColor(sf::Color::Blue);
    aiPaddle_.setFillColor(sf::Color::Red);
    ball_.setFillColor(sf::Color::White);
}

void Game::run() {
    sf::Clock clock;
    
    while (window_.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window_.close();
        }
        
        // Tasto ESC per uscire
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            window_.close();
        }
    }
    
    // Input giocatore
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        playerPaddle_.moveUp();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        playerPaddle_.moveDown();
    } else {
        playerPaddle_.stop();
    }
}

void Game::update(float deltaTime) {
    // Muovi paddle e palla
    playerPaddle_.update(deltaTime);
    aiPaddle_.update(deltaTime);
    ball_.update(deltaTime);
    
    // AI semplice
    float targetY = ball_.getPosition().y;
    if (ball_.getVelocity().x > 0) {  // Palla verso AI
        if (aiPaddle_.getPosition().y < targetY - 20.f) {
            aiPaddle_.moveDown();
        } else if (aiPaddle_.getPosition().y > targetY + 20.f) {
            aiPaddle_.moveUp();
        } else {
            aiPaddle_.stop();
        }
    }
    
    // Collisioni paddle-palla
    if (ball_.getGlobalBounds().intersects(playerPaddle_.getGlobalBounds())) {
        ball_.bounceX();
        // Angolo in base alla posizione di impatto
        float relativeIntersect = (playerPaddle_.getPosition().y - ball_.getPosition().y) / paddleSize_().y;
        ball_.setVelocity(sf::Vector2f(400.f, -300.f * relativeIntersect));
    }
    
    if (ball_.getGlobalBounds().intersects(aiPaddle_.getGlobalBounds())) {
        ball_.bounceX();
        float relativeIntersect = (aiPaddle_.getPosition().y - ball_.getPosition().y) / paddleSize_().y;
        ball_.setVelocity(sf::Vector2f(-400.f, -300.f * relativeIntersect));
    }
    
    // Collisioni con bordi (top/bottom)
    if (ball_.getPosition().y <= 0 || ball_.getPosition().y >= window_.getSize().y) {
        ball_.bounceY();
    }
    
    // Punto segnato
    if (ball_.getPosition().x < 0) {
        aiScore_.increase();
        resetRound();
    } else if (ball_.getPosition().x > window_.getSize().x) {
        playerScore_.increase();
        resetRound();
    }
    
    // Limiti paddle
    sf::Vector2f playerPos = playerPaddle_.getPosition();
    if (playerPos.y < paddleSize_().y/2) playerPaddle_.setPosition(playerPos.x, paddleSize_().y/2);
    if (playerPos.y > window_.getSize().y - paddleSize_().y/2) {
        playerPaddle_.setPosition(playerPos.x, window_.getSize().y - paddleSize_().y/2);
    }
}

void Game::render() {
    window_.clear(sf::Color::Black);
    
    // Linea centrale
    sf::RectangleShape line(sf::Vector2f(2.f, window_.getSize().y));
    line.setFillColor(sf::Color(255, 255, 255, 50));
    line.setPosition(window_.getSize().x/2.f, 0);
    window_.draw(line);
    
    // Disegna oggetti
    playerPaddle_.draw(window_);
    aiPaddle_.draw(window_);
    ball_.draw(window_);
    playerScore_.draw(window_);
    aiScore_.draw(window_);
    
    window_.display();
}

void Game::resetRound() {
    ball_.reset();
    playerPaddle_.setPosition(50.f, window_.getSize().y/2.f);
    aiPaddle_.setPosition(window_.getSize().x - 50.f, window_.getSize().y/2.f);
}