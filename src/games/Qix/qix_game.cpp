/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** qix_game.cpp
*/

#include "games/qix_game.hpp"

extern "C" arcade::IGameModule *entryPoint(void)
{
    return new arcade::QixGame("Qix");
}

namespace arcade
{
    QixGame::QixGame(std::string _name):
        name(_name)
    {}

    void QixGame::init()
    {
        std::cout << "QIX INIT" << std::endl;
        playerPos = Vector2(350, 600);
    }

    void QixGame::stop()
    {
        std::cout << "QIX STOP" << std::endl;
        this->close = false;
    }

    int QixGame::get_score(void) const
    {
        return random() % 500;
    }

    const std::string &QixGame::getName() const
    {
        return this->name;
    }

    const std::vector<GameObject> &QixGame::update(std::vector<Input::Key> input)
    {
        if (input.size() == 1 && (input[0] == Input::Escape || input[0] == Input::Closed)) {
            std::cout << "GAME RECEIVED CLOSED INPUT" << std::endl;
            this->close = true;
        }

        this->objects.clear();
        drawMainBox();
        playerInput(input);

        Circle circ(5);
        if (speed == 1)
            circ.color = Color(255, 0, 0);
        else
            circ.color = Color(0, 255, 255);
        circ.position = Vector2(playerPos.x, playerPos.y);
        this->objects.push_back(circ);

        return this->objects;
    }

    void QixGame::playerInput(std::vector<Input::Key> input)
    {
        if (playerPos.x == 100 || playerPos.x == 600 || playerPos.y == 100 || playerPos.y == 600) {
            if (std::find(input.begin(), input.end(), Input::Key::Space) != input.end())
                speed = 1;
            else
                speed = 2;
        }

        if (std::find(input.begin(), input.end(), Input::Key::Z) != input.end())
            playerPos.y -= speed;
        else if (std::find(input.begin(), input.end(), Input::Key::S) != input.end())
            playerPos.y += speed;
        else if (std::find(input.begin(), input.end(), Input::Key::Q) != input.end())
            playerPos.x -= speed;
        else if (std::find(input.begin(), input.end(), Input::Key::D) != input.end())
            playerPos.x += speed;

        if (playerPos.x < 100)
            playerPos.x = 100;
        if (playerPos.x > 600)
            playerPos.x = 600;
        if (playerPos.y < 100)
            playerPos.y = 100;
        if (playerPos.y > 600)
            playerPos.y = 600;
    }

    void QixGame::drawMainBox(void)
    {
        Line ln(Vector2(100, 100));
        ln.position = Vector2(600, 100);
        ln.color = Color(255, 255, 255);
        this->objects.push_back(ln);

        Line ln2(Vector2(600, 100));
        ln2.position = Vector2(600, 600);
        ln2.color = Color(255, 255, 255);
        this->objects.push_back(ln2);

        Line ln3(Vector2(600, 600));
        ln3.position = Vector2(100, 600);
        ln3.color = Color(255, 255, 255);
        this->objects.push_back(ln3);

        Line ln4(Vector2(100, 600));
        ln4.position = Vector2(100, 100);
        ln4.color = Color(255, 255, 255);
        this->objects.push_back(ln4);
    }

    bool QixGame::is_over(void) const
    {
        return this->close;
    }
} // namespace arcade
