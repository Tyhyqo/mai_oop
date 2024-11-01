cmake_minimum_required(VERSION 3.10)

project(lab_02)

# Стандарт C++ 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем библиотеку
add_library(${PROJECT_NAME}_lib src/thirteen.cpp)

# Добавляем исполняемый файл
add_executable(${PROJECT_NAME}_exe main.cpp)
target_link_libraries(${PROJECT_NAME}_exe PRIVATE ${PROJECT_NAME}_lib)

# Для исполняемых файлов
set_target_properties(${PROJECT_NAME}_exe PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Добавляем Google Tests
enable_testing()
add_executable(tests_lab_02 test/tests02.cpp)
target_link_libraries(tests_lab_02 ${PROJECT_NAME}_lib gtest gmock)
add_test(NAME Lab02Tests COMMAND tests_lab_02)


# Для тестов
set_target_properties(tests_lab_02 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)