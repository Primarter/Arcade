/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** Line.hpp
*/

#pragma once

#include "arcade.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace arcade
{
    namespace UI
    {
        class Line
        {
            protected:
                sf::Vector2f position;
                sf::RectangleShape rectangle;
                bool active = false;
                sf::Color col = sf::Color(UI::DARK_BLUE);
                sf::Color active_col = sf::Color(UI::BLUE);
                sf::Text text;
            public:
                Line(sf::Text _text = sf::Text(),
                    sf::Vector2f position = sf::Vector2f(),
                    sf::Vector2f size = sf::Vector2f(320, 50),
                    sf::Color col = sf::Color(UI::DARK_BLUE),
                    sf::Color active_col = sf::Color(UI::BLUE));
                ~Line(void) = default;
                void set_active(bool set_to = true);
                bool get_active(void);
                sf::Vector2f get_position(void);
                void set_position(sf::Vector2f pos = sf::Vector2f());
                void set_size(sf::Vector2f size = sf::Vector2f(320, 50));
                void set_color(sf::Color col = sf::Color(UI::DARK_BLUE), sf::Color active_col = sf::Color(UI::BLUE));
                virtual std::string get_string(void);
                virtual void set_string(std::string);
                void set_text_color(sf::Color);
                void set_text_size(std::size_t _size);
                void set_text(sf::Text);
                void set_font(sf::Font);
                void set_outline(float thickness = 0, sf::Color col = sf::Color::Black);
                bool contains(sf::Vector2f pt);
                void draw(sf::RenderTarget &win);
        };
    }
}