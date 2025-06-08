#pragma once

#include <algorithm>

#include "Game.h"


struct WinningCombo
{
  uint8_t m_first;
  uint8_t m_second;
  uint8_t m_third;
  constexpr WinningCombo(uint8_t first, uint8_t second, uint8_t third)
    : m_first(first)
    , m_second(second)
    , m_third(third)
  {
  }
};

class TicTacToe : public Game
{
  std::pair<std::string, bool> m_firstPlayerData;
  std::pair<std::string, bool> m_secondPlayerData;
  std::array<char, 9> m_gameArea{-1, -1, -1, -1, -1, -1, -1, -1, -1};
  char m_activeSymbol = 1;
  static constexpr std::array<WinningCombo, 8> m_winningCombos{WinningCombo{0, 1, 2}, WinningCombo{3, 4, 5},
                                                               WinningCombo{6, 7, 8}, WinningCombo{0, 3, 6},
                                                               WinningCombo{1, 4, 7}, WinningCombo{2, 5, 8},
                                                               WinningCombo{0, 4, 8}, WinningCombo{2, 4, 6}};
  bool CheckWinner() const;

public:
  std::optional<uint8_t> Step(uint8_t cellIndex, const std::optional<uint8_t> & optionalCell) override;
  void SetName(const std::string & playerName) override;
  const std::string GetWinnerInformation() override;
  void RestartGame() override;
};
