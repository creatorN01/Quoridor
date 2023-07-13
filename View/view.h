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
namespace Ui
{
    class View;
}
QT_END_NAMESPACE

class QTimer;

class View : public QMainWindow
{
    Q_OBJECT

public:
    explicit View(QWidget *parent = nullptr);
    ~View();

    // 接口
    void set_game_status(GameStatus status) { this->game_status = status; }
    GameStatus get_game_status() { return this->game_status; }

    // 用于判断与修正
    bool ClickedInMap(QPoint point);
    bool ClickedInPlayer(PlayerId activePlayer, QPoint point);
    QPoint CorrectBarrierPosition(QPoint point);

    // 初始化绘制
    void initUI();

    // 重绘并提供执行数据
    void ShowArrowAround(QPoint point);
    BarrierType ShowPossibleBarrier(PlayerId id, QPoint pos, BarrierType type);
    Direction GetDirectionFromKeyboard();
    BarrierType ShowRemoveBarrier(PlayerId activePlayer, QPoint point);

    // view层面的执行函数
    void MoveActivePlayerPos(PlayerId activePlayer, Direction direction);
    void PlaceBarrier_ui();
    void RemoveBarrier_ui();

    bool JudgeBarrierRemovedExistence(QPoint point);
    int get_remove_barrier_index();
    // BarrierType ShowRemoveBarrier(PlayerId activePlayer, QPoint point);
    bool JudgeVictory(PlayerId activePlayer);

signals:
    void singleClickedSignal(QPoint pos, bool clickType);
    void doubleClickedSignal(QPoint pos, bool clickType);
    void keyPressSignal(Direction direction);
    void BarrierSignal(bool fixed);
    void removeBarrierSignal();


public slots:

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void slotClickTime();

private:
    // ui指针
    Ui::View *ui;
    // ui组件
    QSharedPointer<Map_ui> map;
    QSharedPointer<Player_ui> player1;
    QSharedPointer<Player_ui> player2;
    QSharedPointer<Arrow_ui> arrow;
    QSharedPointer<Barrier_ui> tempBarrier;
    // BarrierList
    QSharedPointer<std::vector<QSharedPointer<Barrier_ui>>> Barrier_ui_List;
    // 文字提示
    TextPrompt *info;
    // 墓碑障碍
    int remove_barrier_index;
    // 回收站
    QSharedPointer<std::vector<QSharedPointer<Barrier_ui>>> rubbish_bin;

    // 使用定时器区分鼠标signalClicked与doubleClicked
    QTimer *_clickTimer = nullptr;
    int _clickCount = 0;        // 点击次数
    QPoint clickedPosition;     // 点击位置

    // 游戏状态
    GameStatus game_status;
};

#endif // VIEW_H
