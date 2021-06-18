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
        resource::Resource<level::Data> level;

        float dt;
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
                if(first == "level"){   data->level.read(  root + second); continue; }
            }

            fb.close();
        }
    }

    inline void Unload(Data *data, std::string filepath){
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

                if(first == "texture"){ data->texture.unload(root + second); continue; }
                if(first == "font"){    data->font.unload(   root + second); continue; }
            }

            fb.close();
        }
    }

    inline void Run(Data *data, unsigned int width, unsigned int height, const char *title){
        sf::Clock clock;

        data->window.create(sf::VideoMode(sf::VideoMode::getDesktopMode()), title, sf::Style::Default);
        data->window.setVerticalSyncEnabled(true);

        while(data->window.isOpen()){
            clock.restart();
            
            sf::Event event;
            while(data->window.pollEvent(event)){
            // "close requested" event: we close the window
                if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape)){
                    data->window.close();
                }
            }
            data->dt = clock.getElapsedTime().asSeconds();

            data->state.update();

            data->window.clear();
            data->state.render();
            data->window.display();
        }

        data->state.clearStates();
    }
}

#endif // !GE_HPP
