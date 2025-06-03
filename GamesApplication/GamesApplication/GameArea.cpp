#include "GameArea.h"

GameArea::GameArea(QWidget * parent)
  : QWidget(parent)
{
  m_mainLayout = new QVBoxLayout(this);
}

void GameArea::ConstructGameArea(GamesTypes gameType)
{
  if (m_area != nullptr)
  {
    m_area->deleteLater();
    m_mainLayout->removeWidget(m_area);
  }
  switch (gameType)
  {
    case GamesTypes::TicTacToe:
      m_area = new QTableWidget(3, 3, this);
      m_activeGame = GamesTypes::TicTacToe;
      CreateArea(3);
      break;
    case GamesTypes::Tags:
      m_area = new QTableWidget(4, 4, this);
      m_activeGame = GamesTypes::Tags;
      CreateArea(4);
      break;
    case GamesTypes::ShipsBattle:
      m_area = new QTableWidget(10, 10, this);
      m_activeGame = GamesTypes::ShipsBattle;
      CreateArea(10);
      break;
  }
  m_area->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  m_area->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  m_area->verticalHeader()->setVisible(false);
  m_area->horizontalHeader()->setVisible(false);
  m_mainLayout->addWidget(m_area);
}

void GameArea::SetObserver(std::weak_ptr<GameAreaObserver> observer)
{
  m_observer = std::move(observer);
}

void GameArea::CreateArea(uint8_t size)
{
  m_buttons.clear();
  m_buttons.reserve(size * size);
  for (uint8_t rows = 0; rows < size; ++rows)
  {
    for (uint8_t columns = 0; columns < size; ++columns)
    {
      auto * button = new QPushButton(this);
      button->setFlat(true);
      m_area->setCellWidget(rows, columns, button);
      m_buttons.emplace_back(button);
      switch (m_activeGame)
      {
        case GamesTypes::TicTacToe:
          QObject::connect(button, &QPushButton::clicked, this, &GameArea::TicTacToeButtonClicked);
          break;
        case GamesTypes::Tags:
          QObject::connect(button, &QPushButton::clicked, this, &GameArea::TagsButtonClicked);
          break;
        case GamesTypes::ShipsBattle:
          QObject::connect(button, &QPushButton::clicked, this, &GameArea::ShipBattleButtonClicked);
      }
    }
  }
}

void GameArea::TicTacToeButtonClicked()
{
  auto index = std::distance(m_buttons.begin(), std::ranges::find(m_buttons, sender()));
  int row = index / 3;
  if (auto observer = m_observer.lock())
  {
    observer->SendData(row, index - 3 * row, std::nullopt);
    //Set Icon
  }
}

void GameArea::TagsButtonClicked()
{
}

void GameArea::ShipBattleButtonClicked()
{
}
