/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** Field.hpp
*/

#pragma once

#include "Line.hpp"

namespace arcade
{
    namespace UI
    {
        class Field : public Line
        {
            private:
                std::string total_input;
                std::size_t length;
            public:
                Field(Line _line = Line(),
                    std::string start_input = "",
                    std::size_t _length = 15);
                ~Field(void) = default;
                void set_string(std::string) override;
                std::string get_string(void) override;
        };
    } // namespace UI
} // namespace arcade
