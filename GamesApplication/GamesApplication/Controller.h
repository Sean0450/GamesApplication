#pragma once

#include <iostream>
#include <string>

#include "DataModel.h"
#include "Game.h"
#include "GameAreaObserver.h"
#include "GameInformationPanelObserver.h"
#include "GameSwitcherObserver.h"
#include "View.h"

class Controller : public GameSwitcherObserver,
                   public GameAreaObserver,
                   public GameInformationPanelObserver
{
  struct Private
  {
    explicit Private() = default;
  };
  std::shared_ptr<View> m_view;
  std::unique_ptr<Game> m_activeGame;
  DataModel m_dataModel;

public:
  Controller(Private priv, std::shared_ptr<View> view);
  static std::shared_ptr<Controller> Create(std::shared_ptr<View> view);
  void SendChoosenGame(const std::string & currentGame) override;
  void SendData(char x, char y, const std::optional<char> & optionalCell) override;
  void SendPlayersNames(std::string_view firstPlayer, std::string_view secondPlayer) override;
};
