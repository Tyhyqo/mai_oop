cmake_minimum_required(VERSION 3.12)

project(lab_06)

# Стандарт C++ 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Флаги
set(${CXX_FLAGS} "${CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic -fsanitize=address -fsanitize=undefined")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Для библиотек
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Создаем библиотеку из исходников
add_library(${PROJECT_NAME}_lib STATIC ${SOURCES})

# Добавляем исполняемый файл
add_executable(${PROJECT_NAME}_exe main.cpp)
target_link_libraries(${PROJECT_NAME}_exe ${PROJECT_NAME}_lib)

# Для исполняемых файлов
set_target_properties(${PROJECT_NAME}_exe PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Добавляем Google Tests
enable_testing()
add_executable(tests_lab_06 test/tests06.cpp)
target_link_libraries(tests_lab_06 ${PROJECT_NAME}_lib GTest::GTest GTest::Main)
add_test(NAME Lab06Tests COMMAND tests_lab_06)


# Для тестов
set_target_properties(tests_lab_06 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)
