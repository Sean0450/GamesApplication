#include <gtest/gtest.h>
#include "Game.h"

TEST(GameTest, ConstructorAndGetters) {
    Game game("Test Game", "Adventure", 2023, 4.5);
    
    EXPECT_EQ(game.getName(), "Test Game");
    EXPECT_EQ(game.getGenre(), "Adventure");
    EXPECT_EQ(game.getReleaseYear(), 2023);
    EXPECT_DOUBLE_EQ(game.getRating(), 4.5);
}

TEST(GameTest, Setters) {
    Game game("", "", 0, 0.0);
    
    game.setName("New Name");
    game.setGenre("RPG");
    game.setReleaseYear(2022);
    game.setRating(4.8);
    
    EXPECT_EQ(game.getName(), "New Name");
    EXPECT_EQ(game.getGenre(), "RPG");
    EXPECT_EQ(game.getReleaseYear(), 2022);
    EXPECT_DOUBLE_EQ(game.getRating(), 4.8);
}

TEST(GameTest, RatingValidation) {
    Game game("Game", "Genre", 2023, 3.0);
    
    EXPECT_THROW(game.setRating(-1.0), std::invalid_argument);
    EXPECT_THROW(game.setRating(5.1), std::invalid_argument);
    EXPECT_NO_THROW(game.setRating(0.0));
    EXPECT_NO_THROW(game.setRating(5.0));
}
TEST(GameTest, ConstructorValidation) {
    EXPECT_NO_THROW(Game("Valid Name", "Genre", 1970, 0.0));
    EXPECT_NO_THROW(Game("Valid Name", "Genre", 2023, 5.0));
    
    EXPECT_THROW(Game("", "Genre", 2023, 4.5), std::invalid_argument); // Пустое имя
    EXPECT_THROW(Game("Name", "", 2023, 4.5), std::invalid_argument); // Пустой жанр
    EXPECT_THROW(Game("Name", "Genre", 1969, 4.5), std::invalid_argument); // Год слишком ранний
    EXPECT_THROW(Game("Name", "Genre", 2023, -0.1), std::invalid_argument); // Рейтинг ниже 0
    EXPECT_THROW(Game("Name", "Genre", 2023, 5.1), std::invalid_argument); // Рейтинг выше 5
}

TEST(GameTest, EqualityOperators) {
    Game game1("Game", "Genre", 2020, 4.5);
    Game game2("Game", "Genre", 2020, 4.5);
    Game game3("Different", "Genre", 2020, 4.5);
    
    EXPECT_TRUE(game1 == game2);
    EXPECT_FALSE(game1 == game3);
    EXPECT_FALSE(game1 != game2);
    EXPECT_TRUE(game1 != game3);
}

TEST(GameTest, OutputOperator) {
    Game game("Test Game", "Adventure", 2023, 4.5);
    std::ostringstream oss;
    oss << game;
    
    std::string expected = "Game: Test Game, Genre: Adventure, Year: 2023, Rating: 4.5";
    EXPECT_EQ(oss.str(), expected);
}

TEST(GameTest, CopyAndMoveSemantics) {
    Game original("Original", "Genre", 2020, 4.0);
    
    Game copy = original;
    EXPECT_EQ(copy, original);
    
    Game temp("Temp", "Genre", 2021, 4.1);
    Game moved = std::move(temp);
    EXPECT_EQ(moved, Game("Temp", "Genre", 2021, 4.1));
    EXPECT_EQ(temp.getName(), ""); // Проверка состояния после перемещения
}