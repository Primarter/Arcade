if [ -z "$1" ]
    then
        echo "No arguments supplied"
        exit 84
fi

echo "Adding $1...";

echo "Creating $1.hpp...";
echo "/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** $1.hpp
*/

#pragma once
#include \"IGameModule.hpp\"

extern \"C\" arcade::IGameModule *entryPoint();
namespace arcade
{
    class $1 : public IGameModule
    {
        public:
            $1(void) = default;
            ~$1(void) = default;
            void init(void) override;
            void stop(void) override;
            const std::string &getName(void) const override;
            const std::vector<GameObject> &update(std::vector<Input::Key>) override;
            bool is_over(void) const override;
            int get_score(void) const override;
        private:
            bool close = false;
            std::vector<GameObject> objects;
            std::string _name = \"$1\";
    };
}" > include/libs/$1.hpp;

echo "Creating $1/lib.cpp...";
mkdir src/games/$1
echo "/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** $1.cpp
*/

#include \"games/$1.hpp\"

extern \"C\" arcade::IGameModule *entryPoint(void)
{
    return new arcade::$1(\"$1\");
}

namespace arcade
{
    void $1::init(void)
    {
        std::cout << \"[$1] init\" << std::endl;
    }

    void $1::stop(void)
    {
        std::cout << \"[$1] stop\" << std::endl;
        this->close = false;
    }

    int $1::get_score(void) const
    {
        return random() % 500;
    }

    const std::string &$1::getName(void) const
    {
        return this->_name;
    }

    const std::vector<GameObject> &$1::update(std::vector<Input::Key> input)
    {
        if (input.size() == 1 && (input[0] == Input::Escape || input[0] == Input::Closed)) {
            std::cout << \"GAME RECEIVED CLOSED INPUT\" << std::endl;
            this->close = true;
        }

        this->objects.clear();

        Rectangle rect(Vector2(50, 50));
        rect.color = Color(0xFF00FF);
        this->objects.push_back(rect);

        Circle circ(30);
        circ.color = Color(0, 255, 100);
        circ.position = Vector2(50, 50);
        this->objects.push_back(circ);

        Text tex(this->name);
        tex.color = Color(0xFFFFFF);
        this->objects.push_back(tex);

        Line ln(Vector2(500, 500));
        ln.position = Vector2(50, 400);
        ln.color = Color(100, 0, 255);
        this->objects.push_back(ln);

        return this->objects;
    }

    bool $1::is_over(void) const
    {
        return this->close;
    }
} // namespace arcade" > src/$1/lib.cpp;

echo "adding $1 to CMakeLists.txt...";
echo "

##############################
# $1 game
##############################
add_library($1 SHARED
    src/user_tools/GameObject.cpp
    src/games/$1/$1_game.cpp
)
set_target_properties($1 PROPERTIES
PUBLIC_HEADER include/$1.hpp
ARCHIVE_OUTPUT_DIRECTORY \"../lib/\"
LIBRARY_OUTPUT_DIRECTORY \"../lib/\"
PREFIX \"arcade_\"
)
target_include_directories($1 PRIVATE ./include/)
" >> ./CMakeLists.txt;

echo "Done!";