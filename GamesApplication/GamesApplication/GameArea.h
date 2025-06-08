#pragma once

#include <QtWidgets>

#include "GameAreaObserver.h"

enum class GamesTypes
{
  TicTacToe,
  Tags,
  Sudoku
};

struct SudokuData
{
  QHBoxLayout * m_numbersLayout = nullptr;
  uint8_t m_savedNumber = 0;
  char m_wrongClickedNumber = -1;
  std::array<QPushButton *, 9> m_numbersButtons;
  void SetNumberButtonStyle();
  void SetBaseButtonsStyle();
};

class GameArea : public QWidget
{
  Q_OBJECT
  std::weak_ptr<GameAreaObserver> m_observer;
  QTableWidget * m_area = nullptr;
  QVBoxLayout * m_mainLayout = nullptr;
  std::vector<QPushButton *> m_buttons;
  GamesTypes m_activeGame;
  SudokuData m_sudokuData;

  void CreateArea(uint8_t size);
  void CreateNumbersTable();
private slots:
  void TicTacToeButtonClicked();
  void TagsButtonClicked();
  void SudokuButtonClicked();
  void NumbersTableButtonClicked();

public:
  GameArea(QWidget * parent = nullptr);
  void SetObserver(std::weak_ptr<GameAreaObserver> observer);
  void ConstructGameArea(GamesTypes gameType);
  void Restart();
  void BlockGameArea();
  void ClearGameArea();

  template<uint8_t SIZE>
  void FillGameArea(const std::array<std::array<uint8_t, SIZE>, SIZE> & data)
  {
    for (uint8_t i = 0; i < SIZE; ++i)
    {
      for (uint8_t j = 0; j < SIZE; ++j)
      {
        if (data[i][j] != 0)
        {
          m_buttons[i * SIZE + j]->setText(QString::number(data[i][j]));
          m_buttons[i * SIZE + j]->setEnabled(false);
        }
      }
    }
  }
};
