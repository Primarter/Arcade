/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** pong_game.cpp
*/

#include "games/pong_game.hpp"

extern "C" arcade::IGameModule *entryPoint(void)
{
    return new arcade::Pong("Pong");
}

namespace arcade
{
    Pong::Pong(std::string _name):
        name(_name)
    {}

    void Pong::init()
    {
        menu = true;
        butPos = 0;
        score1 = 0;
        score2 = 0;
        player1 = Vector2(10, 325);
        player2 = Vector2(680, 325);
        ball = Vector2(350, 350);
        ballDirection = Vector2(-1,0);
        std::cout << "PONG INIT" << std::endl;
    }

    void Pong::stop()
    {
        std::cout << "PONG STOP" << std::endl;
        this->close = false;
    }

    int Pong::get_score(void) const
    {
        return score1;
    }

    const std::string &Pong::getName() const
    {
        return this->name;
    }

    const std::vector<GameObject> &Pong::update(std::vector<Input::Key> input)
    {
        if (input.size() == 1 && (input[0] == Input::Escape || input[0] == Input::Closed)) {
            std::cout << "GAME RECEIVED CLOSED INPUT" << std::endl;
            this->close = true;
        }

        this->objects.clear();

        if (!menu) {
            game(input);
        } else {
            menuInput(input);
            menuText();
        }

        return this->objects;
    }

    void Pong::menuInput(std::vector<Input::Key> input)
    {
        if (std::find(input.begin(), input.end(), Input::Key::Up) != input.end())
            butPos = 0;
        if (std::find(input.begin(), input.end(), Input::Key::Down) != input.end())
            butPos = 1;

        if (std::find(input.begin(), input.end(), Input::Key::Space) != input.end()) {
            isAI = butPos == 0 ? true : false;
            menu = false;
        }

        Circle b(10);
        b.color = Color(0x00FF00);
        if (butPos == 0) {
            b.position = Vector2(220, 315);
        } else {
            b.position = Vector2(220, 415);
        }
        this->objects.push_back(b);
    }

    void Pong::menuText(void)
    {
        Text t1("PONG");
        t1.color = Color(0xFFFFFF);
        t1.position = Vector2 (330, 10);
        this->objects.push_back(t1);

        Text t2("PLAYER vs COMPUTER");
        t2.color = Color(0xFFFFFF);
        t2.position = Vector2 (240, 300);
        this->objects.push_back(t2);

        Text t3("PLAYER vs PLAYER");
        t3.color = Color(0xFFFFFF);
        t3.position = Vector2 (255, 400);
        this->objects.push_back(t3);

        Text t4("Select a mode with UP/DOWN and press SPACE to start");
        t4.color = Color(0xFFFFFF);
        t4.position = Vector2 (10, 670);
        this->objects.push_back(t4);

        Text t5("PLAYER 2 controls UP/DOWN");
        t5.color = Color(0xFFFFFF);
        t5.position = Vector2 (10, 640);
        this->objects.push_back(t5);

        Text t6("PLAYER 1 controls Z/S");
        t6.color = Color(0xFFFFFF);
        t6.position = Vector2 (10, 610);
        this->objects.push_back(t6);
    }

    void Pong::ballMovement()
    {
        if (ball.y < 0) {
            ball.y = 0;
            ballDirection.y = -ballDirection.y;
        }
        if (ball.y > 700) {
            ball.y = 700;
            ballDirection.y = -ballDirection.y;
        }
        ball.x += ballDirection.x * 7;
        ball.y += ballDirection.y * 7;
    }

    void Pong::scoring()
    {
        if (ball.x < 0) {
            score2++;
            ball.x = 350;
            ballDirection.y = 0;
        }
        if (ball.x > 700) {
            score1++;
            ball.x = 350;
            ballDirection.y = 0;
        }
    }

    void Pong::playerCollision()
    {
        if (ball.x < player1.x + 15 && ball.x > player1.x - 5 && ball.y > player1.y - 5 && ball.y < player1.y + 55) {
            ballDirection.x = 1;
            ballDirection.y = (ball.y - (player1.y + 25)) / 30;
        }

        if (ball.x < player2.x + 15 && ball.x > player2.x - 5 && ball.y > player2.y - 5 && ball.y < player2.y + 55) {
            ballDirection.x = -1;
            ballDirection.y = (ball.y - (player2.y + 25)) / 30;
        }
    }

    void Pong::boundaries()
    {
        if (player1.y < 0)
            player1.y = 0;
        if (player1.y > 650)
            player1.y = 650;

        if (player2.y < 0)
            player2.y = 0;
        if (player2.y > 650)
            player2.y = 650;
    }

    void Pong::playerMovement(std::vector<Input::Key> input)
    {
        if (std::find(input.begin(), input.end(), Input::Key::Z) != input.end())
            player1.y -= 5;
        if (std::find(input.begin(), input.end(), Input::Key::S) != input.end())
            player1.y += 5;

        if (!isAI) {
            if (std::find(input.begin(), input.end(), Input::Key::Up) != input.end())
                player2.y -= 5;
            if (std::find(input.begin(), input.end(), Input::Key::Down) != input.end())
                player2.y += 5;
        } else {
            if (player2.y + 30 < ball.y) {
                player2.y += 5;
            }
            if (player2.y + 20 > ball.y) {
                player2.y -= 5;
            }
        }
        boundaries();
    }

    void Pong::playerRender()
    {
        Rectangle p1(Vector2(10, 50));
        p1.color = Color(0xFFFFFF);
        p1.position = Vector2(player1.x, player1.y);
        this->objects.push_back(p1);

        Rectangle p2(Vector2(10, 50));
        p2.color = Color(0xFFFFFF);
        p2.position = Vector2(player2.x, player2.y);
        this->objects.push_back(p2);
        
        Circle b(10);
        b.color = Color(0xFFFFFF);
        b.position = Vector2(ball.x, ball.y);
        this->objects.push_back(b);
    }

    void Pong::terrainRender()
    {
        Line ln(Vector2(350, 0));
        ln.position = Vector2(350, 700);
        ln.color = Color(255, 255, 255);
        this->objects.push_back(ln);

        std::ostringstream sc1;
        sc1 << score1;
        std::string scm1 = sc1.str();

        Text tex(scm1);
        tex.color = Color(0xFFFFFF);
        tex.position = Vector2 (150, 330);
        this->objects.push_back(tex);

        std::ostringstream sc2;
        sc2 << score2;
        std::string scm2 = sc2.str();

        Text tex2(scm2);
        tex2.color = Color(0xFFFFFF);
        tex2.position = Vector2 (550, 330);
        this->objects.push_back(tex2);
    }

    void Pong::game(std::vector<Input::Key> input)
    {
        ballMovement();
        scoring();
        playerCollision();
        playerMovement(input);
        playerRender();
        terrainRender();
    }

    bool Pong::is_over(void) const
    {
        return this->close;
    }
} // namespace arcade
