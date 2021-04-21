/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** lib.cpp
*/

#include "libs/sfml.hpp"
#include <iostream>

extern "C" void *entryPoint()
{
    std::cout << "[sfml] sfml load" << std::endl;
    return new arcade::sfml("sfml");
}


namespace arcade {
    static std::map<sf::Keyboard::Key, Input::Key> keymap = {
        {sf::Keyboard::A, Input::Key::A},
        {sf::Keyboard::B, Input::Key::B},
        {sf::Keyboard::C, Input::Key::C},
        {sf::Keyboard::D, Input::Key::D},
        {sf::Keyboard::E, Input::Key::E},
        {sf::Keyboard::F, Input::Key::F},
        {sf::Keyboard::G, Input::Key::G},
        {sf::Keyboard::H, Input::Key::H},
        {sf::Keyboard::I, Input::Key::I},
        {sf::Keyboard::J, Input::Key::J},
        {sf::Keyboard::K, Input::Key::K},
        {sf::Keyboard::L, Input::Key::L},
        {sf::Keyboard::M, Input::Key::M},
        {sf::Keyboard::N, Input::Key::N},
        {sf::Keyboard::O, Input::Key::O},
        {sf::Keyboard::P, Input::Key::P},
        {sf::Keyboard::Q, Input::Key::Q},
        {sf::Keyboard::R, Input::Key::R},
        {sf::Keyboard::S, Input::Key::S},
        {sf::Keyboard::T, Input::Key::T},
        {sf::Keyboard::U, Input::Key::U},
        {sf::Keyboard::V, Input::Key::V},
        {sf::Keyboard::W, Input::Key::W},
        {sf::Keyboard::X, Input::Key::X},
        {sf::Keyboard::Y, Input::Key::Y},
        {sf::Keyboard::Z, Input::Key::Z},
        {sf::Keyboard::Num0, Input::Key::Num0},
        {sf::Keyboard::Num1, Input::Key::Num1},
        {sf::Keyboard::Num2, Input::Key::Num2},
        {sf::Keyboard::Num3, Input::Key::Num3},
        {sf::Keyboard::Num4, Input::Key::Num4},
        {sf::Keyboard::Num5, Input::Key::Num5},
        {sf::Keyboard::Num6, Input::Key::Num6},
        {sf::Keyboard::Num7, Input::Key::Num7},
        {sf::Keyboard::Num8, Input::Key::Num8},
        {sf::Keyboard::Num9, Input::Key::Num9},
        {sf::Keyboard::Escape, Input::Key::Escape},
        {sf::Keyboard::Space, Input::Key::Space},
        {sf::Keyboard::Enter, Input::Key::Enter},
        {sf::Keyboard::Backspace, Input::Key::Backspace},
        {sf::Keyboard::Tab, Input::Key::Tab},
        {sf::Keyboard::Up, Input::Key::Up},
        {sf::Keyboard::Down, Input::Key::Down},
        {sf::Keyboard::Left, Input::Key::Left},
        {sf::Keyboard::Right, Input::Key::Right},
    };

    sfml::sfml(std::string name):
        name(name),
        _draw_func_map({
            { GameObject::ObjectType::CIRCLE, [this](GameObject &obj) { this->draw_circle(obj); } },
            { GameObject::ObjectType::RECTANGLE, [this](GameObject &obj) { this->draw_rectangle(obj); } },
            { GameObject::ObjectType::LINE, [this](GameObject &obj) { this->draw_line(obj); } },
            { GameObject::ObjectType::SPRITE, [this](GameObject &obj) { this->draw_sprite(obj); } },
            { GameObject::ObjectType::TEXT, [this](GameObject &obj) { this->draw_text(obj); } }
        })
    {
        std::cout << "ctor sfml" << std::endl;
    }

    sfml::~sfml()
    {
        std::cout << "dtor sfml" << std::endl;
    }

    const std::string &sfml::getName() const
    {
        return this->name;
    }


    // PUBLIC
    void sfml::init(void)
    {
        std::cout << "[sfml] sfml init" << std::endl;

        _window.create(sf::VideoMode(700, 700), "SFML window");
        _window.setKeyRepeatEnabled(false);
    }

    void sfml::stop(void)
    {
        std::cout << "[sfml] sfml stop" << std::endl;

        this->_keys.clear();
        _window.close();
    }

    void sfml::draw(GameObject &entity)
    {
        _draw_func_map[entity.type](entity);
    }

    std::vector<Input::Key> sfml::get_input(void)
    {
        sf::Event event;

        this->_keys.clear();
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _keys.push_back(Input::Closed);
            // } else if (event.type == sf::Event::KeyPressed) {
                // if (std::find(keymap.begin(), keymap.end(), event.key.code))
                //     _keys.push_back( keymap[event.key.code] );
            }
        }

        // continuous events
        for (const auto& key : keymap) {
            if (sf::Keyboard::isKeyPressed(key.first)) {
                _keys.push_back(key.second);
            }
        }

        return _keys;
    }

    void sfml::display(void)
    {
        _window.display();
    }

    void sfml::clear(void)
    {
        _window.clear();
    }

    //PRIVATE
    void sfml::draw_circle(arcade::GameObject &entity)
    {
        sf::CircleShape circle(entity.circle_radius);
        sf::Color color(entity.color.get_hex());

        circle.setFillColor(color);
        circle.setOutlineColor(color);
        circle.setOrigin(entity.circle_radius, entity.circle_radius);
        circle.setPosition(sf::Vector2f(entity.position.x, entity.position.y));

        _window.draw(circle);
    }

    void sfml::draw_rectangle(arcade::GameObject &entity)
    {
        sf::Color color(entity.color.get_hex());

        sf::RectangleShape rect(sf::Vector2f(entity.rect_dimensions.x, entity.rect_dimensions.y));
        rect.setPosition(sf::Vector2f(entity.position.x, entity.position.y));
        rect.setFillColor(color);

        _window.draw(rect);
    }

    void sfml::draw_line(arcade::GameObject &entity)
    {
        sf::Color color(entity.color.get_hex());
        sf::Vertex v[2];

        v[0].position = sf::Vector2f(entity.position.x, entity.position.y);
        v[0].color  = color;
        v[1].position = sf::Vector2f(entity.line_end.x, entity.line_end.y);
        v[1].color = color;

        _window.draw(v, 2, sf::Lines);
    }

    void sfml::draw_sprite(arcade::GameObject &entity)
    {
        sf::Texture texture;
        sf::Sprite sprite;

        texture.loadFromFile(entity.sprite_src);
        sprite.setTexture(texture);
        sprite.setPosition(sf::Vector2f(entity.position.x, entity.position.y));

        _window.draw(sprite);
    }

    void sfml::draw_text(arcade::GameObject &entity)
    {
        sf::Font font;
        font.loadFromFile("./resources/fonts/whitneymedium.otf");
        uint police = 24;
        sf::Color color(entity.color.get_hex());
        sf::Text text(entity.text_string, font, police);

        text.setPosition(sf::Vector2f(entity.position.x, entity.position.y));
        text.setFillColor(color);

        _window.draw(text);
    }
}
