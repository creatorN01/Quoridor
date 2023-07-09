
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

    // 收到鼠标点击信号后触发的槽函数，传入鼠标点击的具体位置
public slots:
    void When_clicked(QPoint clickedPosition);

private:
    QSharedPointer<View> view;
    QSharedPointer<Model> model;
    QSharedPointer<ViewModel> view_model;

};





#endif // APP_H
