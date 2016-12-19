#include <SFML/Graphics.hpp>
#include "tc/game.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");
    
    tc::Game game;
    
    while(window.isOpen()) {
        window.clear();
        window.display();
        
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed) window.close();
    }
    
    return EXIT_SUCCESS;
}
