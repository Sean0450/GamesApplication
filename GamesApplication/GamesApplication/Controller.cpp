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
  if (choosenGame == resources::GamesNames::ticTacToe)
  {
    m_activeGame = std::make_unique<TicTacToe>();
    m_view->ConstructGameArea(GamesTypes::TicTacToe);
  }
  else if (choosenGame == resources::GamesNames::tags)
  {
    m_view->ConstructGameArea(GamesTypes::Tags);
  }
  else
  {
    m_activeGame = std::make_unique<Sudoku>();
    m_view->ConstructGameArea(GamesTypes::Sudoku);
    StartSudokuGame();
  }
}

std::optional<uint8_t> Controller::SendData(uint8_t cellIndex, const std::optional<uint8_t> & optionalCell)
{
  auto stepResult = m_activeGame->Step(cellIndex, optionalCell);
  auto data = m_activeGame->GetWinnerInformation();
  if (!data.empty())
  {
    m_view->GetInformationPanel()->UpdateStatistics(data);
    m_view->GetGameArea()->BlockGameArea();
  }
  return stepResult;
}

void Controller::SendPlayerName(const std::string & playerName)
{
  m_activeGame->SetName(playerName);
}

void Controller::RestartGame()
{
  m_view->GetGameArea()->Restart();
  m_activeGame->RestartGame();
  StartSudokuGame();
}

void Controller::StartSudokuGame()
{
  if (auto sudoku = dynamic_cast<Sudoku *>(m_activeGame.get()))
  {
    m_view->GetGameArea()->FillGameArea(sudoku->GetUserArea());
  }
}
