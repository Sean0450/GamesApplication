#pragma once

#include <QtWidgets/QMainWindow>

#include "GameArea.h"
#include "GameInformationPanel.h"
#include "GameSwitcher.h"
#include "ui_GamesApplication.h"

class View : public QMainWindow
{
  Q_OBJECT
  GameSwitcher * m_gameSwitcher = nullptr;
  GameArea * m_gameArea = nullptr;
  GameInformationPanel * m_gamePanel = nullptr;
  QHBoxLayout * m_mainLayout = nullptr;
  QVBoxLayout * m_panelLayout = nullptr;

public:
  View(QWidget * parent = nullptr);
  GameSwitcher * GetGameSwitcher() const;
  GameArea * GetGameArea() const;
  GameInformationPanel * GetInformationPanel() const;
  void ConstructGameArea(GamesTypes gameType);
  ~View() = default;

private:
  Ui::GamesApplicationClass ui;
};
