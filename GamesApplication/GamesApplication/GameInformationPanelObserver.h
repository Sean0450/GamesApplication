#pragma once

class GameInformationPanelObserver
{
public:
  virtual ~GameInformationPanelObserver() = default;
  virtual void SendPlayerName(const std::string & playerName) = 0;
};
