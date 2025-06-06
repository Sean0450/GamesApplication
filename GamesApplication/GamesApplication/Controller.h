#pragma once

#include <iostream>
#include <string>

#include "DataModel.h"
#include "TicTacToe.h"
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
  std::optional<uint8_t> SendData(uint8_t cellIndex, const std::optional<uint8_t> & optionalCell) override;
  void SendPlayerName(const std::string & playerName) override;
};
