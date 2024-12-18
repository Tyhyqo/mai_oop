cmake_minimum_required(VERSION 3.12)

project(lab_07)

# Стандарт C++ 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Флаги
set(${CXX_FLAGS} "${CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic -fsanitize=address -fsanitize=undefined")

# Для библиотек
include_directories(${PROJECT_SOURCE_DIR}/include)

# Для библиотек
include_directories(${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Добавляем исполняемый файл
add_executable(${PROJECT_NAME}_exe main.cpp ${SOURCES})

# Для исполняемых файлов
set_target_properties(${PROJECT_NAME}_exe PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
