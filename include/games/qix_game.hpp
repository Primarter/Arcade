/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** qix_game.hpp
*/

#pragma once
#include "IGameModule.hpp"

extern "C" arcade::IGameModule *entryPoint();
namespace arcade
{
    class QixGame : public IGameModule
    {
        public:
            QixGame(std::string name);
            ~QixGame() = default;
            void init() override;
            void stop() override;
            const std::string &getName() const override;
            const std::vector<GameObject> &update(std::vector<Input::Key>) override;
            bool is_over(void) const override;
            int get_score(void) const override;
        private:
            int speed;
            Vector2 playerPos;
            bool close = false;
            std::vector<GameObject> objects;
            std::string name;
            void drawMainBox();
            void playerInput(std::vector<Input::Key>);
    };
}
