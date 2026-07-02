cmake_minimum_required(VERSION 3.26)
project(dream_generator)

set(CMAKE_CXX_STANDARD 23)

add_executable(dream_generator main.cpp
        Dream/Dream.cpp
        Dream/Nightmare/Nightmare.cpp
        Dream/Nightmare/ChaseNightmare/ChaseNightmare.cpp
        Dream/Nightmare/TrappedNightmare/TrappedNightmare.cpp
        Dream/Dream.h
        Dream/Nightmare/Nightmare.h
        Dream/Nightmare/ChaseNightmare/ChaseNightmare.h
        Dream/Nightmare/TrappedNightmare/TrappedNightmare.h
        Dream/Nightmare/TrappedNightmare/TemplateLoader.h
        Dream/Nightmare/TrappedNightmare/TemplateLoader.cpp
        Dream/LucidDream/LucidDream.cpp
        Dream/LucidDream/LucidDream.h
        Dream/LucidDream/PeacefulLucidDream/PeacefulLucidDream.cpp
        Dream/LucidDream/PeacefulLucidDream/PeacefulLucidDream.h
        Dream/LucidDream/RecursiveLucidDream/RecursiveLucidDream.cpp
        Dream/LucidDream/RecursiveLucidDream/RecursiveLucidDream.h
        TemplateLoader/TemplateLoader.cpp
        TemplateLoader/TemplateLoader.h
)
