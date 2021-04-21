/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** NCurses.hpp
*/

#pragma once

#include "IGraphicalLibrary.hpp"
#include <ncurses.h>
#include <map>
#include <functional>
#include <iostream>
#include <fstream>

extern "C" void *entryPoint();
namespace arcade
{
    struct WindowDeleter
    {
        void operator()(WINDOW *win) {
            wborder(win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
            wrefresh(win);
            delwin(win);
        }
    };

    class NCurses : public IGraphicalLibrary
    {
        using draw_function_t = std::function<void(GameObject &)>;

        public:
            NCurses(std::string name);
            ~NCurses(void);
            void init() override;
            void stop() override;
            const std::string &getName() const override;
            void draw(GameObject &entity) override;
            std::vector<Input::Key> get_input(void) override;
            void display(void) override;
            void clear(void) override;
        private:
            std::string name;
            char input;
            std::vector<std::string> grid;
            std::unique_ptr<WINDOW, WindowDeleter> win = std::unique_ptr<WINDOW, WindowDeleter>(nullptr, WindowDeleter());
            std::map<arcade::GameObject::ObjectType, draw_function_t> _draw_func_map;

            void draw_circle(arcade::GameObject &entity);
            void draw_rectangle(arcade::GameObject &entity);
            void draw_line(arcade::GameObject &entity);
            void draw_sprite(arcade::GameObject &entity);
            void draw_text(arcade::GameObject &entity);
    };
}
