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
    m_mainLayout->removeWidget(m_area);
    m_area->deleteLater();
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
    case GamesTypes::Sudoku:
      m_area = new QTableWidget(9, 9, this);
      m_activeGame = GamesTypes::Sudoku;
      CreateArea(9);
      break;
  }
  m_area->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  m_area->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  if (m_activeGame != GamesTypes::Sudoku)
  {
    m_area->verticalHeader()->setVisible(false);
    m_area->horizontalHeader()->setVisible(false);
  }
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
      //button->setFlat(true);
      m_area->setCellWidget(rows, columns, button);
      m_buttons.emplace_back(button);
      QObject::connect(button, &QPushButton::clicked, this, &GameArea::TicTacToeButtonClicked);
    }
  }
}

void GameArea::TicTacToeButtonClicked()
{
  if (auto observer = m_observer.lock())
  {
    auto index = std::distance(m_buttons.begin(), std::ranges::find(m_buttons, sender()));
    auto stepResult = observer->SendData(index, std::nullopt);
    if (stepResult.has_value())
    {
      m_buttons[index]->setText(stepResult == 1 ? "X" : "O");
      m_buttons[index]->setFont(QFont("Arial", 20, QFont::Bold));
    }
  }
}

void GameArea::TagsButtonClicked()
{
}

void GameArea::ShipBattleButtonClicked()
{
}


void GameArea::Restart()
{
  switch (m_activeGame)
  {
    case GamesTypes::TicTacToe:
      std::ranges::for_each(m_buttons,
                            [&](auto * button)
                            {
                              button->setEnabled(true);
                              button->setText("");
                            });
      break;
    case GamesTypes::Tags:
      break;
    case GamesTypes::Sudoku:
      break;
  }
}

void GameArea::BlockGameArea()
{
  std::ranges::for_each(m_buttons, [&](auto * button) { button->setEnabled(false); });
}
