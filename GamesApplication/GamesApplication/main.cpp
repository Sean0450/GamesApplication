#include <QtWidgets/QApplication>

#include "View.h"
#include "Controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto view = std::make_shared<View>();
    auto controller = Controller::Create(view);
    std::weak_ptr<Controller> weakFromController(controller);
    view->GetGameSwitcher()->SetObserver(weakFromController);
    view->GetGameArea()->SetObserver(weakFromController);
    view->show();
    return a.exec();
}
