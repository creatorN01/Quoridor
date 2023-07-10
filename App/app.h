
#ifndef APP_H
#define APP_H

#include <QPoint>
#include <QObject>
#include "Model/model.h"
#include "View/view.h"
#include "ViewModel/viewModel.h"
#include "Common/common.h"
#include <QSharedPointer>
#include "QMouseEvent"

class App : public QObject
{
    Q_OBJECT
public:
    App();
    ~App(){qDebug() << "析构";}
    void InitGameEnv();
    void Run();
    void ExitGame();


//protected:
//    void mousePressEvent(QMouseEvent *e) override;

    // 收到鼠标点击信号后触发的槽函数，传入鼠标点击的具体位置
public slots:
    void When_Clicked(QPoint clickedPosition);

    // connect(view.get(), SIGNAL(mySignal(QPoint pos)), this, SLOT(When_Clicked(QPoint clickedPosition)));
private:
    QSharedPointer<View> view;
    QSharedPointer<Model> model;
    QSharedPointer<ViewModel> view_model;

};





#endif // APP_H
