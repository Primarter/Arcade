/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** draw_menu.cpp
*/

#include "menu/Menu.hpp"
#include "menu/Table.hpp"

static void draw_general_background(sf::RenderTarget &win)
{
    sf::VertexArray gradient(sf::Quads, 4);
    gradient.append(sf::Vertex({0, 0}, sf::Color::Black));
    gradient.append(sf::Vertex({arcade::Menu::width, 0}, sf::Color::Black));
    gradient.append(sf::Vertex({arcade::Menu::width, arcade::Menu::height}, sf::Color(arcade::UI::BLUE)));
    gradient.append(sf::Vertex({0, arcade::Menu::height}, sf::Color(arcade::UI::BLUE)));
    win.draw(gradient);
}

namespace arcade
{

    void Menu::draw_tables(void)
    {
        sf::Text text("Libraries", this->medium_font, 24);
        UI::Line line(text, {0, 140});
        line.set_active(true);
        line.set_position({0, 140});
        line.draw(this->window);
        line.set_string("Games");
        line.set_position({320, 140});
        line.draw(this->window);
        this->libs_table.draw(this->window, this->curr_lib);
        this->games_table.draw(this->window, this->curr_game);
    }

    void Menu::draw_scores(void)
    {
        UI::Line line(sf::Text("Scores:", this->medium_font, 25), {this->width - 150, 66}, {150, 30});
        line.set_active(true);
        line.draw(this->window);
        line.set_active(false);
        line.set_text(sf::Text("", this->regular_font, 20));
        line.set_position(line.get_position() + sf::Vector2f(0, 30));
        for (auto &&score : this->scores) {
            line.set_string(score);
            line.draw(this->window);
            line.set_position(line.get_position() + sf::Vector2f(0, 30));
        }
    }

    void Menu::draw(void)
    {
        draw_general_background(this->window);

        // draw header
        sf::Text text(this->title, this->medium_font, 36);
        text.setOrigin(0, text.getCharacterSize()/2);
        text.setPosition(15, 65/2.5);
        sf::RectangleShape rectangle;
        rectangle.setSize({width, 65});
        rectangle.setFillColor(sf::Color(UI::ORANGE));
        rectangle.setPosition(0, 0);
        this->window.draw(rectangle);
        this->window.draw(text);

        rectangle.setSize({Menu::width, 5});
        rectangle.setFillColor(sf::Color(UI::GREY));
        rectangle.setPosition(0, Menu::height/2 + 75/2 - 2);
        this->window.draw(rectangle);

        text.setString(this->games[this->curr_game]);
        text.setCharacterSize(45);
        text.setPosition(this->width/2 + 25, 90);
        this->window.draw(text);
        text.setString(this->curr_lib >= 0 ? this->libs[this->curr_lib] : this->default_lib);
        text.setCharacterSize(45);
        text.setPosition(this->width/2 + 25, this->height / 2 + 90);
        this->window.draw(text);

        // Draw titles:

        this->def_lib_line.set_active(this->curr_lib == -1);
        this->def_lib_line.draw(this->window);
        this->draw_tables();
        this->play_btn.draw(this->window);
        this->name_field.draw(this->window);
        this->draw_scores();
    }
}