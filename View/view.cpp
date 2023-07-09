#include "view.h"
#include "ui_view.h"
#include "Common/common.h"
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QProcess>

View::View(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
    , timer(new QTimer(this)) // 定时器
    , game_status(INIT)
{
    ui->setupUi(this);
    player1 = QSharedPointer<Player_ui>::create(PlayerId::FIRST, this);
    player2 = QSharedPointer<Player_ui>::create(PlayerId::SECOND, this);
    map = QSharedPointer<Map_ui>::create(this);
//    const int GAP = 1; // 每隔0.001秒触发一次槽函数move
//    timer->start(GAP);
//    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    // 如果完全贴合图片大小，某些屏幕上可能显示不全
    this->setFixedSize(1500, 900);
}

View::~View()
{
    delete ui;
}

//void View::set_game_status_command(QSharedPointer<Commands> command)
//{
//    game_status_command = command;
//}

//void View::set_move_command(QSharedPointer<Commands> command)
//{
//    move_command = command;
//}

void View::initUI()
{
    // 构建画笔
    QPainter painter(this);
    // 初始化玩家坐标，并画出来
    QPoint point1(700, 800);
    QPoint point2(700, 0);
    player1->set_pos(point1);
    player2->set_pos(point2);
    player1->paint(painter, player1->get_pos(), 100, 100);
    player2->paint(painter, player2->get_pos(), 100, 100);
    // 绘制地图
    map->paint(painter, this->width(), this->height());
    // 文字提示，待定

}



