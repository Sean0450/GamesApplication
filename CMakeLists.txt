cmake_minimum_required(VERSION 3.14)
project(GamesApplicationTests)

set(CMAKE_CXX_STANDARD 17)

# Подключаем Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

# Добавляем основной проект для тестирования
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../src ../src_build)

# Создаем исполняемый файл для тестов
add_executable(
  GamesApplicationTests
  GameTest.cpp
  GameLibraryTest.cpp
  UserTest.cpp
)

# Подключаем Google Test
target_link_libraries(
  GamesApplicationTests
  GTest::GTest
  GTest::Main
  GamesApplication
)

include(GoogleTest)
gtest_discover_tests(GamesApplicationTests)