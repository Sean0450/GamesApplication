#include <gtest/gtest.h>
#include "GameLibrary.h"
#include "Game.h"

class GameLibraryTest : public ::testing::Test {
protected:
    void SetUp() override {
        library.addGame(Game("Game 1", "Action", 2020, 4.5));
        library.addGame(Game("Game 2", "RPG", 2021, 4.7));
    }
    
    GameLibrary library;
};

TEST_F(GameLibraryTest, AddGame) {
    EXPECT_EQ(library.getGames().size(), 2);
    
    library.addGame(Game("Game 3", "Adventure", 2022, 4.3));
    EXPECT_EQ(library.getGames().size(), 3);
}

TEST_F(GameLibraryTest, RemoveGame) {
    EXPECT_TRUE(library.removeGame("Game 1"));
    EXPECT_EQ(library.getGames().size(), 1);
    EXPECT_FALSE(library.removeGame("Non-existent Game"));
}

TEST_F(GameLibraryTest, FindGameByName) {
    auto game = library.findGameByName("Game 2");
    ASSERT_NE(game, nullptr);
    EXPECT_EQ(game->getName(), "Game 2");
    
    game = library.findGameByName("Non-existent Game");
    EXPECT_EQ(game, nullptr);
}

TEST_F(GameLibraryTest, FindGamesByGenre) {
    auto games = library.findGamesByGenre("RPG");
    ASSERT_EQ(games.size(), 1);
    EXPECT_EQ(games[0].getName(), "Game 2");
    
    games = library.findGamesByGenre("Non-existent Genre");
    EXPECT_TRUE(games.empty());
}
TEST_F(GameLibraryTest, AddDuplicateGame) {
    EXPECT_THROW(library.addGame(Game("Game 1", "Action", 2020, 4.5)), std::invalid_argument);
    EXPECT_EQ(library.getGames().size(), 3);
}

TEST_F(GameLibraryTest, FindGamesByYearRange) {
    auto games = library.findGamesByYearRange(2020, 2021);
    ASSERT_EQ(games.size(), 2);
    EXPECT_EQ(games[0].getName(), "Game 1");
    EXPECT_EQ(games[1].getName(), "Game 2");
    
    games = library.findGamesByYearRange(2023, 2025);
    EXPECT_TRUE(games.empty());
}

TEST_F(GameLibraryTest, FindGamesByRatingRange) {
    auto games = library.findGamesByRatingRange(4.5, 5.0);
    ASSERT_EQ(games.size(), 2);
    EXPECT_EQ(games[0].getName(), "Game 1");
    EXPECT_EQ(games[1].getName(), "Game 2");
    
    games = library.findGamesByRatingRange(4.8, 5.0);
    EXPECT_EQ(games.size(), 1);
    EXPECT_EQ(games[0].getName(), "Game 2");
}

TEST_F(GameLibraryTest, UpdateGame) {
    EXPECT_TRUE(library.updateGame("Game 1", Game("Updated Game", "Adventure", 2023, 4.8)));
    
    auto game = library.findGameByName("Updated Game");
    ASSERT_NE(game, nullptr);
    EXPECT_EQ(game->getGenre(), "Adventure");
    
    EXPECT_FALSE(library.updateGame("Non-existent", Game("", "", 0, 0.0)));
}

TEST_F(GameLibraryTest, GetTopRatedGames) {
    auto topGames = library.getTopRatedGames(2);
    ASSERT_EQ(topGames.size(), 2);
    EXPECT_EQ(topGames[0].getName(), "Game 2");
    EXPECT_EQ(topGames[1].getName(), "Game 1");
    
    topGames = library.getTopRatedGames(10);
    EXPECT_EQ(topGames.size(), 3);
}

TEST_F(GameLibraryTest, GetGameCountByGenre) {
    auto counts = library.getGameCountByGenre();
    ASSERT_EQ(counts.size(), 2);
    EXPECT_EQ(counts["Action"], 2);
    EXPECT_EQ(counts["RPG"], 1);
}

TEST_F(GameLibraryTest, Serialization) {
    std::string filename = "test_library.dat";
    
    EXPECT_NO_THROW(library.saveToFile(filename));
    
    GameLibrary loadedLibrary;
    EXPECT_NO_THROW(loadedLibrary.loadFromFile(filename));
    EXPECT_EQ(loadedLibrary.getGames().size(), 3);
    
    EXPECT_THROW(loadedLibrary.loadFromFile("non_existent_file.dat"), std::runtime_error);
    
    remove(filename.c_str());
}