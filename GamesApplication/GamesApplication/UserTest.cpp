#include <gtest/gtest.h>
#include "User.h"

TEST(UserTest, ConstructorAndGetters) {
    User user("testuser", "password123", "user@example.com");
    
    EXPECT_EQ(user.getUsername(), "testuser");
    EXPECT_EQ(user.getEmail(), "user@example.com");
    EXPECT_TRUE(user.checkPassword("password123"));
    EXPECT_FALSE(user.checkPassword("wrongpassword"));
}

TEST(UserTest, Setters) {
    User user("", "", "");
    
    user.setUsername("newuser");
    user.setEmail("new@example.com");
    user.setPassword("newpassword");
    
    EXPECT_EQ(user.getUsername(), "newuser");
    EXPECT_EQ(user.getEmail(), "new@example.com");
    EXPECT_TRUE(user.checkPassword("newpassword"));
}

TEST(UserTest, PasswordHashing) {
    User user("user", "password", "email@example.com");
    
    EXPECT_NE(user.getPassword(), "password");
    EXPECT_TRUE(user.checkPassword("password"));
}
TEST(UserTest, ConstructorValidation) {
    EXPECT_NO_THROW(User("validuser", "password123", "valid@email.com"));
    
    EXPECT_THROW(User("", "password", "email@test.com"), std::invalid_argument); // Пустой username
    EXPECT_THROW(User("user", "", "email@test.com"), std::invalid_argument); // Пустой пароль
    EXPECT_THROW(User("user", "password", "invalid-email"), std::invalid_argument); // Невалидный email
}

TEST(UserTest, FavoriteGamesOperations) {
    User user("user", "pass", "email@test.com");
    Game game1("Game 1", "Action", 2020, 4.5);
    Game game2("Game 2", "RPG", 2021, 4.7);
    
    user.addToFavorites(game1);
    user.addToFavorites(game2);
    EXPECT_EQ(user.getFavorites().size(), 2);
    
    EXPECT_THROW(user.addToFavorites(game1), std::invalid_argument);
    
    EXPECT_TRUE(user.removeFromFavorites("Game 1"));
    EXPECT_EQ(user.getFavorites().size(), 1);
    EXPECT_FALSE(user.removeFromFavorites("Non-existent Game"));
    
    EXPECT_TRUE(user.hasInFavorites("Game 2"));
    EXPECT_FALSE(user.hasInFavorites("Game 1"));
}

TEST(UserTest, PasswordRequirements) {
    EXPECT_NO_THROW(User("user", "ValidPass123", "email@test.com"));
    EXPECT_THROW(User("user", "short", "email@test.com"), std::invalid_argument);
    EXPECT_THROW(User("user", "noDigitsHere", "email@test.com"), std::invalid_argument);
}

TEST(UserTest, EmailChangeValidation) {
    User user("user", "pass", "old@email.com");
    
    EXPECT_NO_THROW(user.setEmail("new@email.com"));
    EXPECT_EQ(user.getEmail(), "new@email.com");
    
    EXPECT_THROW(user.setEmail("invalid-email"), std::invalid_argument);
    EXPECT_EQ(user.getEmail(), "new@email.com");
}

TEST(UserTest, Serialization) {
    User user("testuser", "password123", "user@example.com");
    user.addToFavorites(Game("Favorite Game", "Genre", 2023, 4.5));
    
    std::string filename = "test_user.dat";
    
    EXPECT_NO_THROW(user.saveToFile(filename));
    
    User loadedUser;
    EXPECT_NO_THROW(loadedUser.loadFromFile(filename));
    EXPECT_EQ(loadedUser.getUsername(), "testuser");
    EXPECT_EQ(loadedUser.getFavorites().size(), 1);
    
    EXPECT_THROW(loadedUser.loadFromFile("non_existent_file.dat"), std::runtime_error);
    
    remove(filename.c_str());
}