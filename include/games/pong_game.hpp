/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** pong_game.hpp
*/

#pragma once
#include "IGameModule.hpp"
#include <sstream>
#include <string>

extern "C" arcade::IGameModule *entryPoint();
namespace arcade
{
    class Pong : public IGameModule
    {
        public:
            Pong(std::string name);
            ~Pong() = default;
            void init() override;
            void stop() override;
            const std::string &getName() const override;
            const std::vector<GameObject> &update(std::vector<Input::Key>) override;
            bool is_over(void) const override;
            int get_score(void) const override;
        private:
            Vector2 ballDirection;
            Vector2 player1;
            Vector2 player2;
            Vector2 ball;
            int score1;
            int score2;
            bool isAI;
            bool menu;
            int butPos;
            bool close = false;
            std::vector<GameObject> objects;
            std::string name;
            void menuText();
            void ballMovement();
            void scoring();
            void playerCollision();
            void playerRender();
            void terrainRender();
            void boundaries();
            void playerMovement(std::vector<Input::Key>);
            void menuInput(std::vector<Input::Key>);
            void game(std::vector<Input::Key>);
    };
}
