#include <ge/ge.hpp>
#include "menu/menu.hpp"
#include <stdio.h>

int main(){
    ge::Data *data = new ge::Data();

    ge::Load(data, "src/res/settings.config");
    data->state.addState(new herbglitch::Menu(data));

    ge::Run(data, 1920, 1080, "Platformer");
    return 0;
}