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
}

void Controller::SendData(int x, int y, const std::optional<int> optionalCell)
{

}
