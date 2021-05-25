#include "button.hpp"

namespace herbglitch {
    namespace menu {
        Button::Button(ge::Data *data, sf::Vector2f centerCoords, unsigned int txtIndex): ge::State(data), txtIndex(txtIndex){
            state = ButtonState::DEFAULT;
            lastState = ButtonState::DEFAULT;

            sprite.setTexture(data->texture.getResource("button medium")[0]);
            text.setTexture(data->texture.getResource("button txt")[txtIndex]);

            sprite.setOrigin(sprite.getGlobalBounds().width * 0.5f, sprite.getGlobalBounds().height * 0.5f);
            text.setOrigin(text.getGlobalBounds().width * 0.5f, text.getGlobalBounds().height * 0.5f);

            sprite.setScale(data->scale, data->scale);
            text.setScale(data->scale, data->scale);

            sprite.setPosition(centerCoords);
            text.setPosition(centerCoords);
        }

        void Button::update(){
            getCollision();
            setTexture();
            executeClick();
        }

        void Button::render(){
            data->window.draw(sprite);
            data->window.draw(text);
        }

        void Button::getCollision(){
            if(sprite.getGlobalBounds().contains((sf::Vector2f) sf::Mouse::getPosition(data->window))){
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){ state = ButtonState::CLICK; return; }
                state = ButtonState::HOVER; return;
            }
            state = ButtonState::DEFAULT;
        }

        void Button::setTexture(){
            if(lastState == state){ return; }
            lastState = state;
            switch(state){
                case ButtonState::HOVER:
                    sprite.setTexture(data->texture.getResource("button medium")[1]);
                    break;
                case ButtonState::CLICK:
                    sprite.setTexture(data->texture.getResource("button medium")[2]);
                    break;
                default:
                    sprite.setTexture(data->texture.getResource("button medium")[0]);
                    break;
            }
        }

        void Button::executeClick(){
            if(state != ButtonState::CLICK){ return; }
            if(txtIndex == 0){ data->state.addState(new Game(data), true); }
            if(txtIndex == 1){  }
            if(txtIndex == 2){ data->window.close(); }
        }

        void Button::setPosition(sf::Vector2f coords){

        }
    }
}