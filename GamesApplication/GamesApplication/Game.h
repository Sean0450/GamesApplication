#pragma once

class Game
{
public:
  virtual ~Game() = default;
  virtual void Step() = 0;
};
