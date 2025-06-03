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
  if (choosenGame == resources::GamesNames::ticTacToe)
  {
    m_view->ConstructGameArea(GamesTypes::TicTacToe);
  }
  else if (choosenGame == resources::GamesNames::tags)
  {
    m_view->ConstructGameArea(GamesTypes::Tags);
  }
  else
  {
    m_view->ConstructGameArea(GamesTypes::ShipsBattle);
  }
}

void Controller::SendData(char x, char y, const std::optional<char> & optionalCell)
{
}

void Controller::SendPlayersNames(std::string_view firstPlayer, std::string_view secondPlayer)
{

}
