/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** Table.cpp
*/

#include "menu/Table.hpp"

namespace arcade
{
    UI::Table::Table(const std::vector<std::string> &names, const sf::Font &_font, const sf::Vector2u size, const sf::Vector2f pos):
        position(pos), font(_font)
    {
        if (!this->area.create(size.x, size.y))
            throw std::runtime_error("Render Texture couldn't be created");
        sf::Vector2f line_pos = {0, 0};
        for (auto &&name : names) {
            sf::Text text(name, this->font, 24);
            UI::Line line(text, line_pos);
            lines.push_back(line);
            line_pos += {0, 50};
        }
    }

    void UI::Table::add_line(const std::string str)
    {
        UI::Line line = (*(this->lines.end() - 1));
        line.set_string(str);
        line.set_position(line.get_position() + sf::Vector2f{0, 50});
        lines.push_back(line);
    }

    void UI::Table::set_position(const sf::Vector2f pos)
    {
        this->position = pos;
    }

    sf::Vector2f UI::Table::get_position(void)
    {
        return this->position;
    }

    void UI::Table::draw(sf::RenderTarget &target, int active)
    {
        int idx = 0;
        area.clear(sf::Color(UI::DARK_BLUE));
        if (lines.size() == 0) {
            sf::Text text("No content", this->font, 24);
            text.setFillColor(sf::Color(255, 255, 255, 120));
            UI::Line empty_mess(text, sf::Vector2f());
            empty_mess.draw(area);
        } else {
            for (auto &&line : lines) {
                line.set_active(idx == active);
                line.draw(area);
                idx++;
            }
        }
        area.display();
        this->sprite = sf::Sprite(area.getTexture());
        this->sprite.setPosition(this->position);
        target.draw(sprite);
    }

    bool UI::Table::contains(sf::Vector2f point) const
    {
        return this->sprite.getGlobalBounds().contains(point);
    }

    void UI::Table::set_lines(const std::vector<std::string> &names)
    {
        sf::Vector2f line_pos = {0, 0};
        for (auto &&name : names) {
            sf::Text text(name, this->font, 24);
            UI::Line line(text, line_pos);
            lines.push_back(line);
            line_pos += {0, 50};
        }
    }

    int UI::Table::get_offset(void)
    {
        return this->offset;
    }

    void UI::Table::set_offset(int new_offset)
    {
        sf::Vector2f start;
        sf::Vector2f lpos = (this->lines.end() - 1)->get_position();
        sf::Vector2f fpos = this->lines.begin()->get_position();
        if (lpos.y > this->area.getSize().y * (3/4) && fpos.y <= 0) {
            this->offset = new_offset;
            for (auto &&line : lines)
                line.set_position(start + sf::Vector2f(0, this->offset));
        }
    }

    void UI::Table::add_offset(int add)
    {
        sf::Vector2f lpos = (this->lines.end() - 1)->get_position();
        sf::Vector2f fpos = this->lines.begin()->get_position();
        if (lpos.y + add * 10 > ((this->area.getSize().y)*3)/4 && (fpos.y + add * 10) <= 0) {
            this->offset += add * 10;
            for (auto &&line : lines)
                line.set_position(line.get_position() + sf::Vector2f(0, add * 10));
        }
    }
}