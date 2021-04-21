/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** lib.cpp
*/

#include "libs/sdl2.hpp"
#include <iostream>

extern "C" void *entryPoint()
{
    std::cout << "[sdl2] sdl2 load" << std::endl;
    return new arcade::sdl2("sdl2");
}
namespace arcade {

    static std::map<int, Input::Key> keymap = {
        {SDLK_a, Input::Key::A},
        {SDLK_b, Input::Key::B},
        {SDLK_c, Input::Key::C},
        {SDLK_d, Input::Key::D},
        {SDLK_e, Input::Key::E},
        {SDLK_f, Input::Key::F},
        {SDLK_g, Input::Key::G},
        {SDLK_h, Input::Key::H},
        {SDLK_i, Input::Key::I},
        {SDLK_j, Input::Key::J},
        {SDLK_k, Input::Key::K},
        {SDLK_l, Input::Key::L},
        {SDLK_m, Input::Key::M},
        {SDLK_n, Input::Key::N},
        {SDLK_o, Input::Key::O},
        {SDLK_p, Input::Key::P},
        {SDLK_q, Input::Key::Q},
        {SDLK_r, Input::Key::R},
        {SDLK_s, Input::Key::S},
        {SDLK_t, Input::Key::T},
        {SDLK_u, Input::Key::U},
        {SDLK_v, Input::Key::V},
        {SDLK_w, Input::Key::W},
        {SDLK_x, Input::Key::X},
        {SDLK_y, Input::Key::Y},
        {SDLK_z, Input::Key::Z},
        {SDLK_0, Input::Key::Num0},
        {SDLK_1, Input::Key::Num1},
        {SDLK_2, Input::Key::Num2},
        {SDLK_3, Input::Key::Num3},
        {SDLK_4, Input::Key::Num4},
        {SDLK_5, Input::Key::Num5},
        {SDLK_6, Input::Key::Num6},
        {SDLK_7, Input::Key::Num7},
        {SDLK_8, Input::Key::Num8},
        {SDLK_9, Input::Key::Num9},
        {SDLK_ESCAPE, Input::Key::Escape},
        {SDLK_SPACE, Input::Key::Space},
        {SDLK_KP_ENTER, Input::Key::Enter},
        {SDLK_BACKSPACE, Input::Key::Backspace},
        {SDLK_TAB, Input::Key::Tab},
        {SDLK_UP, Input::Key::Up},
        {SDLK_DOWN, Input::Key::Down},
        {SDLK_LEFT, Input::Key::Left},
        {SDLK_RIGHT, Input::Key::Right},
    };

    sdl2::sdl2(std::string name):
        name(name),
        _draw_func_map({
            { GameObject::ObjectType::CIRCLE, [this](GameObject &obj) { this->draw_circle(obj); } },
            { GameObject::ObjectType::RECTANGLE, [this](GameObject &obj) { this->draw_rectangle(obj); } },
            { GameObject::ObjectType::LINE, [this](GameObject &obj) { this->draw_line(obj); } },
            { GameObject::ObjectType::SPRITE, [this](GameObject &obj) { this->draw_sprite(obj); } },
            { GameObject::ObjectType::TEXT, [this](GameObject &obj) { this->draw_text(obj); } }
        })
    {
        std::cout << "ctor sdl2" << std::endl;
    }

    sdl2::~sdl2()
    {
        std::cout << "dtor sdl2" << std::endl;
    }

    // PUBLIC
    void sdl2::init(void)
    {
        std::cout << "[sdl2] sdl2 init" << std::endl;

        int rendererFlags, windowFlags;
        const int screen_width = 700;
        const int screen_height = 700;

        rendererFlags = SDL_RENDERER_ACCELERATED;
        windowFlags = 0;

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            throw std::runtime_error(std::string("Couldn't initialize SDL: ") + SDL_GetError());
        }
        TTF_Init();

        _window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, windowFlags);
        if (!_window) {
            throw std::runtime_error(std::string("Failed to open window: ") + SDL_GetError());
        }

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        _renderer = SDL_CreateRenderer(_window, -1, rendererFlags);
        if (!_renderer) {
            throw std::runtime_error(std::string("Failed to create renderer: ") + SDL_GetError());
        }

        SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
    }

    void sdl2::stop(void)
    {
        std::cout << "[sdl2] sdl2 stop" << std::endl;

        this->_keys.clear();
        TTF_Quit();
        SDL_Quit();
    }

    void sdl2::draw(GameObject &entity)
    {
        _draw_func_map[entity.type](entity);
    }

    std::vector<Input::Key> sdl2::get_input(void)
    {
        SDL_Event event;

        this->_keys.clear();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    _keys.push_back(Input::Closed);
                    break;
            }
        }

        int numKeys = 0;
        const uint8_t* keystate = SDL_GetKeyboardState(&numKeys);

        //continuous-response keys
        for (const auto& key : keymap) {
            SDL_Scancode scode = SDL_GetScancodeFromKey(key.first);
            if (keystate[scode]) {
                _keys.push_back(key.second);
            }
        }

        return _keys;
    }

    void sdl2::display(void)
    {
        SDL_RenderPresent(_renderer);
    }

    void sdl2::clear(void)
    {
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
        SDL_RenderClear(_renderer);
    }

    const std::string &sdl2::getName() const { return this->name; }

    // PRIVATE
    void sdl2::draw_circle(arcade::GameObject &entity)
    {
        SDL_SetRenderDrawColor(_renderer, entity.color.r, entity.color.g, entity.color.b, entity.color.a);
        for (int w = 0; w < entity.circle_radius * 2; ++w) {
            for (int h = 0; h < entity.circle_radius * 2; ++h) {
                int dx = entity.circle_radius - w; // horizontal offset
                int dy = entity.circle_radius - h; // vertical offset
                if ((dx*dx + dy*dy) + 0.5 <= (entity.circle_radius * entity.circle_radius)) {
                    SDL_RenderDrawPoint(_renderer, entity.position.x + dx, entity.position.y + dy);
                }
            }
        }
    }

    void sdl2::draw_rectangle(arcade::GameObject &entity)
    {
        SDL_Rect rect;
        rect.x=entity.position.x;
        rect.y=entity.position.y;
        rect.w=entity.rect_dimensions.x;
        rect.h=entity.rect_dimensions.y;

        SDL_SetRenderDrawColor(_renderer, entity.color.r, entity.color.g, entity.color.b, entity.color.a);
        SDL_RenderFillRect(_renderer, &rect);
        SDL_RenderDrawRect(_renderer, &rect);
    }

    void sdl2::draw_line(arcade::GameObject &entity)
    {
        SDL_SetRenderDrawColor(_renderer, entity.color.r, entity.color.g, entity.color.b, entity.color.a);
        SDL_RenderDrawLine(_renderer, entity.position.x, entity.position.y, entity.line_end.x, entity.line_end.y);
    }

    void sdl2::draw_sprite(arcade::GameObject &entity)
    {
        SDL_Texture *img = NULL;
        int w = 0;
        int h = 0;

        img = IMG_LoadTexture(_renderer, entity.sprite_src.c_str());
        SDL_QueryTexture(img, NULL, NULL, &w, &h);

        SDL_Rect texr;
        texr.x = entity.position.x;
        texr.y = entity.position.y;
        texr.w = w;
        texr.h = h;

        SDL_RenderCopy(_renderer, img, NULL, &texr);
        SDL_DestroyTexture(img);
    }

    void sdl2::draw_text(arcade::GameObject &entity)
    {
        SDL_Color color = {entity.color.r, entity.color.g, entity.color.b, entity.color.a};
        TTF_Font *font = TTF_OpenFont("./resources/fonts/whitneymedium.otf", 24);
        SDL_Surface *surface = TTF_RenderText_Solid(font, entity.text_string.c_str(), color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);

        int texW = 0;
        int texH = 0;
        int x = entity.position.x;
        int y = entity.position.y;
        SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
        SDL_Rect dstrect = {x, y, texW, texH};

        SDL_RenderCopy(_renderer, texture, NULL, &dstrect);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
    }
}
