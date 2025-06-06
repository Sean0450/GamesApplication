#pragma once

#include <iostream>
#include <QtWidgets>
#include <string>

#include "GameInformationPanelObserver.h"
#include "GameArea.h"
#include "Resources.h"

class GameInformationPanel : public QWidget
{
  Q_OBJECT
  std::weak_ptr<GameInformationPanelObserver> m_observer;
  QLabel * m_firstPlayerData = nullptr;
  QLabel * m_secondPlayerData = nullptr;
  GamesTypes m_currentGame;

public:
  GameInformationPanel(QWidget * parent = nullptr);
  void SendPlayerName(const std::string & labelText);
  void ConstructGamePanel(GamesTypes gameType);
  void SetObserver(std::weak_ptr<GameInformationPanelObserver> observer);
  void UpdateStatistics(const std::string & playerStatistics);
};
