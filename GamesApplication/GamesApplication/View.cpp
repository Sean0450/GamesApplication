#include "View.h"

View::View(QWidget * parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);
  this->setWindowTitle("BEST PROJECT IN THE WORLD");

  m_gameSwitcher = new GameSwitcher(this);
  m_gameArea = new GameArea(this);
  auto mainLayout = new QHBoxLayout(ui.centralWidget);
  auto gamesLayout = new QVBoxLayout(ui.centralWidget);
  gamesLayout->addWidget(m_gameArea);
  auto switcherLayout = new QVBoxLayout(ui.centralWidget);
  switcherLayout->addWidget(m_gameSwitcher);
  mainLayout->addLayout(gamesLayout);
  mainLayout->addLayout(switcherLayout);
}

GameSwitcher * View::GetGameSwitcher() const
{
  return m_gameSwitcher;
}

GameArea * View::GetGameArea() const
{
  return m_gameArea;
}
