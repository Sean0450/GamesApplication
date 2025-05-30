#pragma once

#include <optional>

struct GameAreaObserver
{
  virtual ~GameAreaObserver() = default;
  virtual void SendData(int x, int y, const std::optional<int> optionalCell) = 0;
};
