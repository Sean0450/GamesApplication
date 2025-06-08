#include "GameArea.h"

GameArea::GameArea(QWidget * parent)
  : QWidget(parent)
{
  m_mainLayout = new QVBoxLayout(this);
}

void GameArea::ClearGameArea()
{
  if (m_area != nullptr)
  {
    m_mainLayout->removeWidget(m_area);
    m_area->deleteLater();
  }
  if (m_sudokuData.m_numbersLayout != nullptr)
  {
    m_sudokuData.m_numbersLayout->deleteLater();
    std::ranges::for_each(m_sudokuData.m_numbersButtons, [&](auto * button) { button->deleteLater(); });
  }
  repaint();
}

void GameArea::ConstructGameArea(GamesTypes gameType)
{
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
  m_area->verticalHeader()->setVisible(false);
  m_area->horizontalHeader()->setVisible(false);
  m_mainLayout->addWidget(m_area);
  if (m_activeGame == GamesTypes::Sudoku)
  {
    m_sudokuData.m_numbersLayout = new QHBoxLayout(this);
    CreateNumbersTable();
    m_mainLayout->addLayout(m_sudokuData.m_numbersLayout);
  }
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
      button->setFont(QFont("Arial", 12));
      m_area->setCellWidget(rows, columns, button);
      m_buttons.emplace_back(button);
      switch (m_activeGame)
      {
        case GamesTypes::TicTacToe:
          QObject::connect(button, &QPushButton::clicked, this, &GameArea::TicTacToeButtonClicked);
          break;
        case GamesTypes::Tags:
          break;
        case GamesTypes::Sudoku:
          m_buttons.back()->setStyleSheet("background-color: white");
          QObject::connect(button, &QPushButton::clicked, this, &GameArea::SudokuButtonClicked);
          break;
      }
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

void GameArea::SudokuButtonClicked()
{
  if (m_sudokuData.m_savedNumber != 0)
  {
    auto index = std::distance(m_buttons.begin(), std::ranges::find(m_buttons, sender()));
    if (m_sudokuData.m_wrongClickedNumber != -1)
    {
      m_buttons[m_sudokuData.m_wrongClickedNumber]->setStyleSheet("background-color: white");
      m_buttons[m_sudokuData.m_wrongClickedNumber]->setText("");
      m_sudokuData.m_wrongClickedNumber = -1;
    }
    m_buttons[index]->setText(QString::number(m_sudokuData.m_savedNumber));
    if (auto observer = m_observer.lock())
    {
      auto stepResult = observer->SendData(index, m_sudokuData.m_savedNumber);
      if (stepResult.has_value())
      {
        m_buttons[index]->setEnabled(false);
      }
      else
      {
        m_buttons[index]->setStyleSheet("background-color: red");
        m_sudokuData.m_wrongClickedNumber = index;
      }
    }
  }
}


void GameArea::Restart()
{
  std::ranges::for_each(m_buttons,
                        [&](auto * button)
                        {
                          button->setEnabled(true);
                          button->setText("");
                        });
}

void GameArea::BlockGameArea()
{
  std::ranges::for_each(m_buttons, [&](auto * button) { button->setEnabled(false); });
}

void GameArea::CreateNumbersTable()
{
  for (uint8_t i = 1; i < 10; ++i)
  {
    auto * button = new QPushButton(this);
    button->setFont(QFont("Arial", 10));
    button->setText(QString::number(i));
    button->setStyleSheet("background-color: lightGray");
    m_sudokuData.m_numbersLayout->addWidget(button);
    m_sudokuData.m_numbersButtons[i - 1] = button;
    QObject::connect(button, &QPushButton::clicked, this, &GameArea::NumbersTableButtonClicked);
  }
}

void GameArea::NumbersTableButtonClicked()
{
  m_sudokuData.SetBaseButtonsStyle();
  m_sudokuData.m_savedNumber =
    std::distance(m_sudokuData.m_numbersButtons.begin(), std::ranges::find(m_sudokuData.m_numbersButtons, sender()));
  m_sudokuData.SetNumberButtonStyle();
  m_sudokuData.m_savedNumber++; // distance can return 0 index but NUMBERS starts from 1
}

void SudokuData::SetNumberButtonStyle()
{
  m_numbersButtons[m_savedNumber]->setStyleSheet("background-color: darkGray");
}

void SudokuData::SetBaseButtonsStyle()
{
  std::ranges::for_each(m_numbersButtons, [&](auto * button) { button->setStyleSheet("background-color: lightGray"); });
}
