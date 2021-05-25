#pragma once
#include <ge/ge.hpp>
#include <stdio.h>
#include "player/player.hpp"

namespace herbglitch {
    class Game : public ge::State {
    public:
        Game(ge::Data *data);
        ~Game();

        void update();
        void render();

    private:
        Player *player;
    };
}