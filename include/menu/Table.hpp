/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** Table.hpp
*/

#pragma once

#include "arcade.hpp"
#include "menu/Line.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace arcade
{
    namespace UI
    {
        class Table
        {
            private:
                sf::Vector2f position;
                sf::RenderTexture area;
                std::vector<Line> lines;
                sf::Font font;
                sf::Sprite sprite;
                int offset = 0;
                int active = 0;
            public:
                Table(const std::vector<std::string> &str,
                    const sf::Font &_font,
                    const sf::Vector2u size = sf::Vector2u(500, 500),
                    const sf::Vector2f pos = sf::Vector2f());
                ~Table(void) = default;
                void draw(sf::RenderTarget &targ, int active = -1);
                void set_position(const sf::Vector2f pos);
                sf::Vector2f get_position(void);
                void add_line(const std::string str);
                void set_lines(const std::vector<std::string> &str);
                bool contains(sf::Vector2f point) const;
                void set_offset(int new_offset);
                void add_offset(int add);
                int get_offset(void);
        };
    }
}