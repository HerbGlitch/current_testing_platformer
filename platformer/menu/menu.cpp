#include "menu.hpp"

namespace herbglitch {
    Menu::Menu(ge::Data *data): ge::State(data){
        uiBox = new menu::UIBox(data, sf::Vector2f(100.0f, 200.0f));
    }

    Menu::~Menu(){ delete uiBox; }

    void Menu::update(){
        uiBox->update();
    }

    void Menu::render(){
        uiBox->render();
    }
}