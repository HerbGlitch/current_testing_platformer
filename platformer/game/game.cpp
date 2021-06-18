#include "game.hpp"

namespace herbglitch {
    Game::Game(ge::Data *data): ge::State(data){
        map = new game::Map(data, "main_level", sf::Vector2f(0.0, 0.0));
        player = new game::Player(data);
    }

    Game::~Game(){ 
        delete player;
        delete map;
    }

    void Game::update(){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
            data->window.close();
        }

        player->update();
        map->update();
    }

    void Game::render(){
        player->render();
        map->update();
    }
}