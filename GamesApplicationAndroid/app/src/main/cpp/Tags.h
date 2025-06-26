#pragma once

#include <algorithm>
#include <random>
#include <string>

#include "FieldedAreaGame.h"

class Tags : public FieldedAreaGame
{
  std::array<uint8_t, 16> m_gameArea = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
  std::array<uint8_t, 16> m_checker = m_gameArea;
  std::string m_playerName;
  uint16_t m_stepsCount = 0;
  void BaseAreaShuffle();
  
public:
  Tags();
  std::optional<uint8_t> Step(uint8_t cellIndex, const std::optional<uint8_t> & optionalCell) override;
  void SetName(const std::string & playerName) override;
  std::string GetWinnerInformation() override;
  void RestartGame() override;
  std::vector<uint8_t> GetUserArea() const override;
};
