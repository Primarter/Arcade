/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** draw_functions.cpp
*/

#include "libs/NCurses.hpp"

namespace arcade
{
    Vector2 get_grid_proj(Vector2 pt)
    {
        pt.x = (int)((pt.x * 70) / 700);
        pt.y = (int)((pt.y * 70) / 700);
        return pt;
    }

    int get_grid_proj(float val)
    {
        return (val * 70) / 700;
    }

    void NCurses::draw_circle(arcade::GameObject &entity)
    {
        Vector2 pos = get_grid_proj(entity.position);
        int rad = get_grid_proj(entity.circle_radius);
        bool printed = false;
        init_color(1, (entity.color.r * 1000) / 255, (entity.color.g * 1000) / 255, (entity.color.b * 1000) / 255);
        init_pair(1, 1, 1);
        wattron(win.get(), COLOR_PAIR(1));

        for (int w = 0; w < rad * 2; ++w) {
            for (int h = 0; h < rad * 2; ++h) {
                int dx = rad - w; // horizontal offset
                int dy = rad - h; // vertical offset
                if ((dx*dx + dy*dy) + 0.5 <= (rad * rad)) {
                    printed = true;
                    mvwprintw(this->win.get(), pos.y + dy + 1, pos.x + dx + 1, "O");
                }
            }
        }
        if (printed == false) {
            mvwprintw(this->win.get(), pos.y + 1, pos.x + 1, "O");
        }
        wattroff(win.get(), COLOR_PAIR(1));
    }

    void NCurses::draw_rectangle(arcade::GameObject &entity)
    {
        Vector2 pos = get_grid_proj(entity.position);
        Vector2 dims = get_grid_proj(entity.rect_dimensions);
        init_color(2, (entity.color.r * 1000) / 255, (entity.color.g * 1000) / 255, (entity.color.b * 1000) / 255);
        init_pair(2, 2, 2);
        wattron(win.get(), COLOR_PAIR(2));
        bool printed = false;

        for (int y = pos.y; y <= pos.y + dims.y && y < 70; y++) {
            for (int x = pos.x; x <= pos.x + dims.x && x < 70; x++) {
                printed = true;
                mvwprintw(this->win.get(), y + 1, x + 1, "#");
            }
        }
        if (!printed) {
            mvwprintw(this->win.get(), pos.y + 1, pos.x + 1, "#");
        }
        wattroff(win.get(), COLOR_PAIR(2));
    }

    void NCurses::draw_line(arcade::GameObject &entity)
    {
        Vector2 pos = entity.position;
        Vector2 end = entity.line_end;
        init_color(3, (entity.color.r * 1000) / 255, (entity.color.g * 1000) / 255, (entity.color.b * 1000) / 255);
        init_pair(3, 3, 3);
        wattron(win.get(), COLOR_PAIR(3));

        if (pos.x == end.x) {
            int start = pos.y < end.y ? pos.y : end.y;
            int stop = pos.y < end.y ? end.y : pos.y;
            for (; start <= stop; start++)
                mvwprintw(this->win.get(), get_grid_proj(start) + 1, get_grid_proj(pos.x) + 1, "#");
            return;
        }

        int start = pos.x < end.x ? pos.x : end.x;
        int stop = pos.x > end.x ? pos.x : end.x;
        unsigned int a = (pos.y - end.y) / (pos.x - end.x);
        unsigned int b = pos.y - a * pos.x;

        for (unsigned int j = 0; start < 700; start++) {
            Vector2 pos = Vector2(start, a * start + b);
            if (a * start + b < 700) {
                mvwprintw(this->win.get(), get_grid_proj(pos.y) + 1, get_grid_proj(pos.x) + 1, "#");
            }
        }
        wattroff(win.get(), COLOR_PAIR(3));
    }

    void NCurses::draw_sprite(arcade::GameObject &entity)
    {
        std::string src = entity.sprite_src + ".txt";
        std::ifstream file(src);
        std::string line;
        Vector2 pos = get_grid_proj(entity.position);

        init_color(5, 1000, 1000, 1000);
        init_pair(5, 5, COLOR_BLACK);
        wattron(win.get(), COLOR_PAIR(5));

        if (file.is_open()) {
            for (; getline(file, line); pos.y++) {
                for (int x = pos.x; x - pos.x < line.size(); x++) {
                    if (line[x - pos.x] != ' ') {
                        std::string tmp = std::string("");
                        tmp.push_back(line[x - pos.x]);
                        mvwprintw(this->win.get(), pos.y + 1, x + 1, tmp.c_str());
                    }
                }
            }
            file.close();
        }

        wattroff(win.get(), COLOR_PAIR(5));
    }

    void NCurses::draw_text(arcade::GameObject &entity)
    {
        Vector2 pos = get_grid_proj(entity.position);
        init_color(4, (entity.color.r * 1000) / 255, (entity.color.g * 1000) / 255, (entity.color.b * 1000) / 255);
        init_pair(4, 4, COLOR_BLACK);
        wattron(win.get(), COLOR_PAIR(4));

        mvwprintw(this->win.get(), pos.y + 1, pos.x + 1, entity.text_string.c_str());
        wattroff(win.get(), COLOR_PAIR(4));
    }
} // namespace arcade
