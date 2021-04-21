/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** Qix.hpp
*/

#pragma once
#include "IGameModule.hpp"

extern "C" arcade::IGameModule *entryPoint();
namespace arcade
{
    class Qix : public IGameModule
    {
        public:
            Qix(void) = default;
            ~Qix(void) = default;
            void init(void) override;
            void stop(void) override;
            const std::string &getName(void) const override;
            const std::vector<GameObject> &update(std::vector<Input::Key>) override;
            bool is_over(void) const override;
            int get_score(void) const override;
        private:
            bool close = false;
            std::vector<GameObject> objects;
            std::string _name = "Qix";
    };
}
