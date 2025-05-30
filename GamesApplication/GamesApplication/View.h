#pragma once

#include <QtWidgets/QMainWindow>

#include "GameArea.h"
#include "GameSwitcher.h"
#include "ui_GamesApplication.h"

class View : public QMainWindow
{
  Q_OBJECT
  GameSwitcher * m_gameSwitcher = nullptr;
  GameArea * m_gameArea = nullptr;

public:
  View(QWidget * parent = nullptr);
  GameSwitcher * GetGameSwitcher() const;
  GameArea * GetGameArea() const;
  ~View() = default;

private:
  Ui::GamesApplicationClass ui;
};
