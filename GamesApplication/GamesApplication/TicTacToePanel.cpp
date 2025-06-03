#include "TicTacToePanel.h"

TicTacToePanel::TicTacToePanel(QWidget * parent)
  : GameInformationPanel(parent)
{
  bool flag;
  auto hlayout = new QVBoxLayout(this);
  m_firstPlayerData = new QLabel(this);
  m_firstPlayerData->setText(
    QInputDialog::getText(nullptr, "Input player name Dialoge", "Enter first player Name:", QLineEdit::Normal, " ", &flag) +
    ":0");
  m_secondPlayerData = new QLabel(this);
  m_secondPlayerData->setText(
    QInputDialog::getText(nullptr, "Input player name Dialoge", "Enter second player Name:", QLineEdit::Normal, " ", &flag) +
    ":0");
  hlayout->addWidget(m_firstPlayerData);
  hlayout->addWidget(m_secondPlayerData);
  SendPlayersNames();
}

void TicTacToePanel::SendPlayersNames()
{
  if (auto observer = m_observer.lock())
  {
    auto firstStringView = std::string_view{m_firstPlayerData->text().toStdString()};
    auto secondStringView = std::string_view{m_secondPlayerData->text().toStdString()};
    observer->SendPlayersNames(firstStringView.substr(0, firstStringView.size() - 2),
                               secondStringView.substr(0, secondStringView.size() - 2));
  }
}

void TicTacToePanel::GetData()
{
}
