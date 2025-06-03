#pragma once

#include <optional>

struct GameAreaObserver
{
  virtual ~GameAreaObserver() = default;
  virtual void SendData(char x, char y, const std::optional<char> & optionalCell) = 0;
};
