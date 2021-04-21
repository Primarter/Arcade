/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** test_game.cpp
*/

#include "games/test_game.hpp"

extern "C" arcade::IGameModule *entryPoint(void)
{
    return new arcade::TestGame("TestGame");
}

namespace arcade
{
    TestGame::TestGame(std::string _name):
        name(_name)
    {}

    void TestGame::init()
    {
        std::cout << "GAMETEST INIT" << std::endl;
    }

    void TestGame::stop()
    {
        std::cout << "GAMETEST STOP" << std::endl;
        this->close = false;
    }

    int TestGame::get_score(void) const
    {
        return random() % 500;
    }

    const std::string &TestGame::getName() const
    {
        return this->name;
    }

    const std::vector<GameObject> &TestGame::update(std::vector<Input::Key> input)
    {
        if (input.size() == 1 && (input[0] == Input::Escape || input[0] == Input::Closed)) {
            std::cout << "GAME RECEIVED CLOSED INPUT" << std::endl;
            this->close = true;
        }

        this->objects.clear();

        Rectangle rect(Vector2(50, 50));
        rect.color = Color(0xFF00FF);
        this->objects.push_back(rect);

        Circle circ(30);
        circ.color = Color(0, 255, 100);
        circ.position = Vector2(200, 150);
        this->objects.push_back(circ);

        Text tex("Test");
        tex.color = Color(0xFFFFFF);
        this->objects.push_back(tex);

        Sprite sp("./resources/images/guy.png");
        sp.position = Vector2(500, 300);
        this->objects.push_back(sp);

        Line ln(Vector2(500, 500));
        ln.position = Vector2(50, 400);
        ln.color = Color(100, 0, 255);
        this->objects.push_back(ln);

        return this->objects;
    }

    bool TestGame::is_over(void) const
    {
        return this->close;
    }
} // namespace arcade
