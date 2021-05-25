#pragma once
#include <ge/ge.hpp>

namespace herbglitch {
    class Player : public ge::platformer::Entity {
    public:
        Player(ge::Data *data);
        ~Player();

        void update();
        void render();

    private:
    };
}