#include <SFML/Graphics.hpp>
#include "../tools/tools.hpp"

namespace ge {
    struct Data;

    namespace platformer {
        class Entity {
        public:
            Entity(Data *data): data(data), collision(false), g(1.0f), yy(0.0f){}
            virtual ~Entity(){}

            virtual void update() = 0;
            virtual void render() = 0;

            void gravity(){
                if(collision){ return; }

                yy += g;
                entity.move(0.0f, yy);
            }

            void setColision(bool collision){
                if(collision){ yy = 0; }
                this->collision = collision;
            }

        protected:
            Data *data;

            animation::Sprite entity;

            float yy, g;
            bool collision;

        };
    }
}