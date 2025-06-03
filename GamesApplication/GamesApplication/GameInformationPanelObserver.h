#pragma once

class GameInformationPanelObserver
{
public:
  virtual ~GameInformationPanelObserver() = default;
  virtual void SendPlayersNames(std::string_view firstPlayer, std::string_view secondPlayer) = 0;
};
