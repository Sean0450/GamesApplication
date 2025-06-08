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
  if (m_secondPlayerData != nullptr)
  {
    m_secondPlayerData->setText("");
  }
  m_currentGame = gameType;
  auto hlayout = new QVBoxLayout(this);
  m_firstPlayerData = FillLabel(m_firstPlayerData);
  hlayout->addWidget(m_firstPlayerData);
  SendPlayerName(m_firstPlayerData->text().toStdString());
  if (gameType == GamesTypes::TicTacToe)
  {
    m_secondPlayerData = FillLabel(m_secondPlayerData);
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
        auto newScore = splitData[1].toInt() + 1;
        m_firstPlayerData->setText(splitData[0] + ":" + QString::number(newScore));
      }
      else
      {
        splitData = m_secondPlayerData->text().split(":");
        auto newScore = m_secondPlayerData->text().split(":")[1].toInt() + 1;
        m_secondPlayerData->setText(m_secondPlayerData->text().split(":")[0] + ":" + QString::number(newScore));
      }
      dialoges::outputDialoge(playerStatistics, "");
      break;
    case GamesTypes::Tags:
      break;
    case GamesTypes::Sudoku:
      auto splitInfo = QString::fromStdString(playerStatistics).split(":");
      dialoges::outputDialoge(splitInfo[0].toStdString(), resources::yourScore + splitInfo[1].toStdString() + "\n" +
                                                            resources::mistakesCount + splitInfo[2].toStdString());
      m_firstPlayerData->setText(splitData[0] + ":" + QString::number(splitInfo[1].toInt() + splitData[1].toInt()));
  }
}

QLabel * GameInformationPanel::FillLabel(QLabel * label)
{
  bool flag;
  if (label == nullptr)
  {
    label = new QLabel(this);
    label->setFont(QFont("Arial", 15, QFont::Bold));
    label->setText(
      QInputDialog::getText(nullptr, resources::dialogeTitle, resources::firstPlayerQuestion, QLineEdit::Normal, " ", &flag) +
      ":0");
  }
  else
  {
    label->setText(
      QInputDialog::getText(nullptr, resources::dialogeTitle, resources::firstPlayerQuestion, QLineEdit::Normal, " ", &flag) +
      ":0");
  }
  return label;
}
