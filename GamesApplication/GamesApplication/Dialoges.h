#pragma once

#include <QtWidgets>

#include "Resources.h"


namespace dialoges
{
static void outputDialoge(const std::string & string)
{
  auto messageBox = new QMessageBox(0);
  messageBox->setWindowTitle(resources::gameInformation);
  messageBox->setText(QString::fromStdString(string + resources::isWinner));
  messageBox->exec();
}
} // namespace dialoges
