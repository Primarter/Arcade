/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** load_lib_directory.cpp
*/

#include "core/Core.hpp"

extern "C" void *entryPoint(arcade::IGraphicalLibrary *src)
{
    std::cout << "[Core] Loading Core" << std::endl;
    return new arcade::Core (src);
}

namespace arcade
{

    arcade::game_ptr &Core::curr_game(void)
    {
        return this->_games[this->_curr_game_idx];
    }

    arcade::lib_ptr &Core::curr_lib(void)
    {
        if (this->_curr_lib_idx != -1)
            return this->_libs[this->_curr_lib_idx];
        else
            return this->_default_lib;
    }

    void Core::launch_menu(void)
    {
        std::vector<std::string> libs;
        std::vector<std::string> games;

        for (auto &&lib : this->_libs)
            libs.push_back(lib->getName());
        for (auto &&game : this->_games)
            games.push_back(game->getName());
        DLLoader<IMenu, MenuEntryPointFunction> menuLoader("./menu.so");
        std::unique_ptr<IMenu> menu(menuLoader.getInstance()((*this->_default_lib).getName(),
            this->_curr_lib_idx,
            this->_curr_game_idx,
            libs, games, this->get_scores_strings()));
        menu->set_name(this->name);
        this->menu_loop(menu);
    }

    void Core::handle_menu_input(std::unique_ptr<IMenu> &menu, IMenu::Input input)
    {
        switch (input) {
            case IMenu::Input::PLAY:
                if (_games.size() != 0) {
                    menu->close();
                    this->launch_game();
                    menu->set_scores(this->get_scores_strings());
                    menu->open();
                }
                break;
            case IMenu::Input::SET_GAME:
                this->_curr_game_idx = menu->get_curr_game();
                this->get_scores();
                menu->set_scores(this->get_scores_strings());
                break;
            case IMenu::Input::SET_LIB:
                this->_curr_lib_idx = menu->get_curr_lib();
                break;
            case IMenu::Input::SET_NAME:
                this->name = menu->get_name();
                break;
            default:
                break;
        }
    }

    void Core::menu_loop(std::unique_ptr<IMenu> &menu)
    {
        IMenu::Input input = IMenu::IDLE;

        do {
            this->handle_menu_input(menu, input);
            menu->update();
        } while((input = menu->get_input()) != IMenu::QUIT);
    }

    void Core::launch_game(void)
    {
        this->curr_lib()->init();
        this->curr_game()->init();
        this->game_loop();
        this->add_score(-this->curr_game()->get_score());
        this->curr_game()->stop();
        this->curr_lib()->stop();
        this->write_scores();
    }

    void Core::switch_lib(int new_idx)
    {
        if (new_idx < -1 || new_idx >= static_cast<int>(this->_libs.size()))
            return;

        this->curr_lib()->stop();
        this->_curr_lib_idx = new_idx;
        this->curr_lib()->init();
    }

    void Core::game_loop(void)
    {
        Stopwatch sw;
        sw.start();
        int saved_idx = this->_curr_lib_idx;

        while(!this->curr_game()->is_over()) {
            if (sw.getElapsedTime() >= (double)1/60) {
                std::vector<Input::Key> input = this->curr_lib()->get_input();
                if (input.size() && (input[0] == Input::Key::Y || input[0]  == Input::Key::U)) {
                    switch_lib(input[0] == Input::Key::Y ? this->_curr_lib_idx - 1 : this->_curr_lib_idx + 1);
                }

                std::vector<arcade::GameObject> entity_list = this->curr_game()->update(input);

                this->curr_lib()->clear();
                for (auto &&entity : entity_list) {
                    this->curr_lib()->draw(entity);
                }
                this->curr_lib()->display();
                sw.restart();
            }
        }
        switch_lib(saved_idx);
    }
}
