
#include "App/app.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    App app;
    QSharedPointer<InitCommand> init = app.getInitCommand();


    return a.exec();
}
