/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** core_scores.cpp
*/

#include "core/Core.hpp"
#include <fstream>
#include <iostream>
#include <regex>

namespace arcade
{

    void Core::get_scores(void)
    {
        std::string line;
        std::ifstream file("./resources/scores/" + this->curr_game()->getName());
        std::regex reg("(\\w+): (\\d+)");

        this->scores.clear();
        if (file.is_open()) {
            for(int i = 0; i < 5 && getline(file, line); i++) {
                std::smatch m;
                if (!std::regex_search(line, m, reg)) {
                    this->scores.clear();
                    break;
                }
                this->scores.insert({-std::atoi(m[2].str().c_str()), m[1]});
            }
            file.close();
        } else {
            this->scores.clear();
        }
    }

    void Core::add_score(int score)
    {
        this->scores.insert(std::make_pair(score, this->name));
    }

    void Core::write_scores(void)
    {
        std::ofstream file;
        int idx = 0;

        file.open("./resources/scores/" + this->curr_game()->getName(), std::ios::out | std::ios::trunc);
        for (auto it : this->scores) {
            if (idx >= 5)
                break;
            file << it.second << ": " << -it.first << std::endl;
            idx++;
        }
    }

    std::vector<std::string> Core::get_scores_strings(void)
    {
        std::vector<std::string> vec;
        int idx = 0;

        for (auto it : this->scores) {
            if (idx >= 5)
                break;
            vec.push_back(it.second + ": " + std::to_string(-it.first));
            idx++;
        }
        return vec;
    }
} // namespace arcade
