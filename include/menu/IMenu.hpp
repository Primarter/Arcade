/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** menu/IMenu.hpp
*/

#pragma once

#include "arcade.hpp"

namespace arcade
{
    class IMenu
    {
        public:
            enum Input {
                IDLE,
                PLAY,
                SET_GAME,
                SET_LIB,
                SET_NAME,
                QUIT,
            };
            ~IMenu(void) = default;
            virtual void update(void) = 0;
            virtual Input get_input(void) const = 0;
            virtual int get_curr_game(void) const = 0;
            virtual int get_curr_lib(void) const = 0;
            virtual void open(void) = 0;
            virtual void close(void) = 0;
            virtual void set_name(std::string _name) = 0;
            virtual std::string get_name(void) = 0;
            virtual void set_scores(std::vector<std::string> _scores) = 0;
    };
    namespace UI
    {
        enum Color {
            ORANGE = 0xFCA311FF,
            BLUE = 0x14213DFF,
            DARK_BLUE = 0x0B1221FF,
            GREY = 0xAAAAAAFF
        };
    } // namespace UI
} // namespace arcade

using MenuEntryPointFunction = arcade::IMenu *(*)(
    const std::string &default_lib,
    const std::size_t &curr_lib,
    const std::size_t &game,
    const std::vector<std::string> &_libs,
    const std::vector<std::string> &_games,
    const std::vector<std::string> &_scores);
