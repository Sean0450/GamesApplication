#pragma once

#include <QtWidgets>

#include "GameAreaObserver.h"

class GameArea : public QWidget
{
  Q_OBJECT
  std::weak_ptr<GameAreaObserver> m_observer;

public:
  GameArea(QWidget * parent = nullptr);
  void SetObserver(std::weak_ptr<GameAreaObserver> observer);
};
