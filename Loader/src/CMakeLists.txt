cmake_minimum_required(VERSION 3.22)

add_executable(${PROJECT_NAME} ./main.cpp)


target_sources(${PROJECT_NAME}
        PRIVATE
        main.cpp
        riff_reader.cpp
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ../include
)
