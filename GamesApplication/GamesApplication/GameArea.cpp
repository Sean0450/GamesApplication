#include "GameArea.h"

GameArea::GameArea(QWidget * parent): QWidget(parent){
  auto label = new QLabel("GameArea", this);
}

void GameArea::SetObserver(std::weak_ptr<GameAreaObserver> observer)
{
  m_observer = std::move(observer);
}
