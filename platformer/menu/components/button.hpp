#pragma once
#include <ge/ge.hpp>
#include "../../game/game.hpp"

namespace herbglitch {
    namespace menu {
        enum class ButtonState { DEFAULT, HOVER, CLICK };
        class Button : public ge::State {
        public:
            Button(ge::Data *data, sf::Vector2f centerCoords, unsigned int txtIndex);

            void update();
            void render();

            void setPosition(sf::Vector2f coords);

        private:
            void getCollision();
            void setTexture();
            void executeClick();

            unsigned int txtIndex;

            sf::Sprite sprite;
            sf::Sprite text;

            ButtonState state;
            ButtonState lastState;
        };
    }
}