/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** Core.hpp
*/

#pragma once

#include "arcade.hpp"
#include "menu/IMenu.hpp"
#include "IGraphicalLibrary.hpp"
#include "IGameModule.hpp"
#include "DLLoader.hpp"
#include "core/Stopwatch.hpp"
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <map>

namespace arcade
{

    using lib_ptr = std::unique_ptr<arcade::IGraphicalLibrary>;
    using lib_array = std::vector<lib_ptr>;

    using game_ptr = std::unique_ptr<arcade::IGameModule>;
    using game_array = std::vector<game_ptr>;

    class Core
    {
        private:
            void menu_loop(std::unique_ptr<IMenu> &menu);
            void game_loop(void);
            void handle_menu_input(std::unique_ptr<IMenu> &menu, IMenu::Input input);
            void get_scores(void);
            void add_score(int score);
            void write_scores(void);
            std::vector<std::string> get_scores_strings(void);
            void switch_lib(int idx);

            arcade::lib_ptr _default_lib;
            arcade::lib_array _libs;
            arcade::game_array _games;
            int _curr_lib_idx = -1;
            std::size_t _curr_game_idx = 0;
            std::string name = "Guest";
            std::multimap<int, std::string> scores;
        public:
            Core(arcade::IGraphicalLibrary *dl);
            ~Core(void) = default;

            arcade::game_ptr &curr_game(void);
            arcade::lib_ptr &curr_lib(void);

            void load_lib_directory(void);
            void add_lib(IGraphicalLibrary *inst);
            void add_game(IGameModule *inst);
            void launch_menu(void);
            void launch_game(void);
            void set_game(std::size_t idx);
            void set_lib(int idx);
    };
}