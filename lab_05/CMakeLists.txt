cmake_minimum_required(VERSION 3.12)

project(lab_05)

# Стандарт C++ 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Флаги
set(${CXX_FLAGS} "${CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic -fsanitize=address -fsanitize=undefined")

# Для библиотек
include_directories(${PROJECT_SOURCE_DIR}/include)

# Для библиотек
include_directories(${PROJECT_SOURCE_DIR}/src)

# Добавляем исполняемый файл
add_executable(${PROJECT_NAME}_exe main.cpp)

# Для исполняемых файлов
set_target_properties(${PROJECT_NAME}_exe PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Добавляем Google Tests
enable_testing()
add_executable(tests_lab_05 test/tests05.cpp)
target_link_libraries(tests_lab_05 gtest gmock)
add_test(NAME Lab05Tests COMMAND tests_lab_05)


# Для тестов
set_target_properties(tests_lab_05 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)



