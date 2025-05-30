#pragma once

struct GameSwitcherObserver
{
  virtual ~GameSwitcherObserver() = default;
  virtual void SendChoosenGame(const std::string & currentGame) = 0;
};
