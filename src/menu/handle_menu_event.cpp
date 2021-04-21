/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** handle_menu_event.cpp
*/

#include "menu/Menu.hpp"

namespace arcade
{
    void Menu::handle_fields(sf::Event event)
    {
        if (this->name_field.contains(
        sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
            this->typing = true;
            this->name_field.set_active(true);
        } else {
            this->name_field.set_active(false);
            if (this->name_field.get_string().empty())
                this->set_name("Guest");
        }
    }

    void Menu::handle_click_event(sf::Event event)
    {
        this->handle_fields(event);
        if (libs_table.contains(
        sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
            int new_idx = (int)((event.mouseButton.y - libs_table.get_position().y)/50 + (-libs_table.get_offset())/50);
            curr_lib = new_idx >= (int)(this->libs.size()) ? curr_lib : new_idx;
            this->input = Input::SET_LIB;
        } else if (games_table.contains(
        sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
            int new_idx = (int)((event.mouseButton.y - games_table.get_position().y)/50 + (-games_table.get_offset())/50);
            curr_game = new_idx >= (int)(this->games.size()) ? curr_game : new_idx;
            this->input = Input::SET_GAME;
        } else if (this->def_lib_line.contains(
        sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
            curr_lib = -1;
            this->input = Input::SET_LIB;
        } else if (this->play_btn.get_active() && this->play_btn.contains(
        sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
            this->input = Input::PLAY;
        }
    }

    void Menu::handle_scroll_event(sf::Event event)
    {
        if (this->libs_table.contains(
        sf::Vector2f(event.mouseWheel.x, event.mouseWheel.y))) {
            this->libs_table.add_offset(event.mouseWheel.delta);
        } else if (this->games_table.contains(
        sf::Vector2f(event.mouseWheel.x, event.mouseWheel.y))) {
            this->games_table.add_offset(event.mouseWheel.delta);
        }
    }

    void Menu::handle_keyboard(sf::Event event)
    {
        if (event.key.code == sf::Keyboard::Z) {
            if (this->curr_lib - 1 >= -1) {
                this->curr_lib -= 1;
                this->input = Input::SET_LIB;
            }
        } else if (event.key.code == sf::Keyboard::S) {
            if (this->curr_lib + 1 < static_cast<int>(this->libs.size())) {
                this->curr_lib += 1;
                this->input = Input::SET_LIB;
            }
        } else if (event.key.code == sf::Keyboard::Up) {
            if (this->curr_game - 1 >= 0) {
                this->curr_game -= 1;
                this->input = Input::SET_GAME;
            }
        } else if (event.key.code == sf::Keyboard::Down) {
            if (this->curr_game + 1 < static_cast<int>(this->games.size())) {
                this->curr_game += 1;
                this->input = Input::SET_GAME;
            }
        }
    }

    void Menu::handle_typing(sf::Event event)
    {
        std::string tmp = this->get_name();
        if (event.text.unicode == '\b' && tmp.size() > 0)
            tmp.erase(tmp.end() - 1);
        else if (event.text.unicode != '\b' && event.text.unicode)
            tmp += event.text.unicode;
        this->set_name(tmp);
        this->input = Input::SET_NAME;
    }
} // namespace arcade
