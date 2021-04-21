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
#include \"IGraphicalLibrary.hpp\"

extern \"C\" void *entryPoint();
namespace arcade
{
    class $1 : public IGraphicalLibrary
    {
        public:
            $1(std::string name);
            ~$1();
            void init() override;
            void stop() override;
            const std::string &getName() const override;
            void draw(GameObject &entity) override;
            std::string get_input(void) override;
            void display(void) override;
        private:
            std::string name;
    };
}" > include/libs/$1.hpp;

echo "Creating $1/lib.cpp...";
mkdir src/libs/$1
echo "/*
** EPITECH PROJECT, 2020
** B-OOP-400-MPL-4-1-arcade-alec.ferrari
** File description:
** $1.cpp
*/

#include \"libs/$1.hpp\"
#include <iostream>

extern \"C\" void *entryPoint()
{
    std::cout << \"[$1] $1 load\" << std::endl;
    return new arcade::$1(\"$1\");
}
namespace arcade
{
    $1::$1(std::string name): name(name) {std::cout << \"[$1] Loading lib\" << std::endl;}
    $1::~$1() {std::cout << \"[$1] Destroying lib\" << std::endl;}

    void $1::init(void) {std::cout << \"[$1] $1 init\" << std::endl;}
    void $1::stop(void) {std::cout << \"[$1] $1 stop\" << std::endl;}
    void $1::draw(GameObject &entity) {}
    std::string $1::get_input(void) { return false; }
    void $1::display(void) {}

    const std::string &$1::getName() const { return this->name; }
}" > src/libs/$1/$1.cpp;

echo "adding $1 to CMakeLists.txt...";
echo "

##############################
# $1 library
##############################
add_library($1 SHARED src/$1/lib.cpp)
set_target_properties($1 PROPERTIES
PUBLIC_HEADER include/$1.hpp
ARCHIVE_OUTPUT_DIRECTORY \"../lib/\"
LIBRARY_OUTPUT_DIRECTORY \"../lib/\"
PREFIX \"arcade_\"
)
target_include_directories($1 PRIVATE ./include/)
# target_link_libraries($1 PUBLIC link_flags)
" >> ./CMakeLists.txt;

echo "Done!";