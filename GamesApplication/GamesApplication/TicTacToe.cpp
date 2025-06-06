#include "TicTacToe.h"

std::optional<uint8_t> TicTacToe::Step(uint8_t cellIndex, const std::optional<uint8_t> & optionalCell)
{
  if (m_gameArea[cellIndex] != 1 and m_gameArea[cellIndex] != 0)
  {
    m_gameArea[cellIndex] = m_activeSymbol;
    std::swap(m_firstPlayerData.second, m_secondPlayerData.second);
    if (m_activeSymbol == 1)
    {
      m_activeSymbol = 0;
    }
    else
    {
      m_activeSymbol = 1;
    }
  }
  return m_activeSymbol == 1 ? 0 : 1;
}

void TicTacToe::SetName(const std::string & playerName)
{
  if (m_firstPlayerData.first.empty())
  {
    m_firstPlayerData.first = playerName;
    m_firstPlayerData.second = true;
  }
  else if (m_secondPlayerData.first.empty())
  {
    m_secondPlayerData.first = playerName;
    m_secondPlayerData.second = false;
  }
}

bool TicTacToe::CheckWinner() const
{
  for (auto & wc : m_winningCombos)
  {
    if (m_gameArea[wc.m_first] == m_gameArea[wc.m_second] and m_gameArea[wc.m_first] == m_gameArea[wc.m_third] and
        m_gameArea[wc.m_first] != -1)
    {
      return true;
    }
  }
  return false;
}

const std::string & TicTacToe::GetWinnerInformation()
{
  if (CheckWinner())
  {
    if (m_firstPlayerData.second)
    {
      dialoges::outputDialoge(m_secondPlayerData.first); //std::swap() in Step function calls earliaer so I have to use reverse data
      return m_secondPlayerData.first;
    }
    dialoges::outputDialoge(m_firstPlayerData.first);
    return m_firstPlayerData.first;
  }
  return {};
}
