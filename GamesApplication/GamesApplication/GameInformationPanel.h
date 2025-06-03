#pragma once

#include <iostream>
#include <QtWidgets>
#include <string>

#include "GameInformationPanelObserver.h"


class GameInformationPanel : public QWidget
{
  Q_OBJECT
protected:
  std::weak_ptr<GameInformationPanelObserver> m_observer;

public:
  GameInformationPanel(QWidget * parent = nullptr){};
  virtual ~GameInformationPanel() = default;
  virtual void SendPlayersNames() = 0;
  virtual void GetData() = 0; //TODO TYPE!
  void SetObserver(std::weak_ptr<GameInformationPanelObserver> observer) { m_observer = std::move(observer); } // Общая реализация для всех наследников
};
