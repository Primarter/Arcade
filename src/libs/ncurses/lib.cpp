/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** lib.cpp
*/

#include "libs/NCurses.hpp"
#include <iostream>

extern "C" void *entryPoint()
{
    std::cout << "[NCurses] NCurses load" << std::endl;
    return new arcade::NCurses("NCurses");
}

// void set_color(std::unique_ptr<WINDOW, arcade::WindowDeleter> &win, arcade::Color &color, int pair)
// {
//     init_color(COLOR_RED, (color.r * 1000) / 255, (color.g * 1000) / 255, (color.b * 1000) / 255);
//     init_pair(1, COLOR_RED, COLOR_RED);
//     init_pair(2, COLOR_RED, COLOR_BLACK);
//     wattron(win.get(), COLOR_PAIR(pair));
// }

// void unset_color(std::unique_ptr<WINDOW, arcade::WindowDeleter> &win, int pair)
// {
//     wattroff(win.get(), COLOR_PAIR(pair));
// }

namespace arcade {

    static std::map<char, Input::Key> keymap = {
        {'a', Input::Key::A},
        {'b', Input::Key::B},
        {'c', Input::Key::C},
        {'d', Input::Key::D},
        {'e', Input::Key::E},
        {'f', Input::Key::F},
        {'g', Input::Key::G},
        {'h', Input::Key::H},
        {'i', Input::Key::I},
        {'j', Input::Key::J},
        {'k', Input::Key::K},
        {'l', Input::Key::L},
        {'m', Input::Key::M},
        {'n', Input::Key::N},
        {'o', Input::Key::O},
        {'p', Input::Key::P},
        {'q', Input::Key::Q},
        {'r', Input::Key::R},
        {'s', Input::Key::S},
        {'t', Input::Key::T},
        {'u', Input::Key::U},
        {'v', Input::Key::V},
        {'w', Input::Key::W},
        {'x', Input::Key::X},
        {'y', Input::Key::Y},
        {'z', Input::Key::Z},
        {-15456, Input::Key::Num0},
        {'&', Input::Key::Num1},
        {-15447, Input::Key::Num2},
        {'\"', Input::Key::Num3},
        {'\'', Input::Key::Num4},
        {'(', Input::Key::Num5},
        {'-', Input::Key::Num6},
        {-15448, Input::Key::Num7},
        {'_', Input::Key::Num8},
        {-15449, Input::Key::Num9},
        {27, Input::Key::Escape},
        {' ', Input::Key::Space},
        {'\n', Input::Key::Enter},
        {'\b', Input::Key::Backspace},
        {'\t', Input::Key::Tab},
        {KEY_UP, Input::Key::Up},
        {KEY_DOWN, Input::Key::Down},
        {KEY_LEFT, Input::Key::Left},
        {KEY_RIGHT, Input::Key::Right},
    };

    NCurses::NCurses(std::string name):
        name(name),
        _draw_func_map({
            { GameObject::ObjectType::CIRCLE, [this](GameObject &obj) { this->draw_circle(obj); } },
            { GameObject::ObjectType::RECTANGLE, [this](GameObject &obj) { this->draw_rectangle(obj); } },
            { GameObject::ObjectType::LINE, [this](GameObject &obj) { this->draw_line(obj); } },
            { GameObject::ObjectType::SPRITE, [this](GameObject &obj) { this->draw_sprite(obj); } },
            { GameObject::ObjectType::TEXT, [this](GameObject &obj) { this->draw_text(obj); } }
        })
    {
        std::cout << "[NCurses] Loading lib" << std::endl;
    }

    NCurses::~NCurses(void)
    {
        std::cout << "[NCurses] Destroying lib" << std::endl;
    }

    void NCurses::init(void)
    {
        std::cout << "[NCurses] NCurses init" << std::endl;
        initscr();
        start_color();
        keypad(stdscr, true);
        noecho();
        cbreak();
        nodelay(stdscr, true);
        curs_set(0);

        this->win.reset(newwin(72, 72, 0, 0));
        box(this->win.get(), 0, 0);
    }

    void NCurses::stop(void)
    {
        this->win.reset();
        if (endwin() == ERR)
            throw std::runtime_error("[NCurses] endwin returned an error in ncurses stop method");
        std::cout << "[NCurses] NCurses stop" << std::endl;
    }

    void NCurses::draw(GameObject &entity)
    {
        _draw_func_map[entity.type](entity);
    }

    std::vector<Input::Key> NCurses::get_input(void)
    {
        this->input = getch();
        if (this->input == KEY_F(1)) {
            return {Input::Key::Closed};
        }
        return {keymap[this->input]};
    }

    void NCurses::display(void)
    {
        if (LINES < 72 || COLS < 72) {
            wclear(stdscr);
            printw("Window is too small!\nResize to at least 50*50 please.\n");
            refresh();
            return;
        }
        box(this->win.get(), 0, 0);
        wrefresh(this->win.get());
    }

    void NCurses::clear(void)
    {
        werase(this->win.get());
    }

    const std::string &NCurses::getName() const
    {
        return this->name;
    }
}
