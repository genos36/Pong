#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Score.h"
#include "Paddle.h"
#include "Game.h"
#include <iostream>
/*
int main()
{
    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bouncing Ball");

    // Create the ball
    sf::CircleShape ball(20.f);
    ball.setFillColor(sf::Color::Green);
    
    // Initial position (center of the window)
    sf::Vector2f position(400.f, 300.f);
    ball.setPosition(position);
    
    // Initial velocity (pixels per frame)
    sf::Vector2f velocity(1.f, 1.f);

    // Main game loop
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update ball position
        position += velocity;
        ball.setPosition(position);

        // Check for collisions with window borders
        if (position.x <= 0 || position.x >= window.getSize().x - ball.getRadius()*2)
        {
            velocity.x = -velocity.x; // Reverse horizontal direction
        }
        if (position.y <= 0 || position.y >= window.getSize().y - ball.getRadius()*2)
        {
            velocity.y = -velocity.y; // Reverse vertical direction
        }

        // Clear, draw, display
        window.clear();
        window.draw(ball);
        window.display();
    }

    return 0;
}

*/

int main(){
    std::cout<<"inizio"<<std::endl;   
    Game game=Game(800,500,"ProvaGame");
    game.run();


    return 0;
}

int main3(){

    const int WIDTH = 800;
    const int HEIGHT = 600;
    const int HUD_HEIGHT = 50; // Altezza area contatore
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Pong con HUD");
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf")) {
        return EXIT_FAILURE;
    }
    Score bounceCounter(font,HUD_HEIGHT,sf::Vector2f(10,10));
    Ball ball (15.f,sf::Vector2f(WIDTH/2, HUD_HEIGHT + 50));
    ball.setFillColor(sf::Color::White);
    ball.reset();
    ball.addObserver(&bounceCounter);
    sf::FloatRect gameArea(0, HUD_HEIGHT, WIDTH, HEIGHT - HUD_HEIGHT);




    Paddle paddle=Paddle(sf::Vector2f(500,40),sf::Vector2f(100,300));
    paddle.stop();
    float deltaTime=clock.restart().asSeconds();
    while(window.isOpen()){
        //deltaTime=clock.restart().asSeconds();
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed) window.close();
        }

    paddle.update(deltaTime);
    paddle.handleBoundaries(paddle.checkBoundaries(gameArea));

    ball.update(deltaTime);
    ball.handleBoundaries(ball.checkBoundaries(gameArea));

    ball.handleCollision(paddle);


        window.clear();
        ball.draw(window);
        paddle.draw(window);
        bounceCounter.draw(window);
        window.display();
    }
    window.close();
    return 0;
}
int main1(){

    sf::RenderWindow window(sf::VideoMode(800, 600), "Bouncing Ball");

    Ball ball=Ball(20.f,sf::Vector2f(window.getSize().x/2.f,window.getSize().y/2.f));
/*
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
                
        }
        window.clear();
        ball.draw(window);
        window.display();
        // Update ball position
    }
*/



    // Main game loop
    
    sf::Clock clock;
    sf::FloatRect gameZone(0,0,800,500);

    while (window.isOpen())
    {
            float deltaTime  = clock.restart().asSeconds();
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update ball position

        ball.update(deltaTime);
 
        
        auto position=ball.getPosition();
        // Check for collisions with window borders
        if (position.x <= 0 || position.x >= window.getSize().x - ball.getRadius()*2)
        {
           ball.bounceX(); // Reverse horizontal direction
           ball.notifyAll();
        }
        if (position.y <= 0 || position.y >= window.getSize().y - ball.getRadius()*2)
        {
            ball.bounceY(); // Reverse vertical direction
            ball.notifyAll();
        }

        window.clear();
        ball.draw(window);
        window.display();
    }



    return 0;
}


#include <sstream>

int main2() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bouncing Ball with Counter");
    
    // Font
    sf::Font font;
// Prova diversi font comuni su Ubuntu
if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf") &&  // Font comune
    !font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf") &&   // Font predefinito Ubuntu
    !font.loadFromFile("/usr/share/fonts/truetype/freefont/FreeSans.ttf")) { // Font libero
    std::cerr << "Errore: Impossibile caricare alcun font!" << std::endl;
    return EXIT_FAILURE;
}

    // Testo
    sf::Text bounceText;
    bounceText.setFont(font);
    bounceText.setCharacterSize(24);
    bounceText.setFillColor(sf::Color::White);
    bounceText.setPosition(10, 10);

    // Ball setup...
    sf::CircleShape ball(20.f);
    ball.setFillColor(sf::Color::Green);
    sf::Vector2f position(400.f, 300.f);
    sf::Vector2f velocity(5.f, 5.f);
    int bounceCount = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        position += velocity;
        ball.setPosition(position);

        // Collision detection
        bool bounced = false;
        if (position.x <= 0 || position.x >= window.getSize().x - ball.getRadius()*2) {
            velocity.x = -velocity.x;
            bounced = true;
        }
        if (position.y <= 0 || position.y >= window.getSize().y - ball.getRadius()*2) {
            velocity.y = -velocity.y;
            bounced = true;
        }

        if (bounced) {
            bounceCount++;
        }

        // Update text
        std::ostringstream ss;
        ss << "Rimbalzi: " << bounceCount;
        bounceText.setString(ss.str());

        window.clear();
        window.draw(ball);
        window.draw(bounceText);
        window.display();
    }

    return 0;
}