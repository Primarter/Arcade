/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** Line.cpp
*/

#include "menu/Line.hpp"

namespace arcade
{
    UI::Line::Line(sf::Text _text, sf::Vector2f pos, sf::Vector2f size, sf::Color col, sf::Color active_col):
        position(pos), col(col), active_col(active_col), text(_text)
    {
        this->rectangle.setSize(size);
        this->set_position(pos);
        this->rectangle.setFillColor(col);
        this->rectangle.setOutlineThickness(1);
        this->rectangle.setOutlineColor(sf::Color::Black);
    }


    bool UI::Line::get_active(void)
    {
        return this->active;
    }

    void UI::Line::set_active(bool set_to)
    {
        this->active = set_to;
        this->rectangle.setFillColor(set_to ? this->active_col : this->col);
    }

    void UI::Line::set_position(sf::Vector2f pos)
    {
        position = pos;
        this->rectangle.setPosition(pos);
        this->text.setOrigin(sf::Vector2f(0, this->text.getCharacterSize() / 1.5));
        this->text.setPosition(sf::Vector2f(10, this->rectangle.getSize().y / 2) + pos);
    }

    void UI::Line::set_size(sf::Vector2f size)
    {
        this->rectangle.setSize(size);
    }

    void UI::Line::set_color(sf::Color _col, sf::Color _active_col)
    {
        this->col = _col;
        this->active_col = _active_col;
        this->rectangle.setFillColor(this->active ? _active_col : _col);
    }
    void UI::Line::set_outline(float thickness, sf::Color col)
    {
        this->rectangle.setOutlineThickness(thickness);
        this->rectangle.setOutlineColor(col);
    }

    bool UI::Line::contains(sf::Vector2f pt)
    {
        return (rectangle.getGlobalBounds().contains(pt));
    }

    void UI::Line::draw(sf::RenderTarget &win)
    {
        win.draw(this->rectangle);
        win.draw(this->text);
    }

    sf::Vector2f UI::Line::get_position(void)
    {
        return this->position;
    }

    void UI::Line::set_string(std::string s)
    {
        this->text.setString(s);
    }

    void UI::Line::set_text_color(sf::Color col)
    {
        this->text.setFillColor(col);
    }

    void UI::Line::set_text_size(std::size_t size)
    {
        this->text.setCharacterSize(size);
    }

    void UI::Line::set_text(sf::Text txt)
    {
        this->text = txt;
    }

    void UI::Line::set_font(sf::Font f)
    {
        this->text.setFont(f);
    }

    std::string UI::Line::get_string(void)
    {
        return (this->text.getString());
    }
}
