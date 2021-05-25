#include "uibox.hpp"

namespace herbglitch {
    namespace menu {
        UIBox::UIBox(ge::Data *data, sf::Vector2f coords): ge::State(data), buttonNum(3){
            sprites = new sf::Sprite[buttonNum + 1];
            buttons = new Button *[buttonNum];

            setSprites();
            setPosition(coords);
            setButtons();
        }

        UIBox::~UIBox(){
            delete [] sprites;
            for(int i = 0; i < buttonNum; i++){ delete buttons[i]; }
            delete [] buttons;
        }

        void UIBox::update(){
            for(int i = 0; i < buttonNum; i++){ buttons[i]->update(); }
        }

        void UIBox::render(){
            for(int i = 0; i < buttonNum + 1; i++){ data->window.draw(sprites[i]); }
            for(int i = 0; i < buttonNum; i++){ buttons[i]->render(); }
        }

        void UIBox::setSprites(){
            sprites[0].setTexture(data->texture.getResource("gui")[0]);
            for(int i = 1; i < buttonNum; i++){ sprites[i].setTexture(data->texture.getResource("gui")[1]); }
            sprites[buttonNum].setTexture(data->texture.getResource("gui")[2]);

            for(int i = 0; i < buttonNum + 1; i++){ sprites[i].setScale(data->scale, data->scale); }
        }

        void UIBox::setPosition(sf::Vector2f coords){
            sprites[0].setPosition(coords);
            for(int i = 1; i < buttonNum + 1; i++){
                sprites[i].setPosition(sf::Vector2f(coords.x, sprites[i - 1].getGlobalBounds().height + sprites[i - 1].getGlobalBounds().top));
            }
        }

        void UIBox::setButtons(){
            for(int i = 0; i < buttonNum; i++){
                buttons[i] = new Button(data, sf::Vector2f(
                    sprites[i + 1].getGlobalBounds().left + (sprites[i + 1].getGlobalBounds().width * 0.5f),
                    sprites[i + 1].getGlobalBounds().top), i);
            }
        }
    }
}

// for(int i = 0; i < uiBoxSize; i++){ data->window.draw(uiBox[i]); }