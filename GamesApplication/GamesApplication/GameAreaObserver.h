#pragma once

#include <optional>

struct GameAreaObserver
{
  virtual ~GameAreaObserver() = default;
  virtual std::optional<uint8_t> SendData(uint8_t cellIndex, const std::optional<uint8_t> & optionalCell) = 0;
};
