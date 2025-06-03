#include "View.h"

View::View(QWidget * parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);
  this->setWindowTitle("BEST PROJECT IN THE WORLD");

  m_gameSwitcher = new GameSwitcher(this);
  m_gameArea = new GameArea(this);
  m_mainLayout = new QHBoxLayout(ui.centralWidget);
  auto gamesLayout = new QVBoxLayout(ui.centralWidget);
  gamesLayout->addWidget(m_gameArea);
  auto switcherLayout = new QVBoxLayout(ui.centralWidget);
  switcherLayout->addWidget(m_gameSwitcher);
  m_panelLayout = new QVBoxLayout(this);
  m_mainLayout->addLayout(m_panelLayout);
  m_mainLayout->addLayout(gamesLayout);
  m_mainLayout->addLayout(switcherLayout);
}

void View::ConstructGameArea(GamesTypes gameType)
{
  m_gameArea->ConstructGameArea(gameType);
  if (m_gamePanel != nullptr)
  {
    m_gamePanel->deleteLater();
  }
  switch (gameType)
  {
    case GamesTypes::TicTacToe:
      m_gamePanel = new TicTacToePanel(this); 
      break;
    case GamesTypes::Tags:
      break;
    case GamesTypes::ShipsBattle:
      std::cout << "N";
  }
  m_panelLayout->addWidget(m_gamePanel);
}

GameSwitcher * View::GetGameSwitcher() const
{
  return m_gameSwitcher;
}

GameArea * View::GetGameArea() const
{
  return m_gameArea;
}
