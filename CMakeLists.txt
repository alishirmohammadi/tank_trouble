cmake_minimum_required(VERSION 3.0)
project(alter_tank C)
set(alter_tank 99)

file(GLOB_RECURSE SOURCE "src/*.c" "src/*.h")
add_executable(alter_tank "${SOURCE}" src/tank.c src/tank.h src/map.c src/map.h src/graphics.c src/graphics.h src/physics.c src/physics.h src/keyboard_handler.c src/keyboard_handler.h src/colors.c src/colors.h src/bullet.c src/bullet.h src/structs.c src/structs.h src/manager.c src/manager.h)

include_directories("/usr/include/SDL2")
target_link_libraries(alter_tank m SDL2 SDL2_gfx)
