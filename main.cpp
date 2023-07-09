
#include "App/app.h"
#include <QDebug>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    App app;
    app.InitGameEnv();
    app.Run();


    return a.exec();
}
