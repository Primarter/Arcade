cmake_minimum_required(VERSION 3.9)
project(arcade DESCRIPTION "arcade executable and libraries")

##############################
# arcade executable
##############################
set(SRC_FILES
    ./src/main.cpp
    ./src/DLLoader.cpp
    ./src/core/Core.cpp
    ./src/core/core_init.cpp
    ./src/core/core_scores.cpp
    ./src/core/Stopwatch.cpp
    ./src/user_tools/GameObject.cpp
)
add_executable(arcade ${SRC_FILES})
target_include_directories(arcade PRIVATE include/)
set_target_properties(arcade PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../"
)
target_compile_options(arcade PRIVATE -std=c++17 -g3 -W -Wall -Wextra)
target_link_libraries(arcade PRIVATE -ldl)

##############################
# menu library
##############################
add_library(menu SHARED
    ./src/menu/Line.cpp
    ./src/menu/Field.cpp
    ./src/menu/Table.cpp
    ./src/menu/Menu.cpp
    ./src/menu/draw_menu.cpp
    ./src/menu/handle_menu_event.cpp
)
target_include_directories(menu PRIVATE include/)
set_target_properties(menu PROPERTIES
PUBLIC_HEADER include/menu.hpp
ARCHIVE_OUTPUT_DIRECTORY "../"
LIBRARY_OUTPUT_DIRECTORY "../"
PREFIX ""
)
target_compile_options(menu PRIVATE -std=c++17 -g3 -W -Wall -Wextra)
target_link_libraries(menu PUBLIC -ldl -lsfml-graphics -lsfml-window -lsfml-system)

##############################
# sfml library
##############################
add_library(sfml SHARED
    src/libs/sfml/lib.cpp
    src/user_tools/GameObject.cpp
)
set_target_properties(sfml PROPERTIES
PUBLIC_HEADER include/sfml.hpp
ARCHIVE_OUTPUT_DIRECTORY "../lib/"
LIBRARY_OUTPUT_DIRECTORY "../lib/"
PREFIX "arcade_"
)
target_include_directories(sfml PRIVATE ./include/)
target_link_libraries(sfml PUBLIC -lsfml-graphics -lsfml-window -lsfml-system)



##############################
# sdl2 library
##############################
find_package(SDL2 REQUIRED)
add_library(sdl2 SHARED
    src/libs/sdl2/lib.cpp
    src/user_tools/GameObject.cpp
)
set_target_properties(sdl2 PROPERTIES
PUBLIC_HEADER include/sdl2.hpp
ARCHIVE_OUTPUT_DIRECTORY "../lib/"
LIBRARY_OUTPUT_DIRECTORY "../lib/"
PREFIX "arcade_"
)
set(SDL2_LIBRARIES ${SDL2_LIBRARIES} -lSDL2_ttf -lSDL2_image)
target_include_directories(sdl2 PRIVATE ./include/ ${SDL2_INCLUDE_DIRS})
target_link_libraries(sdl2 ${SDL2_LIBRARIES})



##############################
# ncurses library
##############################
add_library(ncurses SHARED
    src/user_tools/GameObject.cpp
    src/libs/ncurses/lib.cpp
    src/libs/ncurses/draw_functions.cpp
)
set_target_properties(ncurses PROPERTIES
PUBLIC_HEADER include/NCurses.hpp
ARCHIVE_OUTPUT_DIRECTORY "../lib/"
LIBRARY_OUTPUT_DIRECTORY "../lib/"
PREFIX "arcade_"
)
target_include_directories(ncurses PRIVATE ./include/)
target_link_libraries(ncurses -lncurses)

##############################
# test_game game
##############################
# add_library(test_game SHARED
#     src/user_tools/GameObject.cpp
#     src/games/test/test_game.cpp
# )
# set_target_properties(test_game PROPERTIES
# PUBLIC_HEADER include/test_game.hpp
# ARCHIVE_OUTPUT_DIRECTORY "../lib/"
# LIBRARY_OUTPUT_DIRECTORY "../lib/"
# PREFIX "arcade_"
# )
# target_include_directories(test_game PRIVATE ./include/)

##############################
# centipede game
##############################
add_library(centipede SHARED
    src/user_tools/GameObject.cpp
    src/games/centipede.cpp
)
set_target_properties(centipede PROPERTIES
PUBLIC_HEADER include/centipede.hpp
ARCHIVE_OUTPUT_DIRECTORY "../lib/"
LIBRARY_OUTPUT_DIRECTORY "../lib/"
PREFIX "arcade_"
)
target_include_directories(centipede PRIVATE ./include/)


##############################
# Qix game
##############################
# add_library(Qix SHARED
#     src/user_tools/GameObject.cpp
#     src/games/Qix/qix_game.cpp
# )
# set_target_properties(Qix PROPERTIES
# PUBLIC_HEADER include/Qix.hpp
# ARCHIVE_OUTPUT_DIRECTORY "../lib/"
# LIBRARY_OUTPUT_DIRECTORY "../lib/"
# PREFIX "arcade_"
# )
# target_include_directories(Qix PRIVATE ./include/)


##############################
# nibbler game
##############################
add_library(nibbler SHARED
    src/user_tools/GameObject.cpp
    src/games/nibbler/nibbler_game.cpp
)
set_target_properties(nibbler PROPERTIES
PUBLIC_HEADER include/nibbler.hpp
ARCHIVE_OUTPUT_DIRECTORY "../lib/"
LIBRARY_OUTPUT_DIRECTORY "../lib/"
PREFIX "arcade_"
)
target_include_directories(nibbler PRIVATE ./include/)



##############################
# pong game
##############################
add_library(pong SHARED
    src/user_tools/GameObject.cpp
    src/games/pong/pong_game.cpp
)
set_target_properties(pong PROPERTIES
PUBLIC_HEADER include/pong.hpp
ARCHIVE_OUTPUT_DIRECTORY "../lib/"
LIBRARY_OUTPUT_DIRECTORY "../lib/"
PREFIX "arcade_"
)
target_include_directories(pong PRIVATE ./include/)

