/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** sdl2.hpp
*/

#pragma once
#include "IGraphicalLibrary.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_ttf.h>
#include <map>
#include <functional>

extern "C" void *entryPoint();
namespace arcade
{
    class sdl2 : public IGraphicalLibrary
    {
        using draw_function_t = std::function<void(GameObject &)>;

        public:
            sdl2(std::string name);
            ~sdl2();
            void init() override;
            void stop() override;
            const std::string &getName() const override;
            void draw(GameObject &entity) override;
            std::vector<Input::Key> get_input(void) override;
            void display(void) override;
            void clear(void) override;
        private:
            std::string name;

            std::vector<Input::Key> _keys;
            SDL_Renderer *_renderer;
            SDL_Window *_window;

            std::map<arcade::GameObject::ObjectType, draw_function_t> _draw_func_map;

            void draw_circle(arcade::GameObject &entity);
            void draw_rectangle(arcade::GameObject &entity);
            void draw_line(arcade::GameObject &entity);
            void draw_sprite(arcade::GameObject &entity);
            void draw_text(arcade::GameObject &entity);
    };
}
