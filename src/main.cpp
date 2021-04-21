/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** arcade.cpp
*/

#include <iostream>
#include "IGameModule.hpp"
#include "IGraphicalLibrary.hpp"
#include "arcade.hpp"

int main(int argc, char const *argv[])
{
    if (argc != 2)
        return 84;

    arcade::DLLoader<arcade::IGraphicalLibrary> argLoader(argv[1]);
    arcade::Core core(argLoader.getInstance()());
    core.launch_menu();

    return 0;
}
