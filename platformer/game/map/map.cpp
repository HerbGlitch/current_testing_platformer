#include "map.hpp"

namespace herbglitch {
    namespace game {
        Map::Map(ge::Data *data, std::string map, sf::Vector2f coords): State(data), map(data->level.getResource(map)[0]), coords(coords){
            tileSize = this->map.width() * this->map.height();
            tiles = new sf::Sprite[tileSize];

            for(unsigned int y = 0; y < this->map.height(); y++){
                for(unsigned int x = 0; x < this->map.width(); x++){
                    sf::Sprite *temp = &tiles[(y * this->map.width()) + x];
                    temp->setTexture(data->texture.getResource("buck idle")[0]);
                    // temp->setTexture(data->texture.getResource(this->map[(y * this->map.width()) + x])[0]);
            //         tiles->setPosition(sf::Vector2f(x * temp->getGlobalBounds().width, y * temp->getGlobalBounds().height));
                    tiles->setPosition(sf::Vector2f(10.0f, 10.0f));
                }
            }
        }

        Map::~Map(){
            delete [] tiles;
        }

        void Map::update(){
        }

        void Map::render(){
            for(unsigned int i = 0; i < tileSize; i++){ data->window.draw(tiles[i]); }
        }

        void Map::setPosition(sf::Vector2f coords){
            
        }
    }
}