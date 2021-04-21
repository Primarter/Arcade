/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** centipede.hpp
*/

#pragma once

#include "IGameModule.hpp"

extern "C" arcade::IGameModule *entryPoint();

struct Box
{
    Box(int _x = 0, int _y = 0): x(_x), y(_y), life(3) {};
    ~Box(void) = default;

    int x, y;
    int life;
};

enum Direction {
    LEFT = 0,
    RIGHT = 1,
};

struct Centi_spawner
{
    Centi_spawner(int _x, int _count = 0, int _dir = LEFT): x(_x), count(_count), dir(_dir) {}
    ~Centi_spawner(void) = default;

    int x;
    int count;
    int dir;
};

struct Centi
{
    Centi(int _x = 0, int _y = 0, int _dir = LEFT): x(_x), y(_y), dir(_dir) {}
    ~Centi(void) = default;

    int x, y;
    int dir;
};

template<typename T>
using vector2D = std::vector<std::vector<T>>;

namespace arcade
{
    class Centipede : public IGameModule
    {
        public:
            Centipede(std::string name);
            ~Centipede() = default;
            void init() override;
            void stop() override;
            const std::string &getName() const override;
            const std::vector<GameObject> &update(std::vector<Input::Key>) override;
            bool is_over(void) const override;
            int get_score(void) const override;
        private:
            bool close = false;
            std::vector<GameObject> objects;
            std::string name;

            int _score;
            int _highscore;
            bool _game_over;

            const int _min_player_height = 700 * 0.7;
            const float _speed = 4.5;
            const int _grid_width = 30;
            const int _grid_height = 30;
            const int _dx = 700 / _grid_width;
            const int _dy = 700 / _grid_height;
            const float _box_size = 700.f / _grid_width;

            int _centipede_left;
            int _time_next_centipede;

            Vector2 _player;
            Vector2 _player_dim;

            Vector2 _projectile;
            bool _projectile_alive;

            vector2D<int8_t> _boxes;

            std::vector<Centi_spawner> _centipedes_spawner;
            std::vector<Centi> _centipedes;
            int next_tick = 10;

            void fire();
            void add_box(int x, int y);
            void game_start();
            void game_over();
            void spawn_centipede(int x, int length, int direction);
            void draw_boxes();
            void draw_centipedes();
            void draw_score();
    };
}
