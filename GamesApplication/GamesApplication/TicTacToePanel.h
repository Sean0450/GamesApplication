#pragma once

#include <GameInformationPanel.h>


class TicTacToePanel: public GameInformationPanel
{
  Q_OBJECT

  QLabel * m_firstPlayerData = nullptr;
  QLabel * m_secondPlayerData = nullptr;

public:
  TicTacToePanel(QWidget * parent = nullptr);
  void SendPlayersNames() override;
  void GetData() override; //TODO TYPE!
};
