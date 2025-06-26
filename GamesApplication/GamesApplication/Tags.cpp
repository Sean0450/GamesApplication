#include "Tags.h"

Tags::Tags()
{
  BaseAreaShuffle();
}

std::optional<uint8_t> Tags::Step(uint8_t cellIndex, const std::optional<uint8_t> & optionalCell)
{
  m_stepsCount++;
  if (cellIndex % 4 != 0 and m_gameArea[cellIndex - 1] == 0)
  {
    std::swap(m_gameArea[cellIndex], m_gameArea[cellIndex - 1]);
    return cellIndex - 1;
  }
  if (cellIndex < 15 and m_gameArea[cellIndex + 1] == 0)
  {
    if (cellIndex != 3 and cellIndex != 7 and cellIndex != 11 and cellIndex != 15)
    {
      std::swap(m_gameArea[cellIndex], m_gameArea[cellIndex + 1]);
      return cellIndex + 1;
    }
    return std::nullopt;
  }
  if (cellIndex < 12 and m_gameArea[cellIndex + 4] == 0)
  {
    std::swap(m_gameArea[cellIndex], m_gameArea[cellIndex + 4]);
    return cellIndex + 4;
  }
  if (cellIndex > 3 and m_gameArea[cellIndex - 4] == 0)
  {
    std::swap(m_gameArea[cellIndex], m_gameArea[cellIndex - 4]);
    return cellIndex - 4;
  }
  return std::nullopt;
}

void Tags::SetName(const std::string & playerName)
{
  m_playerName = playerName;
}

std::string Tags::GetWinnerInformation()
{
  if (m_gameArea == m_checker)
  {
    return m_playerName + ":" + std::to_string(m_stepsCount);
  }
  return {};
}

std::vector<uint8_t> Tags::GetUserArea() const
{
  std::vector<uint8_t> userArea(16);
  std::ranges::copy(m_gameArea, userArea.begin());
  return userArea;
}

void Tags::RestartGame()
{
  m_stepsCount = 0;
  BaseAreaShuffle();
}

void Tags::BaseAreaShuffle()
{
  std::random_device dev;
  std::mt19937 generator(dev());
  std::ranges::shuffle(m_gameArea, dev);
}
