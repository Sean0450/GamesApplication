#pragma once

#include <iostream>
#include <string>

#include "GameSwitcherObserver.h"
#include "View.h"
#include "DataModel.h"
#include "GameAreaObserver.h"

class Controller : public GameSwitcherObserver, public GameAreaObserver
{
  struct Private
  {
    explicit Private() = default;
  };
  std::shared_ptr<View> m_view;
  DataModel m_dataModel;

public:
  Controller(Private priv, std::shared_ptr<View> view);
  static std::shared_ptr<Controller> Create(std::shared_ptr<View> view);
  void SendChoosenGame(const std::string & currentGame) override;
  void SendData(int x, int y, const std::optional<int> optionalCell) override;
};
