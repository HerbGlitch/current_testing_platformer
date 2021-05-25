#include <SFML/Graphics.hpp>

namespace ge {
    namespace animation {
        class Sprite : public sf::Sprite {
        public:
            unsigned int i = 0;
            unsigned int speed = 15;
            unsigned int frame = 0;

            bool isFrame(unsigned int frameSize){
                i++;
                if(i < speed){ return false; }
                i = 0;
                frame = (frame < frameSize - 1)? frame + 1 : 0;
                return true;
            }
        };
    }
}