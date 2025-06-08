#pragma once

#include <QtWidgets>

#include "Resources.h"


namespace dialoges
{
static void outputDialoge(const std::string & name, const std::string & otherData)
{
  auto messageBox = new QMessageBox(0);
  messageBox->setWindowTitle(resources::gameInformation);
  messageBox->setText(QString::fromStdString(name + resources::isWinner + "\n" + otherData));
  messageBox->exec();
}
} // namespace dialoges
