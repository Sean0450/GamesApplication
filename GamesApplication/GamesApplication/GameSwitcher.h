#pragma once

#include <iostream>
#include <QtWidgets>

#include "GameSwitcherObserver.h"
#include "Resources.h"


class GameSwitcher : public QWidget
{
  Q_OBJECT
  std::weak_ptr<GameSwitcherObserver> m_observer;
  QComboBox * m_gamesList = nullptr;
  QPushButton * m_chooseGame = nullptr;

private slots:
  void ChooseGameButtonClicked();

public:
  GameSwitcher(QWidget * parent = nullptr);
  void SetObserver(std::weak_ptr<GameSwitcherObserver> observer);
};
