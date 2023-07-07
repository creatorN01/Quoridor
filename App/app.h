
#ifndef APP_H
#define APP_H


#include <QObject>
#include "Model/model.h"
#include "View/view.h"
#include "ViewModel/viewModel.h"
#include "Common/common.h"
#include <QSharedPointer>

class App : public QObject
{
    Q_OBJECT
public:
    App();
    void InitGameEnv();
    void Run();
    void ExitGame();
private:
    QSharedPointer<View> view;
    QSharedPointer<Model> model;
    QSharedPointer<ViewModel> view_model;

};





#endif // APP_H
