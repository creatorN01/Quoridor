#ifndef VIEW_H
#define VIEW_H

#include <vector>
#include <QMainWindow>
#include <QSet>
#include <QSharedPointer>
#include <QTimer>
#include "View/barrier_ui.h"
#include "View/player_ui.h"
#include "View/map_ui.h"
#include "View/textprompt.h"
#include "View/arrow_ui.h"
#include <QTimer>
#include "QMouseEvent"

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE


class Commands
{
public:
    Commands()
    {

    }
public:
    // 执行程序
    virtual void exec() = 0;
};

class View : public QMainWindow
{
    Q_OBJECT

public:
    explicit View(QWidget *parent = nullptr);
    ~View();

    void set_game_status_command(QSharedPointer<Commands>);
    void set_move_command(QSharedPointer<Commands>);

//    void set_get_ice_pos(const std::function<QPoint(void)>&&);
//    void set_get_fire_pos(const std::function<QPoint(void)>&&);

    // 信号和槽等到第一轮迭代开始时，再写~


    void initUI();                      // 初始化绘制
    bool ClickedInMap(QPoint point);
    bool ClickedInPlayer(PlayerId activePlayer, QPoint point);
    QPoint CorrectBarrierPosition(QPoint point);
    void ShowArrowAround(QPoint point);
    BarrierType ShowPossibleBarrier(PlayerId id, QPoint pos, BarrierType type);
    Direction GetDirectionFromKeyboard();
    void MoveActivePlayerPos(PlayerId activePlayer, Direction direction);
    void PlaceBarrier_ui();
signals:
    void mySignal(QPoint pos);
    void keyPressSignal(Direction direction);
    void placeBarrierSignal(bool fixed);

// public slots:
    void react_game_status_change(const GameStatus &status); // 接收游戏状态改变的信号
//public slots:
//    void test(QPoint clickedPosition);
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    // ui指针
    Ui::View *ui;
    // ui组件
    QSharedPointer<Map_ui> map;
    QSharedPointer<Player_ui> player1;
    QSharedPointer<Player_ui> player2;
    QSharedPointer<Arrow_ui> arrow;
    QSharedPointer<Barrier_ui> tempBarrier;
    // 一些文字提示（待完成）
    TextPrompt* info;
    // ...
    // 初步觉得用一个vector存，后期如果有不方便的地方，可以再调整，换成map什么的
    std::vector<QSharedPointer<Barrier_ui>> Barrier_ui_List;

    QTimer* timer;
    // int curFrame; // 用于绘制地图，记录帧数
    GameStatus game_status; // 游戏状态

};

#endif // VIEW_H


