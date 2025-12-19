cmake_minimum_required(VERSION 3.30)
project(BridgeBotTelegram)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
    tgbot-cpp
    GIT_REPOSITORY https://github.com/reo7sp/tgbot-cpp
    GIT_TAG master
    FIND_PACKAGE_ARGS NAMES tgbot-cpp
)

FetchContent_MakeAvailable(tgbot-cpp)

add_executable(tgbot src/main.cpp)

if(TARGET TgBot::TgBot)
    target_link_libraries(tgbot PRIVATE TgBot::TgBot)
else()
    target_link_libraries(tgbot PRIVATE TgBot)
endif()
