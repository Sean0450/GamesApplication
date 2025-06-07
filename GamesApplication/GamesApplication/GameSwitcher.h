#pragma once

#include <iostream>
#include <QtWidgets>

#include "GameSwitcherObserver.h"
#include "Resources.h"


class GameSwitcher : public QWidget
{
  Q_OBJECT
  std::weak_ptr<GameSwitcherObserver> m_observer;
  QPushButton * m_restartGame = nullptr;
  QComboBox * m_gamesList = nullptr;
  QPushButton * m_chooseGame = nullptr;

private slots:
  void ChooseGameButtonClicked();
  void RestartButtonClicked();

public:
  GameSwitcher(QWidget * parent = nullptr);
  void SetObserver(std::weak_ptr<GameSwitcherObserver> observer);
};
