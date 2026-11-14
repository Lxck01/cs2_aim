cmake_minimum_required(VERSION 3.20)
project(cs2_aim CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cs2_aim
    main.cpp
    memory.cpp
    config.cpp
    aimbot.cpp
)

if (MSVC)
    target_compile_options(cs2_aim PRIVATE /O2 /W3)
    target_compile_definitions(cs2_aim PRIVATE _CRT_SECURE_NO_WARNINGS NOMINMAX)
endif()
