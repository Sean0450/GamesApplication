#pragma once

#include <random>
#include <algorithm>
#include <string>

#include "FieldedAreaGame.h"

class Sudoku : public FieldedAreaGame
{
  std::string m_name;
  uint16_t m_score = 0;
  uint8_t m_mistakesCounter = 0;
  std::random_device m_dev;
  static constexpr uint8_t m_difficultyBarrier = 51;
  std::array<std::array<uint8_t, 9>, 9> m_baseArea = {
    std::array<uint8_t, 9>{1, 2, 3, 4, 5, 6, 7, 8, 9},
    {4, 5, 6, 7, 8, 9, 1, 2, 3},
    {7, 8, 9, 1, 2, 3, 4, 5, 6},
    {2, 3, 4, 5, 6, 7, 8, 9, 1},
    {5, 6, 7, 8, 9, 1, 2, 3, 4},
    {8, 9, 1, 2, 3, 4, 5, 6, 7},
    {3, 4, 5, 6, 7, 8, 9, 1, 2},
    {6, 7, 8, 9, 1, 2, 3, 4, 5},
    {9, 1, 2, 3, 4, 5, 6, 7, 8},
  };
  std::array<std::array<uint8_t, 9>, 9> m_userArea;
  void TransposeArea();
  void RowsSwapper(uint8_t rowIndex);
  void ColumnsSwapper(uint8_t columnIndex);
  uint8_t CalculateSwappingIndex(uint8_t index) const;
  void ConstructUserArea();
  void BaseAreaShuffle();

public:
  Sudoku();
  std::optional<uint8_t> Step(uint8_t cellIndex, const std::optional<uint8_t> & optionalCell) override;
  void SetName(const std::string & playerName) override;
  std::string GetWinnerInformation() override;
  void RestartGame() override;
  std::vector<uint8_t> GetUserArea() const override;
};
