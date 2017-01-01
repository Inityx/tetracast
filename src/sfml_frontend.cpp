#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "tc/game.hpp"
#include "tc/gamedefs.h"
#include "sfml_aux.hpp"

#define SCALE_FACTOR 50
#define FRAMERATE 30

int main() {
    tc::Game game;
    tc::Game::State state;
    srand(time(NULL));
    
    sf::RenderWindow window(
        sf::VideoMode(
            GAME_WIDTH  * SCALE_FACTOR,
            GAME_HEIGHT * SCALE_FACTOR
        ),
        "SFML Window"
    );
    window.setFramerateLimit(FRAMERATE);
    
    sf::Clock tick_clock;
    sf::Event event;
    struct { int type; int count; } prev_event_meta = { -1, 0 };
    
    draw_dots(window, SCALE_FACTOR);
    window.display(); // + framerate management

    while(window.isOpen()) {
        // frame loop
        while (window.pollEvent(event)) {
            // Process window event queue
            switch(event.type) {
                // Handle event by type
                case sf::Event::Closed:
                    window.close();
                    break;
                
                default:
                    break;
            }
            prev_event_meta.type = event.type;
        }
        
        state = game.try_tick(
            tick_clock.getElapsedTime().asMilliseconds(),
            rand()
        );
        
        switch(state) {
            case tc::Game::NO_ACTION:
                break;
            
            case tc::Game::LOSE:
                puts("HAH, you lose");
                printf("x: %d, y: %d\n", game.get_piece().loc_x(), game.get_piece().loc_y());
                // window.close();
                pause();
                break;
            
            case tc::Game::TICK:
                puts("Tick");
                printf("x: %d, y: %d\n", game.get_piece().loc_x(), game.get_piece().loc_y());
                tick_clock.restart();
                window.clear(sf::Color::Black);
                // TODO: draw content
                draw_dots(window, SCALE_FACTOR);
                draw_blocks(window, SCALE_FACTOR, game);
                break;
        }
        
        window.display(); // + framerate management
    }
    
    return EXIT_SUCCESS;
}
