#include "GameSwitcher.h"

#include <span>
GameSwitcher::GameSwitcher(QWidget * parent)
  : QWidget(parent)
{
  m_restartGame = new QPushButton(this);
  m_restartGame->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));
  m_restartGame->setToolTip(resources::pressToRestart);
  QObject::connect(m_restartGame, &QPushButton::clicked, this, &GameSwitcher::RestartButtonClicked);

  m_gamesList = new QComboBox(this);
  m_gamesList->addItem(resources::GamesNames::ticTacToe);
  m_gamesList->addItem(resources::GamesNames::tags);
  m_gamesList->addItem(resources::GamesNames::sudoku);

  m_chooseGame = new QPushButton(this);
  m_chooseGame->setText(resources::startGame);
  QObject::connect(m_chooseGame, &QPushButton::clicked, this, &GameSwitcher::ChooseGameButtonClicked);

  auto vlayout = new QVBoxLayout(this);
  vlayout->addWidget(m_restartGame);
  vlayout->addWidget(m_gamesList);
  vlayout->addWidget(m_chooseGame);
}

void GameSwitcher::ChooseGameButtonClicked()
{
  if (auto observer = m_observer.lock())
  {
    observer->SendChoosenGame(m_gamesList->currentText().toStdString());
  }
}

void GameSwitcher::SetObserver(std::weak_ptr<GameSwitcherObserver> observer)
{
  m_observer = std::move(observer);
}

void GameSwitcher::RestartButtonClicked()
{
  if (auto observer = m_observer.lock())
  {
    observer->RestartGame();
  }
}
