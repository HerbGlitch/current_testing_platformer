#pragma once
#include <ge/ge.hpp>
#include <iostream>

namespace herbglitch {
    namespace game {
        class Player : public ge::platformer::Entity {
        public:
            Player(ge::Data *data);
            ~Player();

            void update();
            void render();

        private:
        };
    }
}