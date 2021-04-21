/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** centipede.cpp
*/

#include "games/centipede.hpp"

extern "C" arcade::IGameModule *entryPoint(void)
{
    return new arcade::Centipede("Centipede");
}

void clamp(float &x, float min, float max)
{
    if (x < min) {
        x = min;
    } else if (x > max) {
        x = max;
    }
}

static int randint(int min, int max)
{
    return (rand() % (max-min)) + min;
}

namespace arcade
{
    Centipede::Centipede(std::string _name):
        name(_name)
    {}

    int Centipede::get_score(void) const
    {
        return _score;
    }

    void Centipede::init()
    {
        std::cout << "CENTIPEDE INIT" << std::endl;
        game_start();
    }

    void Centipede::stop()
    {
        std::cout << "CENTIPEDE STOP" << std::endl;
        this->close = false;

        this->objects.clear();
        _centipedes.clear();
        _centipedes_spawner.clear();
    }

    const std::string &Centipede::getName() const
    {
        return this->name;
    }

    const std::vector<GameObject> &Centipede::update(std::vector<Input::Key> input)
    {

        if (input.size() == 1 && (input[0] == Input::Escape || input[0] == Input::Closed)) {
            std::cout << "GAME RECEIVED CLOSED INPUT" << std::endl;
            this->close = true;
        }

        if (_game_over == true) {
            if (std::find(input.begin(), input.end(), Input::Key::R) != input.end()) {
                game_start();
            }
        }

        if (!_game_over) {
            // player
            if (std::find(input.begin(), input.end(), Input::Key::Z) != input.end())
                _player.y -= _speed;
            if (std::find(input.begin(), input.end(), Input::Key::S) != input.end())
                _player.y += _speed;
            if (std::find(input.begin(), input.end(), Input::Key::Q) != input.end())
                _player.x -= _speed;
            if (std::find(input.begin(), input.end(), Input::Key::D) != input.end())
                _player.x += _speed;

            clamp(_player.y, _min_player_height, 700 - _player_dim.y);
            clamp(_player.x, 0, 700 - _player_dim.x);

            _time_next_centipede -= 1;
            if (_time_next_centipede <= 0) {
                _time_next_centipede = randint(60*16, 60*30);
                spawn_centipede(
                    randint(0, _grid_width-1),
                    randint(8, 14),
                    rand() % 2
                );
            }

            next_tick -= 1;
            if (next_tick <= 0) {
                next_tick = 6;

                // spawn centipedes
                for (auto it = _centipedes_spawner.begin(); it != _centipedes_spawner.end(); ) {
                    it->count -= 1;

                    _centipedes.push_back( Centi(it->x, 0, it->dir) );

                    if ( it->count <= 0) {
                        it = _centipedes_spawner.erase(it);
                    } else {
                         ++it;
                    }
                }


                // centipedes
                for (auto it = _centipedes.begin(); it != _centipedes.end(); ) {
                    const int x = it->x;
                    const int y = it->y;
                    const int dir = it->dir;

                    if ( (x == 0 && dir == Direction::LEFT) ||
                         (x == _grid_width-1 && dir == Direction::RIGHT) ) {

                        it->y += 1;
                        it->dir = 1 - dir;

                    } else {


                        if ( (dir == Direction::RIGHT && _boxes[y][x + 1] > 0) ||
                             (dir == Direction::LEFT && _boxes[y][x - 1] > 0) ) {

                            it->y += 1;
                            it->dir = 1 - dir;
                        } else {

                            // step
                            if ( dir == Direction::LEFT ) {
                                it->x -= 1;
                            } else {
                                it->x += 1;
                            }
                        }
                    }

                    int ppx = _player.x / _dx;
                    int ppy = _player.y / _dy;
                    if (it->x == ppx && it->y == ppy) {
                        game_over();
                    }

                    if ( it->y > _grid_height-1 ) {
                        _centipedes.erase(it);
                        _score -= 100;
                    } else {
                         ++it;
                    }

                }
            }

            // projectile
            if (!_projectile_alive) {
                if (std::find(input.begin(), input.end(), Input::Key::Space) != input.end())
                    fire();
            } else { // if alive

                _projectile.y -= 17.0;
                if (_projectile.y < 0)
                    _projectile_alive = false;

                int ppx = _projectile.x / _dx;
                int ppy = _projectile.y / _dy;

                // if hit
                if (_boxes[ppy][ppx] > 0) {
                    _boxes[ppy][ppx] -= 1;
                    _projectile_alive = false;
                    _score += 5;
                } else {

                    // check hit against centipede
                    for (auto it = _centipedes.begin(); it != _centipedes.end(); ++it) {
                        if (ppx == it->x && ppy == it->y) {
                            _centipedes.erase(it);
                            _projectile_alive = false;
                            _boxes[ppy][ppx] = 5;
                            _score += 100;
                            break;
                        }
                    }
                }
            }
        }

        // draw
        this->objects.clear();

        // projectile
        if (_projectile_alive) {
            Line pj({_projectile.x, _projectile.y - 15});
            pj.position = _projectile;
            pj.color = Color(255, 0, 0);
            this->objects.push_back(pj);
        }

        // player
        Rectangle player({_player_dim.x, _player_dim.y});
        player.position = _player;
        player.color = Color(0xFF00FF);
        this->objects.push_back(player);

        draw_boxes();
        draw_centipedes();
        draw_score();

        if (_game_over) {
            Rectangle mask({700, 700});
            mask.position = Vector2(0.f, 0.f);
            mask.color = Color(0, 0, 0, 200);
            this->objects.push_back(mask);

            std::string txt("Press R to retry");
            Text text(txt);
            text.position = Vector2(_grid_width * 0.5f * _dx - 70 , _grid_height *_dy *0.5f);
            text.color = Color(255, 255, 255);
            this->objects.push_back(text);
        }

        return this->objects;
    }

    bool Centipede::is_over(void) const
    {
        return this->close;
    }

    void Centipede::fire()
    {
        _projectile = Vector2(_player.x + _player_dim.x*0.5, _player.y);
        _projectile_alive = true;
    }

    void Centipede::add_box(int x, int y)
    {
        if (x < 0 || x > _grid_width || y < 0 || y > _grid_height || _boxes[y][x] > 0)
            return;

        _boxes[y][x] = 5;
    }

    void Centipede::spawn_centipede(int x, int length, int direction)
    {
        if (x < 0 || x > _grid_width-1 || length < 1)
            return;

        _centipedes_spawner.push_back( Centi_spawner(x, length, direction) );
    }

    void Centipede::draw_boxes()
    {
        for (int y = 0 ; y < 30 ; ++y) {
            for (int x = 0 ; x < 30 ; ++x) {
                if (_boxes[y][x] > 0) {
                    Rectangle b({_box_size, _box_size});
                    b.position = Vector2(x * _dx, y * _dy);
                    b.color = Color(255-(_boxes[y][x]*51), _boxes[y][x]*51, 0);
                    this->objects.push_back(b);
                }
            }
        }
    }

    void Centipede::draw_centipedes()
    {
        for (auto const& cen: _centipedes) {
            Circle circ(_box_size * 0.5f);
            float x = cen.x * _dx;
            float y = cen.y * _dy;

            // circle for ncurses
            circ.color = Color(255, 0, 100, 0);
            circ.position = Vector2(x, y);
            this->objects.push_back(circ);

            if (cen.dir == LEFT) {
                Sprite sp("./resources/images/centipede_body_left.png");
                sp.position = Vector2(x, y);
                this->objects.push_back(sp);
            } else {
                Sprite sp("./resources/images/centipede_body_right.png");
                sp.position = Vector2(x, y);
                this->objects.push_back(sp);
            }
        }
    }

    void Centipede::draw_score()
    {
        std::string score = std::to_string(_score);
        Text tex(score);
        int offset = (24 * score.length()) * 0.25f;
        tex.position = Vector2(_grid_width * 0.5f *_dx - offset , 0);
        tex.color = Color(255, 255, 255);
        this->objects.push_back(tex);
    }

    void Centipede::game_start()
    {
        this->objects.clear();
        _boxes.clear();
        _centipedes.clear();
        _centipedes_spawner.clear();

        _player = Vector2(350, 600);
        _player_dim = Vector2(15, 15);
        _projectile_alive = false;

        _boxes.resize(30);
        for (int i = 0 ; i < _grid_width ; ++i) {
            _boxes[i].assign(_grid_width, 0);
        }
        for (int i = 0 ; i < 20 ; ++i) {
            int x = rand() % _grid_width;
            int y = rand() % (_grid_height-1);

            add_box(x, y);
        }

        _score = 0;
        _centipede_left = 20;
        _time_next_centipede = 60;
        _game_over = false;
    }

    void Centipede::game_over()
    {
        _game_over = true;
    }

} // namespace arcade
