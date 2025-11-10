cmake_minimum_required(VERSION 3.22)

message(STATUS "IS_WIN32_APP=${IS_WIN32_APP}")

if(IS_WIN32_APP)
    add_executable(${PROJECT_NAME} WIN32 ./main.cpp)
    target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32_APP)
else ()
    add_executable(${PROJECT_NAME} ./main.cpp)
endif()


target_sources(${PROJECT_NAME}
        PRIVATE
        main.cpp
        application.cpp
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ../include
)
