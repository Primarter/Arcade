/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** nibbler_game.cpp
*/

#include "games/nibbler_game.hpp"

extern "C" arcade::IGameModule *entryPoint(void)
{
    return new arcade::NibblerGame("Nibbler");
}

namespace arcade
{
    NibblerGame::NibblerGame(std::string _name):
        name(_name)
    {}

    void NibblerGame::init()
    {
        std::cout << "NIBBLER INIT" << std::endl;
        playerPos = Vector2(340, 340);
        direction = 'r';
        dead = false;
        win = false;
        time = -180;
        gameTime = 6000;
        score = 0;
        position.clear();
        for (int i = 1; i < 6; i++) {
            position.push_back(Vector2(playerPos.x - (20 * i), playerPos.y));
        }
        for(int i = 0; i < 25; i++) {
            for(int j = 0; j < 25; j++) {
                map[i][j] = originalMap[i][j];
            }
        }
    }

    void NibblerGame::reset(void)
    {
        playerPos = Vector2(340, 340);
        direction = 'r';
        dead = false;
        win = false;
        time = -180;
        gameTime = 6000;
        score = 0;
        position.clear();
        for (int i = 1; i < 6; i++) {
            position.push_back(Vector2(playerPos.x - (20 * i), playerPos.y));
        }
        for(int i = 0; i < 25; i++) {
            for(int j = 0; j < 25; j++) {
                map[i][j] = originalMap[i][j];
            }
        }
    }

    void NibblerGame::stop()
    {
        std::cout << "NIBBLER STOP" << std::endl;
        this->close = false;
    }

    int NibblerGame::get_score(void) const
    {
        return score;
    }

    const std::string &NibblerGame::getName() const
    {
        return this->name;
    }

    const std::vector<GameObject> &NibblerGame::update(std::vector<Input::Key> input)
    {

        if (input.size() == 1 && (input[0] == Input::Escape || input[0] == Input::Closed)) {
            std::cout << "GAME RECEIVED CLOSED INPUT" << std::endl;
            this->close = true;
        }
        if (time >= 0 && !dead && !win)
            gameTime--;
        if(gameTime < 0)
            dead = true;
        this->objects.clear();
        if (!dead && !win)
            playerInput(input);
        if (std::find(input.begin(), input.end(), Input::Key::Space) != input.end() && dead)
            reset();
        if (std::find(input.begin(), input.end(), Input::Key::Space) != input.end() && win)
            reset();


        win = true;

        //Draw map

        Sprite sp("./resources/images/map.png");
        sp.position = Vector2(100, 100);
        this->objects.push_back(sp);

        for(int i = 0; i < 25; i++) {
            for(int j = 0; j < 25; j++) {
                if(map[i][j] == 'O') {
                    Sprite sp("./resources/images/apple.png");
                    sp.position = Vector2((j * 20) + 105, (i * 20) + 105);
                    this->objects.push_back(sp);
                    win = false;
                }

                if(map[i][j] == 'X' && playerPos.x == (j * 20) + 100 && playerPos.y == (i * 20) + 100)
                    dead = true;

                if(map[i][j] == 'O' && playerPos.x == (j * 20) + 100 && playerPos.y == (i * 20) + 100) {
                    position.push_back(Vector2(position[position.size()].x, position[position.size()].y));
                    map[i][j] = '-';
                    score += 100;
                }
            }
        }

        drawPlayerBody();
        drawPlayerHead();
        drawMainBox();
        drawText();

        return this->objects;
    }

    void NibblerGame::drawPlayerBody()
    {
        for(int i = 0; i < position.size(); i++) {
            //Tail
            if (i == position.size() - 1) {
                std::string part = "";
                if (position[i].x < position[i-1].x)
                    part = "./resources/images/tail0.png";
                if (position[i].y < position[i-1].y)
                    part = "./resources/images/tail1.png";
                if (position[i].x > position[i-1].x)
                    part = "./resources/images/tail2.png";
                if (position[i].y > position[i-1].y)
                    part = "./resources/images/tail3.png";
                if (part != "") {
                    Sprite b(part);
                    b.position = Vector2(position[i].x, position[i].y);
                    this->objects.push_back(b);
                }
            }
            //Neck
            if (i == 0) {
                //Line
                std::string part = "";
                if ((position[i].x > position[i+1].x && position[i].x < playerPos.x) || (position[i].x < position[i+1].x && position[i].x > playerPos.x))
                    part = "./resources/images/body0.png";
                if ((position[i].y > position[i+1].y && position[i].y < playerPos.y) || (position[i].y < position[i+1].y && position[i].y > playerPos.y))
                    part = "./resources/images/body1.png";

                //Corner
                if ((position[i].x < playerPos.x && position[i].y < position[i+1].y) || (position[i].x < position[i+1].x && position[i].y < playerPos.y))
                    part = "./resources/images/corner0.png";
                if ((position[i].x > position[i+1].x && position[i].y < playerPos.y) || (position[i].x > playerPos.x && position[i].y < position[i+1].y))
                    part = "./resources/images/corner1.png";
                if ((position[i].x > playerPos.x && position[i].y > position[i+1].y) || (position[i].x > position[i+1].x && position[i].y > playerPos.y))
                    part = "./resources/images/corner2.png";
                if ((position[i].x < position[i+1].x && position[i].y > playerPos.y) || (position[i].x < playerPos.x && position[i].y > position[i+1].y))
                    part = "./resources/images/corner3.png";
                if (part != "") {
                    Sprite b(part);
                    b.position = Vector2(position[i].x, position[i].y);
                    this->objects.push_back(b);
                }
            }

            //Body
            if (i > 0 && i < position.size() - 1) {
                //Line
                std::string part = "";
                if ((position[i].x > position[i+1].x && position[i].x < position[i-1].x) || (position[i].x < position[i+1].x && position[i].x > position[i-1].x))
                    part = "./resources/images/body0.png";
                if ((position[i].y > position[i+1].y && position[i].y < position[i-1].y) || (position[i].y < position[i+1].y && position[i].y > position[i-1].y))
                    part = "./resources/images/body1.png";

                //Corner
                if ((position[i].x < position[i-1].x && position[i].y < position[i+1].y) || (position[i].x < position[i+1].x && position[i].y < position[i-1].y))
                    part = "./resources/images/corner0.png";
                if ((position[i].x > position[i+1].x && position[i].y < position[i-1].y) || (position[i].x > position[i-1].x && position[i].y < position[i+1].y))
                    part = "./resources/images/corner1.png";
                if ((position[i].x > position[i-1].x && position[i].y > position[i+1].y) || (position[i].x > position[i+1].x && position[i].y > position[i-1].y))
                    part = "./resources/images/corner2.png";
                if ((position[i].x < position[i+1].x && position[i].y > position[i-1].y) || (position[i].x < position[i-1].x && position[i].y > position[i+1].y))
                    part = "./resources/images/corner3.png";
                if (part != "") {
                    Sprite b(part);
                    b.position = Vector2(position[i].x, position[i].y);
                    this->objects.push_back(b);
                }
            }

            if (position[i].x == playerPos.x && position[i].y == playerPos.y)
                dead = true;
        }
    }

    void NibblerGame::drawPlayerHead()
    {
        std::string part = "";
        if (playerPos.x > position[0].x)
            part = "./resources/images/head0.png";
        if (playerPos.y > position[0].y)
            part = "./resources/images/head1.png";
        if (playerPos.x < position[0].x)
            part = "./resources/images/head2.png";
        if (playerPos.y < position[0].y)
            part = "./resources/images/head3.png";
        if (part != "") {
            Sprite b(part);
            b.position = Vector2(playerPos.x, playerPos.y);
            this->objects.push_back(b);
        }
    }

    void NibblerGame::playerInput(std::vector<Input::Key> input)
    {
        if (std::find(input.begin(), input.end(), Input::Key::Z) != input.end() && direction != 'd')
            direction = 'u';
        else if (std::find(input.begin(), input.end(), Input::Key::S) != input.end() && direction != 'u')
            direction = 'd';
        else if (std::find(input.begin(), input.end(), Input::Key::Q) != input.end() && direction != 'r')
            direction = 'l';
        else if (std::find(input.begin(), input.end(), Input::Key::D) != input.end() && direction != 'l')
            direction = 'r';

        time++;
        if (time > 10) {
            time = 0;

            for(int i = position.size(); i > 0; i--) {
                position[i] = position[i-1];
            }
            position[0] = playerPos;

            if (direction == 'u')
                playerPos.y -= 20;
            if (direction == 'd')
                playerPos.y += 20;
            if (direction == 'l')
                playerPos.x -= 20;
            if (direction == 'r')
                playerPos.x += 20;

            if (playerPos.x < 100)
                dead = true;
            if (playerPos.x > 590)
                dead = true;
            if (playerPos.y < 100)
                dead = true;
            if (playerPos.y > 590)
                dead = true;
        }
    }

    void NibblerGame::drawText(void)
    {

        std::ostringstream oss;
        oss << "Time " << gameTime / 60;
        std::string tm = oss.str();

        Text tex(tm);
        tex.color = Color(0xFFFF00);
        tex.position = Vector2(100, 50);
        this->objects.push_back(tex);

        std::ostringstream sc;
        sc << "Score " << score;
        std::string scm = sc.str();
        Text tex2(scm);
        tex2.color = Color(0xFF0000);
        tex2.position = Vector2(100, 70);
        this->objects.push_back(tex2);

        if (dead) {
            Rectangle b2(Vector2(700, 700));
            b2.position = Vector2(0, 0);
            b2.color = Color(0, 0, 0, 100);
            this->objects.push_back(b2);

            Text tex3("Game Over");
            tex3.color = Color(255, 255, 255);
            tex3.position = Vector2(300, 320);
            this->objects.push_back(tex3);

            Text tex4("Press SPACE to retry");
            tex4.color = Color(255, 255, 255);
            tex4.position = Vector2(270, 360);
            this->objects.push_back(tex4);
        }

        if (win) {
            Rectangle b2(Vector2(700, 700));
            b2.position = Vector2(0, 0);
            b2.color = Color(0, 0, 0, 100);
            this->objects.push_back(b2);

            Text tex3("Congratulation");
            tex3.color = Color(255, 255, 255);
            tex3.position = Vector2(290, 320);
            this->objects.push_back(tex3);

            Text tex4("Press SPACE to retry");
            tex4.color = Color(255, 255, 255);
            tex4.position = Vector2(270, 360);
            this->objects.push_back(tex4);
        }

        if (time < 0) {
            Rectangle b2(Vector2(700, 700));
            b2.position = Vector2(0, 0);
            b2.color = Color(0, 0, 0, 100);
            this->objects.push_back(b2);

            Text tex3("Ready ?");
            tex3.color = Color(255, 255, 255);
            tex3.position = Vector2(315, 320);
            this->objects.push_back(tex3);
        }
    }

    void NibblerGame::drawMainBox(void)
    {
        // Line ln(Vector2(100, 100));
        // ln.position = Vector2(600, 100);
        // ln.color = Color(255, 255, 255);
        // this->objects.push_back(ln);

        // Line ln2(Vector2(600, 100));
        // ln2.position = Vector2(600, 600);
        // ln2.color = Color(255, 255, 255);
        // this->objects.push_back(ln2);

        // Line ln3(Vector2(600, 600));
        // ln3.position = Vector2(100, 600);
        // ln3.color = Color(255, 255, 255);
        // this->objects.push_back(ln3);

        // Line ln4(Vector2(100, 600));
        // ln4.position = Vector2(100, 100);
        // ln4.color = Color(255, 255, 255);
        // this->objects.push_back(ln4);
    }

    bool NibblerGame::is_over(void) const
    {
        return this->close;
    }
} // namespace arcade
