#include "View.h"

View::View(QWidget * parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);
  this->setWindowTitle(resources::applicationTitle);
  m_gameSwitcher = new GameSwitcher(this);
  m_gameArea = new GameArea(this);
  m_gamePanel = new GameInformationPanel(this);
  m_mainLayout = new QHBoxLayout(ui.centralWidget);
  auto gamesLayout = new QVBoxLayout(ui.centralWidget);
  gamesLayout->addWidget(m_gameArea);
  auto switcherLayout = new QVBoxLayout(ui.centralWidget);
  switcherLayout->addWidget(m_gameSwitcher);
  m_panelLayout = new QVBoxLayout(this);
  m_panelLayout->addWidget(m_gamePanel);
  m_mainLayout->addLayout(m_panelLayout);
  m_mainLayout->addLayout(gamesLayout);
  m_mainLayout->addLayout(switcherLayout);
}

void View::ConstructGameArea(GamesTypes gameType)
{
  m_gameArea->ConstructGameArea(gameType);
  m_gamePanel->ConstructGamePanel(gameType);
}

GameSwitcher * View::GetGameSwitcher() const
{
  return m_gameSwitcher;
}

GameArea * View::GetGameArea() const
{
  return m_gameArea;
}

GameInformationPanel * View::GetInformationPanel() const
{
  return m_gamePanel;
}
