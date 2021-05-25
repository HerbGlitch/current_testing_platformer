#include "player.hpp"
#include <stdio.h>

namespace herbglitch {
    Player::Player(ge::Data *data): ge::platformer::Entity(data){
        entity.setTexture(data->texture.getResource("buck idle")[0]);
        entity.setScale(data->scale, data->scale);
    }

    Player::~Player(){}

    void Player::update(){
        gravity();

        setColision(entity.getGlobalBounds().top + entity.getGlobalBounds().height >= data->window.getSize().y);

        if(entity.isFrame(data->texture.getResource("buck idle").getSize())){
            entity.setTexture(data->texture.getResource("buck idle")[entity.frame]);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            yy = -20;
            setColision(false);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){ entity.move(4.0f, 0.0f); }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){ entity.move(-4.0f, 0.0f); }
    }

    void Player::render(){
        data->window.draw(entity);
    }
}