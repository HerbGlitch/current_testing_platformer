#pragma once
#include <ge/ge.hpp>
#include "button.hpp"

namespace herbglitch {
    namespace menu {
        class UIBox : public ge::State {
        public:
            UIBox(ge::Data *data, sf::Vector2f coords);
            ~UIBox();

            void update();
            void render();

            void setSprites();
            void setPosition(sf::Vector2f coords);
            void setButtons();

        private:
            sf::Sprite *sprites;
            Button **buttons;
            int buttonNum;
        };
    }
}