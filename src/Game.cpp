#include "Game.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Game.h"
#include <iostream>
#include <memory>

using std::cout;
using std::endl;

Game::Game(int width, int height, const std::string& title)
    : window_(sf::VideoMode(width, height), title),
      playerPaddle_(sf::Vector2f(PADDLE_SIZE_X,PADDLE_SIZE_Y),sf::Vector2f(PADDLE_START_POS_X,PADDLE_START_POS_Y)),
      aiPaddle_(sf::Vector2f(PADDLE_SIZE_X,PADDLE_SIZE_Y),sf::Vector2f(abs(PADDLE_START_POS_X-width),PADDLE_START_POS_Y)),
      ball_(BALL_RADIUS, sf::Vector2f(width/2.f, height/2.f)),
      playerScore_(font_, 48, sf::Vector2f(width/4.f, 30.f)),
      aiScore_(font_, 48, sf::Vector2f(3*width/4.f, 30.f)),
      gameArea_(0.f, 0.f, width, height){
    

    cout<<"siamo nel costruttore di game"<<endl;   
    initializeWindow();
    initializeFont();
    initializeGameObjects();
    cout<<"siamo fuori dal costruttore di game"<<endl;   
}

void Game::initializeWindow() {
    window_.setVerticalSyncEnabled(true);
    // Add window settings like framerate limit if needed
}

void Game::initializeFont() {
    if (!font_.loadFromFile("assets/Roboto_Condensed-BlackItalic.ttf")) {
        std::cerr << "Failed to load font! Using default." << std::endl;
        // Consider a fallback system font
    }
    playerScore_.setFont(font_);
    aiScore_.setFont(font_);
}

void Game::initializeGameObjects() {
    playerPaddle_.setFillColor(sf::Color::Blue);
    aiPaddle_.setFillColor(sf::Color::Red);
    ball_.setFillColor(sf::Color::White);
    ball_.reset();
    
    // Controller setup
    playerPaddle_.setController(std::make_unique<HumanPlayer>(sf::Keyboard::W, sf::Keyboard::S));
    aiPaddle_.setController(std::make_unique<AIPlayer>(&ball_));
    playerPaddle_.addObserver(&playerScore_);
    aiPaddle_.addObserver(&aiScore_);
}


void Game::run() {
    sf::Clock clock;


// cout<<"entrando nel game loop"<<endl;
    while (window_.isOpen()) {
       float deltaTime=clock.restart().asSeconds();
        // cout<<"process event"<<endl;
        processEvents();
     
        // Fixed timestep for stable physicsw

// cout<<"update "<<deltaTime<<endl;
            update(deltaTime);
// cout<<"render"<<endl;    
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
    

}

void Game::update(float deltaTime) {
    // Muovi paddle e palla
    ball_.update(deltaTime);    
    ball_.handleBoundaries(ball_.checkBoundaries(gameArea_));    
    ball_.handleCollision(playerPaddle_);
    ball_.handleCollision(aiPaddle_);
    
    playerPaddle_.update(deltaTime);
    playerPaddle_.handleBoundaries(playerPaddle_.checkBoundaries(gameArea_));
    aiPaddle_.update(deltaTime);
    aiPaddle_.handleBoundaries(aiPaddle_.checkBoundaries(gameArea_));

    // Scoring logic
    switch(ball_.checkBoundaries(gameArea_)){
        case BoundaryCheck::RIGHT :
        playerScore_.increase();
        resetRound();
        break;
        case BoundaryCheck::LEFT :
        aiScore_.increase();
        resetRound();
        break;
    }


    


}

void Game::resetRound() {
    ball_.reset();
    playerPaddle_.reset();
    aiPaddle_.reset();
}



void Game::render() {
    window_.clear();
    

    
    // Disegna oggetti
    playerPaddle_.draw(window_);
    aiPaddle_.draw(window_);
    ball_.draw(window_);
    playerScore_.draw(window_);
    aiScore_.draw(window_);
    
    window_.display();
}


    unsigned int Game::width() const{
        return window_.getSize().x;
    }
    unsigned int Game::height() const{
        return window_.getSize().y;
    }
