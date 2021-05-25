#ifndef GE_HPP
#define GE_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "level/level.hpp"
#include "platformer/entity.hpp"
#include "resource/resource.hpp"
#include "resource/texture.hpp"
#include "state/state.hpp"
#include "tools/tools.hpp"

namespace ge {
    struct Data {
        sf::RenderWindow window;
        state::Handler state;
        resource::Texture texture;
        resource::Resource<sf::Font> font;
        float scale = 8.0f;
    };

    inline void Load(Data *data, std::string filepath){
        std::filebuf fb;
        if(fb.open(filepath, std::ios::in)){
            std::istream is(&fb);
            while(is){
                std::string temp;
                std::getline(is, temp);
                if(temp.find(':') == std::string::npos){ continue; }

                std::string first = temp.substr(0, temp.find(':'));
                std::string second = temp.substr(temp.find(':') + 2, temp.size() - 1);
                std::string root = filepath.substr(0, filepath.find_last_of("/") + 1);

                if(first == "texture"){ data->texture.read(root + second); continue; }
                if(first == "font"){    data->font.read(   root + second); continue; }
            }

            fb.close();
        }
    }

    inline void Input(Data *data){
        
    }

    inline void Run(Data *data, unsigned int width, unsigned int height, const char *title, float UPS = 1.0f / 60.0f){
        sf::Clock clock;

        data->window.create(sf::VideoMode(sf::VideoMode::getDesktopMode()), title, sf::Style::Default);

        float dt = clock.getElapsedTime().asSeconds();
        float new_dt = 0.0f, elapsed = 0.0f;

        while(data->window.isOpen()){
            new_dt = clock.getElapsedTime().asSeconds();
            elapsed += new_dt - dt;
            dt = new_dt;

            if(elapsed >= UPS){
                data->state.update();
                elapsed -= UPS;
            }

            //render
            data->window.clear();
            data->state.render();
            data->window.display();
        }
    }
}

#endif // !GE_HPP
