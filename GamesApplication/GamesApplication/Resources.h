#pragma once

#include <string>

namespace resources
{
struct GamesNames
{
  static constexpr auto ticTacToe{"TicTacToe"};
  static constexpr auto tags{"Tags"};
  static constexpr auto sudoku{"Sudoku"};
};
constexpr auto applicationTitle = "BEST PROJECT IN THE WORLD";
constexpr auto startGame = "Start game";
constexpr auto dialogeTitle = "Input player name Dialoge";
constexpr auto firstPlayerQuestion = "Enter player Name:";
constexpr auto secondPlayerQuestion = "Enter second player Name:";
constexpr auto gameInformation = "Game information";
constexpr auto isWinner = " is winner!";
constexpr auto pressToRestart = "Press to restart the game";
constexpr auto yourScore = "Your score: ";
constexpr auto mistakesCount = "Mistakes count: ";
} // namespace resources
