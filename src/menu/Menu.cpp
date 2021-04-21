/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** Menu.cpp
*/

#include "menu/Menu.hpp"

namespace arcade
{

    sf::Font get_font_from_file(const std::string src)
    {
        sf::Font f;
        f.loadFromFile(src);
        return (f);
    }

    bool is_word_char(char c)
    {
        return (
            (c >= '0' && c <= '9') ||
            (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            (c == '_' || c == '-')
        );
    }

    Menu::~Menu(void) {}
    Menu::Menu(const std::string &default_lib,
                const std::size_t &curr_lib,
                const std::size_t &game,
                const std::vector<std::string> &_libs,
                const std::vector<std::string> &_games,
                const std::vector<std::string> &_scores):
        default_lib(default_lib),
        curr_lib(curr_lib),
        curr_game(game),
        libs(_libs),
        games(_games),
        scores(_scores),
        regular_font(get_font_from_file("resources/fonts/whitneybook.otf")),
        bold_font(get_font_from_file("resources/fonts/whitneybold.otf")),
        medium_font(get_font_from_file("resources/fonts/whitneymedium.otf")),
        libs_table(this->libs, this->regular_font, {320, 530}, {0, 190}),
        games_table(this->games, this->regular_font, {320, 530}, {320, 190}),
        def_lib_line(
            sf::Text("Default library:\t" + this->default_lib, this->medium_font, 24),
            sf::Vector2f(0, 65),
            sf::Vector2f(width/2, 75)
        ),
        play_btn(sf::Text("PLAY >", this->bold_font, 36),
            sf::Vector2f(width - 175, height/2),
            sf::Vector2f(175, 75)
        ),
        name_field(UI::Line(sf::Text(this->name, this->medium_font, 20),
            sf::Vector2f(width - 170, 15),
            sf::Vector2f(150, 35)),
            this->name
        )
    {
        this->window.create(sf::VideoMode(this->width, this->height), "", sf::Style::Default);
        this->window.setFramerateLimit(this->fps);
        play_btn.set_color(sf::Color(UI::DARK_BLUE), sf::Color(UI::ORANGE));
        if (this->games.size() > 0) {
            play_btn.set_active(true);
            play_btn.set_color(sf::Color::White);
        } else
            play_btn.set_color(sf::Color(UI::GREY));
    }

    void Menu::update(void)
    {
        this->input = Input::IDLE;
        window.clear(sf::Color::Black);

        this->draw();

        window.display();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                event.type = sf::Event::Closed;
            switch (event.type) {
                case sf::Event::TextEntered:
                    if (this->name_field.get_active())
                        handle_typing(event);
                    break;
                case sf::Event::Closed:
                    window.close();
                    this->input = Input::QUIT;
                    break;
                case sf::Event::MouseButtonReleased:
                    this->handle_click_event(event);
                    break;
                case sf::Event::MouseWheelMoved:
                    this->handle_scroll_event(event);
                    break;
                case sf::Event::KeyReleased:
                    if (!this->name_field.get_active())
                        this->handle_keyboard(event);
                    break;
                default:
                    break;
            }
        }
    }

    Menu::Input Menu::get_input(void) const { return this->input; }
    int Menu::get_curr_lib(void) const { return this->curr_lib; }
    int Menu::get_curr_game(void) const { return this->curr_game; }
    void Menu::open(void)
    {
        if (!this->window.isOpen()) {
            this->window.create(sf::VideoMode(this->width, this->height), "", sf::Style::Default);
            this->window.setFramerateLimit(this->fps);
        }
    }
    void Menu::close(void)
    {
        if (this->window.isOpen()) {
            this->window.close();
        }
    }

    void Menu::set_name(std::string _name)
    {
        this->name = _name;
        this->name_field.set_string(_name);
    }

    std::string Menu::get_name(void)
    {
        return this->name;
    }

    void Menu::set_scores(std::vector<std::string> _scores)
    {
        this->scores = _scores;
    }
}

extern "C" arcade::Menu *entryPoint(
    const std::string &default_lib,
    const std::size_t &curr_lib,
    const std::size_t &game,
    const std::vector<std::string> &_libs,
    const std::vector<std::string> &_games,
    const std::vector<std::string> &_scores)
{
    return new arcade::Menu(default_lib, curr_lib, game, _libs, _games, _scores);
}
