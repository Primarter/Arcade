/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** nibbler_game.hpp
*/

#pragma once
#include "IGameModule.hpp"
#include <sstream>
#include <string>

extern "C" arcade::IGameModule *entryPoint();
namespace arcade
{
    class NibblerGame : public IGameModule
    {
        public:
            NibblerGame(std::string name);
            ~NibblerGame() = default;
            void init() override;
            void stop() override;
            const std::string &getName() const override;
            const std::vector<GameObject> &update(std::vector<Input::Key>) override;
            bool is_over(void) const override;
            int get_score(void) const override;
        private:
            std::vector<Vector2> position;
            int speed;
            int time;
            int gameTime;
            int score;
            Vector2 playerPos;
            char direction;
            bool close = false;
            bool win = false;
            bool dead;
            std::vector<GameObject> objects;
            std::string name;
            void drawMainBox();
            void drawPlayerHead();
            void drawPlayerBody();
            void drawText();
            void playerInput(std::vector<Input::Key>);
            void reset(void);
            char map[25][25];
            char originalMap[25][25] = {
            {'O','-','-','-','O','-','-','-','-','O','-','-','O','-','-','O','-','-','-','-','O','-','-','-','O'},
            {'-','X','X','X','-','X','O','X','-','X','X','X','X','X','X','X','-','X','O','X','-','X','X','X','-'},
            {'-','X','-','X','-','X','-','X','-','-','O','-','-','-','O','-','-','X','-','X','-','X','-','X','-'},
            {'-','X','X','X','-','X','-','X','-','X','X','X','-','X','X','X','-','X','-','X','-','X','X','X','-'},
            {'O','-','-','-','O','X','-','X','-','X','-','O','-','O','-','X','-','X','-','X','O','-','-','-','O'},
            {'-','X','X','X','X','X','O','X','O','X','O','X','X','X','O','X','O','X','O','X','X','X','X','X','-'},
            {'-','X','-','-','-','-','-','X','-','X','-','X','-','X','-','X','-','X','-','-','-','-','-','X','-'},
            {'O','X','O','X','X','X','-','X','-','X','O','X','X','X','O','X','-','X','-','X','X','X','O','X','O'},
            {'-','X','-','-','-','-','-','X','-','-','-','O','-','O','-','-','-','X','-','-','-','-','-','X','-'},
            {'-','X','X','X','X','X','O','X','O','X','X','X','-','X','X','X','O','X','O','X','X','X','X','X','-'},
            {'O','-','-','-','O','X','-','-','-','-','-','-','-','-','-','-','-','-','-','X','O','-','-','-','O'},
            {'X','X','X','X','-','X','-','X','X','X','O','X','X','X','O','X','X','X','-','X','-','X','X','X','X'},
            {'-','-','-','X','-','O','-','-','-','-','-','-','-','-','-','-','-','-','-','O','-','X','-','-','-'},
            {'X','X','X','X','-','X','-','X','X','X','O','X','X','X','O','X','X','X','-','X','-','X','X','X','X'},
            {'O','-','-','-','O','X','-','-','-','-','-','-','-','-','-','-','-','-','-','X','O','-','-','-','O'},
            {'-','X','X','X','X','X','O','X','O','X','X','X','-','X','X','X','O','X','O','X','X','X','X','X','-'},
            {'-','X','-','-','-','-','-','X','-','-','-','O','-','O','-','-','-','X','-','-','-','-','-','X','-'},
            {'O','X','O','X','X','X','-','X','-','X','O','X','X','X','O','X','-','X','-','X','X','X','O','X','O'},
            {'-','X','-','-','-','-','-','X','-','X','-','X','-','X','-','X','-','X','-','-','-','-','-','X','-'},
            {'-','X','X','X','X','X','O','X','O','X','O','X','X','X','O','X','O','X','O','X','X','X','X','X','-'},
            {'O','-','-','-','O','X','-','X','-','X','-','O','-','O','-','X','-','X','-','X','O','-','-','-','O'},
            {'-','X','X','X','-','X','-','X','-','X','X','X','-','X','X','X','-','X','-','X','-','X','X','X','-'},
            {'-','X','-','X','-','X','-','X','-','-','O','-','-','-','O','-','-','X','-','X','-','X','-','X','-'},
            {'-','X','X','X','-','X','O','X','-','X','X','X','X','X','X','X','-','X','O','X','-','X','X','X','-'},
            {'O','-','-','-','O','-','-','-','-','O','-','-','O','-','-','O','-','-','-','-','O','-','-','-','O'}};
    };
}
