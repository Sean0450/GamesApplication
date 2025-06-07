#pragma once

#include <string_view>
#include <optional>

class Game
{

public:
  virtual ~Game() = default;
  virtual std::optional<uint8_t> Step(uint8_t cellIndex, const std::optional<uint8_t> & optionalCell) = 0;
  virtual void SetName(const std::string & playerName) = 0;
  virtual const std::string & GetWinnerInformation() = 0;
  virtual void RestartGame() = 0;
};
