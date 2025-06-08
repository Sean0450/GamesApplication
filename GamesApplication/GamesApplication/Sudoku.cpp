#include "Sudoku.h"


Sudoku::Sudoku()
{
  BaseAreaShuffle();
}

std::optional<uint8_t> Sudoku::Step(uint8_t cellIndex, const std::optional<uint8_t> & optionalCell)
{
  uint8_t row = cellIndex / 9;
  uint8_t column = cellIndex - row * 9;
  if (m_baseArea[row][column] == optionalCell.value())
  {
    m_userArea[row][column] = optionalCell.value();
    m_score += 100 - m_mistakesCounter * 50;
    return 1;
  }
  m_mistakesCounter++;
  return std::nullopt;
}

void Sudoku::SetName(const std::string & playerName)
{
  m_name = playerName;
}

const std::string Sudoku::GetWinnerInformation()
{
  for (auto & row : m_userArea)
  {
    if (std::ranges::find(row, 0) != row.end())
    {
      return {};
    }
  }
  return m_name + ":" + std::to_string(m_score) + ":" + std::to_string(m_mistakesCounter);
}

void Sudoku::RestartGame()
{
  for (auto & row : m_userArea)
  {
    std::ranges::for_each(row, [&](auto & element) { element = 0; });
  }
  m_mistakesCounter = 0;
  m_score = 0;
  BaseAreaShuffle();
}

void Sudoku::TransposeArea()
{
  for (uint8_t row = 0; row < 9; ++row)
  {
    for (uint8_t column = row; column < 9; ++column)
    {
      std::swap(m_baseArea[row][column], m_baseArea[column][row]);
    }
  }
}

void Sudoku::RowsSwapper(uint8_t rowIndex)
{
  if (rowIndex < 6)
  {
    std::swap(m_baseArea[rowIndex], m_baseArea[CalculateSwappingIndex(rowIndex)]);
  }
  else
  {
    std::swap(m_baseArea[rowIndex == 6 ? rowIndex + 1 : rowIndex - 1], m_baseArea[rowIndex]);
  }
}

void Sudoku::ColumnsSwapper(uint8_t columnIndex)
{
  if (columnIndex < 6)
  {
    auto swappingIndex = CalculateSwappingIndex(columnIndex);
    for (uint8_t i = 0; i < 9; ++i)
    {
      std::swap(m_baseArea[i][columnIndex], m_baseArea[i][swappingIndex]);
    }
  }
  else
  {
    for (uint8_t i = 0; i < 9; ++i)
    {
      std::swap(m_baseArea[i][columnIndex == 6 ? columnIndex + 1 : columnIndex - 1], m_baseArea[i][columnIndex]);
    }
  }
}

std::array<std::array<uint8_t, 9>, 9> Sudoku::GetUserArea() const
{
  return m_userArea;
}

uint8_t Sudoku::CalculateSwappingIndex(uint8_t index) const
{
  if (index < 3)
  {
    return index == 0 ? index + 1 : index - 1;
  }
  else
  {
    return index == 3 ? index + 2 : index - 1;
  }
}

void Sudoku::ConstructUserArea()
{
  m_userArea = m_baseArea;
  uint8_t difficultyCounter = 0; //This variable shows how many numbers wiil be removed from table
  std::mt19937 gen(m_dev());
  std::uniform_int_distribution<> number(0, 8);
  while (difficultyCounter != m_difficultyBarrier)
  {
    uint8_t rowIndex = number(gen);
    uint8_t columnIndex = number(gen);
    if (m_userArea[rowIndex][columnIndex] != 0)
    {
      m_userArea[rowIndex][columnIndex] = 0;
      difficultyCounter++;
    }
  }
}

void Sudoku::BaseAreaShuffle()
{
  //Try to make random base matrix construction
  std::mt19937 gen(m_dev());
  std::uniform_int_distribution<> number(0, 8);
  if (number(gen) % 2 == 0)
  {
    TransposeArea();
  }
  for (uint8_t i = 0; i < 15; i++)
  {
    RowsSwapper(number(gen));
    ColumnsSwapper(number(gen));
  }
  ConstructUserArea();
}
