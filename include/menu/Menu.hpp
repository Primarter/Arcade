/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** Menu.hpp
*/

#pragma once

#include "arcade.hpp"
#include "menu/IMenu.hpp"
#include "Line.hpp"
#include "Field.hpp"
#include "Table.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace arcade
{
    class Menu : public IMenu
    {
        private:
            void moveFrame(void);
            void draw(void);
            void draw_tables(void);
            void draw_scores(void);
            void handle_click_event(sf::Event event);
            void handle_scroll_event(sf::Event event);
            void handle_keyboard(sf::Event event);
            void handle_typing(sf::Event event);
            void handle_fields(sf::Event event);

            std::string default_lib;
            int curr_lib;
            int curr_game;
            std::vector<std::string> libs;
            std::vector<std::string> games;
            std::vector<std::string> scores;
            std::string name;

            sf::RenderWindow window;
            sf::Vector2i offset;
            sf::Font regular_font;
            sf::Font bold_font;
            sf::Font medium_font;
            UI::Table libs_table;
            UI::Table games_table;
            UI::Line def_lib_line;
            UI::Line play_btn;
            UI::Field name_field;
            bool typing = false;
            std::string title = "ARCADE";
            const int fps = 60;
            Input input = Input::IDLE;
        public:
            static const int width = 1280;
            static const int height = 720;
            Menu(const std::string &default_lib,
                const std::size_t &curr_lib,
                const std::size_t &game,
                const std::vector<std::string> &libs,
                const std::vector<std::string> &games,
                const std::vector<std::string> &scores);
            ~Menu(void);
            void update(void) override;
            Input get_input(void) const override;
            int get_curr_lib(void) const override;
            int get_curr_game(void) const override;
            void set_scores(std::vector<std::string> _scores) override;
            void open(void) override;
            void close(void) override;
            void set_name(std::string _name) override;
            std::string get_name(void) override;
    };
}
