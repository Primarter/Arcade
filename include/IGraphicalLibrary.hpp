/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** IGraphicalLibrary.hpp
*/

#pragma once

#include <iostream>
#include <memory>
#include "GameObject.hpp"

namespace arcade
{

    // This should be derived for every library.
    // The interface allows specific behaviors for each library through the different functions.
    // init and stop are self-explanatory and are important because they allow loading the library without launching.
    class IGraphicalLibrary {
        public:
            virtual ~IGraphicalLibrary() = default;
            virtual void init() = 0;
            virtual void stop() = 0;
            virtual const std::string &getName() const = 0;
            // Draw uses the information contained in a GameObject to draw it onto the window
            // Persist those changes with the display method.
            virtual void draw(GameObject &entity) = 0;
            // Returns all the pressed keys at the moment
            virtual std::vector<Input::Key> get_input(void) = 0;
            // Display should be called every frame,
            // it persists any use of the draw function on the window
            virtual void display(void) = 0;
            // This will be called each frame to clear the current window
            virtual void clear(void) = 0;
    };
}