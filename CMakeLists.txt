cmake_minimum_required(VERSION 3.29)
project(allegro_projet_v1 C)

set(CMAKE_C_STANDARD 11)

add_executable(allegro_projet_v1 main.c
        sauvegarde.c
        sauvegarde.h
        personnage.c
        menu.c
        menu.h
        decor.c
        decor.h)
target_link_libraries(allegro_projet_v1 -lmingw32 -lalleg44)