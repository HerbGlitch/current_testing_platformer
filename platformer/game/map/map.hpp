#pragma once
#include <ge/ge.hpp>
#include <string>

namespace herbglitch {
    namespace game {
        class Map : public ge::State {
        public:
            Map(ge::Data *data, std::string map, sf::Vector2f coords);
            ~Map();

            void update();
            void render();

            void setPosition(sf::Vector2f coords);

        private:
            ge::level::Data map;
            sf::Vector2f coords;

            sf::Sprite *tiles;
            unsigned int tileSize;
        };
    }
}