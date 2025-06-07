#include "GameInformationPanel.h"

GameInformationPanel::GameInformationPanel(QWidget * parent)
  : QWidget(parent)
{
}

void GameInformationPanel::SendPlayerName(const std::string & labelText)
{
  if (auto observer = m_observer.lock())
  {
    observer->SendPlayerName(labelText.substr(0, labelText.size() - 2));
  }
}

void GameInformationPanel::ConstructGamePanel(GamesTypes gameType)
{
  m_currentGame = gameType;
  bool flag;
  auto hlayout = new QVBoxLayout(this);
  m_firstPlayerData = new QLabel(this);
  m_firstPlayerData->setText(
    QInputDialog::getText(nullptr, resources::dialogeTitle, resources::firstPlayerQuestion, QLineEdit::Normal, " ", &flag) +
    ":0");
  hlayout->addWidget(m_firstPlayerData);
  SendPlayerName(m_firstPlayerData->text().toStdString());
  if (gameType == GamesTypes::TicTacToe)
  {
    m_secondPlayerData = new QLabel(this);
    m_secondPlayerData->setText(
      QInputDialog::getText(nullptr, resources::dialogeTitle, resources::secondPlayerQuestion, QLineEdit::Normal, " ", &flag) +
      ":0");
    hlayout->addWidget(m_secondPlayerData);
    SendPlayerName(m_secondPlayerData->text().toStdString());
  }
}

void GameInformationPanel::SetObserver(std::weak_ptr<GameInformationPanelObserver> observer)
{
  m_observer = std::move(observer);
}

void GameInformationPanel::UpdateStatistics(const std::string & playerStatistics)
{
  auto splitData = m_firstPlayerData->text().split(":");
  switch (m_currentGame)
  {
    case GamesTypes::TicTacToe:
      if (splitData[0].toStdString() == playerStatistics)
      {
        auto newScore = std::to_string(splitData[1].toInt() + 1);
        m_firstPlayerData->setText(splitData[0] + ":" + QString::fromStdString(newScore));
      }
      else
      {
        splitData = m_secondPlayerData->text().split(":");
        auto newScore = std::to_string(m_secondPlayerData->text().split(":")[1].toInt() + 1);
        m_secondPlayerData->setText(m_secondPlayerData->text().split(":")[0] + ":" + QString::fromStdString(newScore));
      }
      break;
    case GamesTypes::Tags:
      break;
    case GamesTypes::Sudoku:
      break;
  }
  dialoges::outputDialoge(playerStatistics);
}
