#include "game.hpp"

namespace herbglitch {
    Game::Game(ge::Data *data): ge::State(data){
        printf("HERE?");
        player = new Player(data);
    }

    Game::~Game(){ 
        delete player;
    }

    void Game::update(){
        player->update();
    }

    void Game::render(){
        player->render();
    }
}