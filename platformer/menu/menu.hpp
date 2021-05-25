#pragma once
#include <ge/ge.hpp>
#include "components/uibox.hpp"

namespace herbglitch {
    class Menu : public ge::State {
    public:
        Menu(ge::Data *data);
        ~Menu();

        void update();
        void render();

    private:
        menu::UIBox *uiBox;
    };
}