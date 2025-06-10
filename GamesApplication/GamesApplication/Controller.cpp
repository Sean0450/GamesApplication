#include "Controller.h"

Controller::Controller(Private priv, std::shared_ptr<View> view)
  : m_view(std::move(view))
{
}

std::shared_ptr<Controller> Controller::Create(std::shared_ptr<View> view)
{
  auto controller = std::make_shared<Controller>(Private(), view);
  return controller;
}

void Controller::SendChoosenGame(const std::string & choosenGame)
{
  m_view->GetGameArea()->ClearGameArea();
  m_activeGame.reset();
  m_fieldedActiveGame.reset();
  if (choosenGame == resources::GamesNames::ticTacToe)
  {
    m_activeGame = std::make_unique<TicTacToe>();
    m_view->ConstructGameArea(GamesTypes::TicTacToe);
  }
  else if (choosenGame == resources::GamesNames::tags)
  {
    m_fieldedActiveGame = std::make_unique<Tags>();
    m_view->ConstructGameArea(GamesTypes::Tags);
    m_view->GetGameArea()->FillGameArea(m_fieldedActiveGame->GetUserArea());
  }
  else
  {
    m_fieldedActiveGame = std::make_unique<Sudoku>();
    m_view->ConstructGameArea(GamesTypes::Sudoku);
    m_view->GetGameArea()->FillGameArea(m_fieldedActiveGame->GetUserArea());
  }
}

std::optional<uint8_t> Controller::SendData(uint8_t cellIndex, const std::optional<uint8_t> & optionalCell)
{
  std::optional<uint8_t> stepResult;
  std::string data;
  if (m_activeGame != nullptr)
  {
    stepResult = m_activeGame->Step(cellIndex, optionalCell);
    data = m_activeGame->GetWinnerInformation();
  }
  else
  {
    stepResult = m_fieldedActiveGame->Step(cellIndex, optionalCell);
    data = m_fieldedActiveGame->GetWinnerInformation();
  }
  if (!data.empty())
  {
    m_view->GetInformationPanel()->UpdateStatistics(data);
    m_view->GetGameArea()->BlockGameArea();
  }
  return stepResult;
}

void Controller::SendPlayerName(const std::string & playerName)
{
  if (m_activeGame != nullptr)
  {
    m_activeGame->SetName(playerName);
  }
  else
  {
    m_fieldedActiveGame->SetName(playerName);
  }
}

void Controller::RestartGame()
{
  m_view->GetGameArea()->Restart();
  if (m_fieldedActiveGame != nullptr)
  {
    m_fieldedActiveGame->RestartGame();
    m_view->GetGameArea()->FillGameArea(m_fieldedActiveGame->GetUserArea());
  }
  else
  {
    m_activeGame->RestartGame();
  }
}
