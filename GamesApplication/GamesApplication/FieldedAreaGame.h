#pragma once

#include <vector>

#include "Game.h"

class FieldedAreaGame : public Game
{
public:
  virtual ~FieldedAreaGame() = default;
  virtual std::optional<uint8_t> Step(uint8_t cellIndex, const std::optional<uint8_t> & optionalCell) = 0;
  virtual void SetName(const std::string & playerName) = 0;
  virtual std::string GetWinnerInformation() = 0;
  virtual void RestartGame() = 0;
  virtual std ::vector<uint8_t> GetUserArea() const = 0;
};
