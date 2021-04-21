/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** core_init.cpp
*/

#include "core/Core.hpp"

static bool is_lib(std::string name)
{
    std::vector<std::string> libs = {
        "arcade_ndk++.so",
        "arcade_aalib.so",
        "arcade_libcaca.so",
        "arcade_allegro5.so",
        "arcade_xlib.so",
        "arcade_gtk+.so",
        "arcade_sfml.so",
        "arcade_irrlicht.so",
        "arcade_opengl.so",
        "arcade_vulkan.so",
        "arcade_qt5.so",
        "arcade_ncurses.so",
        "arcade_sdl2.so",
    };
    if (std::find(libs.begin(), libs.end(), name) != libs.end())
        return (true);
    return (false);
}

namespace arcade
{
    Core::Core(arcade::IGraphicalLibrary *dl)
    {
        if (!dl)
            throw std::runtime_error("dl ptr passed to Core constructor is null");
        try {
            this->_default_lib = arcade::lib_ptr (dl);
        } catch (std::runtime_error &e) {
            throw std::runtime_error("Core constructor: " + std::string(e.what()));
        }
        this->load_lib_directory();
        this->get_scores();
    }

    void Core::load_lib_directory(void)
    {
        DIR *dir_ptr;
        struct dirent *ent;

        if (!(dir_ptr = opendir("./lib")))
            throw std::runtime_error("Couldn't open ./lib directory");
        while ((ent = readdir(dir_ptr))) {
            if (ent->d_name == std::string(".") || ent->d_name == std::string(".."))
                continue;
            if (is_lib(ent->d_name)) {
                arcade::DLLoader<arcade::IGraphicalLibrary> loader(std::string("./lib/") + ent->d_name);
                this->_libs.push_back(std::unique_ptr<arcade::IGraphicalLibrary>(loader.getInstance()()));
            } else {
                arcade::DLLoader<arcade::IGameModule> loader(std::string("./lib/") + ent->d_name);
                this->_games.push_back(std::unique_ptr<arcade::IGameModule>(loader.getInstance()()));
            }
        }
        closedir(dir_ptr);
    }

    void Core::add_lib(IGraphicalLibrary *inst)
    {
        if (!inst)
            throw std::runtime_error("lib ptr passed is null");
        _libs.push_back(arcade::lib_ptr(inst));
    }

    void Core::add_game(IGameModule *inst)
    {
        if (!inst)
            throw std::runtime_error("game ptr passed is null");
        _games.push_back(arcade::game_ptr(inst));
    }
}