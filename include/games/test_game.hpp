/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** test_game.hpp
*/

#pragma once
#include "IGameModule.hpp"

extern "C" arcade::IGameModule *entryPoint();
namespace arcade
{
    class TestGame : public IGameModule
    {
        public:
            TestGame(std::string name);
            ~TestGame() = default;
            void init() override;
            void stop() override;
            const std::string &getName() const override;
            const std::vector<GameObject> &update(std::vector<Input::Key>) override;
            bool is_over(void) const override;
            int get_score(void) const override;
        private:
            bool close = false;
            std::vector<GameObject> objects;
            std::string name;
    };
}
