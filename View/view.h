#ifndef VIEW_H
#define VIEW_H

#include <vector>
#include <QMainWindow>
#include <QSharedPointer>
#include "View/barrier_ui.h"
#include "View/player_ui.h"
#include "View/map_ui.h"
#include "View/textprompt.h"


namespace Ui {
class View;
}

class View : public QMainWindow
{
    Q_OBJECT

public:
    explicit View(QWidget *parent = nullptr);
    ~View();

    // 信号和槽等到第一轮迭代开始时，再写~


private:
    // ui指针
    Ui::View *ui;
    // ui组件
    QSharedPointer<Map_ui> map;
    QSharedPointer<Player_ui> player1;
    QSharedPointer<Player_ui> player2;
    // 一些文字提示（待完成）
    QSharedPointer<TextPrompt> PlayerName;
    // ...
    // 初步觉得用一个vector存，后期如果有不方便的地方，可以再调整，换成map什么的
    std::vector<QSharedPointer<Barrier_ui>> Barrier_ui_List;
};

#endif // VIEW_H
