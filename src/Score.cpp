#include "Score.h"

    Score::Score(const sf::Font& font, unsigned int size, const sf::Vector2f& position)
    :value_(0),font_(font){    
        text_.setFont(font_);
        text_.setPosition(position);
        text_.setFillColor(sf::Color::White);
        text_.setCharacterSize(size);
    reset();
}
void Score::increase() {
    ++value_;
    updateText();
}

void Score::reset() {
    value_ = 0;
    updateText();
}

unsigned int Score::getValue() const {
    return value_;
}

void Score::setPosition(const sf::Vector2f& position) {
    text_.setPosition(position);
}

void Score::setColor(const sf::Color& color) {
    text_.setFillColor(color);
}

void Score::draw(sf::RenderWindow& window) const {
    window.draw(text_);
}

void Score::updateText() {
    text_.setString(std::to_string(value_));
    
    // Centra il testo sulla posizione originale
    sf::FloatRect bounds = text_.getLocalBounds();
    //text_.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Score::update(const GameObject& obj){
    increase();
}
void Score::setFont(const sf::Font& font){
    text_.setFont(font);
}