/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** Field.cpp
*/

#include "menu/Field.hpp"

namespace arcade
{
    namespace UI
    {
        Field::Field(Line _line,
                std::string _start_input,
                std::size_t _length):
            Line(_line), total_input(_start_input), length(_length)
        {
            _start_input[_length - 1] = 0;
            this->text.setString(_start_input);
        }

        std::string Field::get_string(void)
        {
            return this->total_input;
        }

        void Field::set_string(std::string s)
        {
            this->total_input = s;
            this->text.setString(
                s.substr(0, this->length - 1)
                + (s.size() > this->length ? "..." : "")
            );
        }
    } // namespace UI
} // namespace arcade
