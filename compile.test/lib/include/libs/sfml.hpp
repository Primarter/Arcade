/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** sfml.hpp
*/

#pragma once
#include "IGraphicalLibrary.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <functional>

extern "C" void *entryPoint();

namespace arcade
{
    class sfml : public IGraphicalLibrary
    {
        using draw_function_t = std::function<void(GameObject &)>;

        public:
            sfml(std::string name);
            ~sfml();
            void init() override;
            void stop() override;
            const std::string &getName() const override;
            void draw(GameObject &entity) override;
            std::vector<Input::Key> get_input(void) override;
            void display(void) override;
            void clear(void) override;
        private:
            std::string name;

            // sfml
            sf::RenderWindow _window;
            std::vector<Input::Key> _keys;

            std::map<arcade::GameObject::ObjectType, draw_function_t> _draw_func_map;

            void draw_circle(arcade::GameObject &entity);
            void draw_rectangle(arcade::GameObject &entity);
            void draw_line(arcade::GameObject &entity);
            void draw_sprite(arcade::GameObject &entity);
            void draw_text(arcade::GameObject &entity);
    };

}
