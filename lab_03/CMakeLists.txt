cmake_minimum_required(VERSION 3.10)

project(lab_03)

# Стандарт C++ 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Флаги
set(${CXX_FLAGS} "${CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic -fsanitize=address -fsanitize=undefined")

# Находим все исходные файлы в директории src
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Добавляем библиотеку
add_library(${PROJECT_NAME}_lib ${SOURCES})

# Для библиотек
include_directories(${PROJECT_SOURCE_DIR}/include)

# Добавляем исполняемый файл
add_executable(${PROJECT_NAME}_exe main.cpp)
target_link_libraries(${PROJECT_NAME}_exe PRIVATE ${PROJECT_NAME}_lib)

# Для исполняемых файлов
set_target_properties(${PROJECT_NAME}_exe PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Добавляем Google Tests
enable_testing()
add_executable(tests_lab_03 test/tests03.cpp)
target_link_libraries(tests_lab_03 ${PROJECT_NAME}_lib gtest gmock)
add_test(NAME Lab03Tests COMMAND tests_lab_03)


# Для тестов
set_target_properties(tests_lab_03 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)

