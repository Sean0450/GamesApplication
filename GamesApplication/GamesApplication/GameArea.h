#pragma once

#include <QtWidgets>

#include "GameAreaObserver.h"

enum class GamesTypes
{
  TicTacToe,
  Tags,
  ShipsBattle
};

class GameArea : public QWidget
{
  Q_OBJECT
  std::weak_ptr<GameAreaObserver> m_observer;
  QTableWidget * m_area = nullptr;
  QVBoxLayout * m_mainLayout = nullptr;
  std::vector<QPushButton *> m_buttons;
  GamesTypes m_activeGame;

  void CreateArea(uint8_t size);
private slots:
  void TicTacToeButtonClicked();
  void TagsButtonClicked();
  void ShipBattleButtonClicked();

public:
  GameArea(QWidget * parent = nullptr);
  void SetObserver(std::weak_ptr<GameAreaObserver> observer);
  void ConstructGameArea(GamesTypes gameType);
};
