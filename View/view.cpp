#include "view.h"
#include "ui_view.h"
#include "Common/common.h"
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QProcess>
#include <QPainter>

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
    QPoint point(0,0);
    arrow = QSharedPointer<Arrow_ui>::create(point, false, this);
    tempBarrier = QSharedPointer<Barrier_ui>::create(this);
    // const int GAP = 1; // 每隔0.001秒触发一次槽函数move
    // timer->start(GAP);
    // connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    // 如果完全贴合图片大小，某些屏幕上可能显示不全
    this->setFixedSize(1500, 900);

    // connect(this, SIGNAL(mySignal(QPoint)), this, SLOT(test(QPoint)));
}

View::~View()
{
    delete ui;
}

// ...

void View::initUI()
{
    // 初始化玩家坐标
    QPoint point1(700, 800);
    QPoint point2(700, 0);
    player1->set_pos(point1);
    player2->set_pos(point2);
    qDebug() << "after initUI";
    qDebug() << "player1: " << player1->get_pos().x() << "," << player1->get_pos().y();
    qDebug() << "player2: " << player2->get_pos().x() << "," << player2->get_pos().y();
    // 强制重绘
    update();
}

void View::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // 绘制地图
    map->paint(painter, this->width(), this->height());

    // 绘制玩家
    player1->paint(painter, player1->get_pos(), 100, 100);
    player2->paint(painter, player2->get_pos(), 100, 100);

    // 如果需要的话，要绘制arrow
    if (arrow->IfNeedToShow())
    {
        arrow->paint(painter);
    }
    else
    {

    }

    // 如果需要画tempBarrier的话
    if (tempBarrier->getIfNeedToShow())
    {
        tempBarrier->paint(painter);
    }


}


void View::mousePressEvent(QMouseEvent *e)
{
    qDebug() << "hello";
    auto touchPoint = e->pos();
    qDebug() << touchPoint;

    qDebug() << "准备emit";
    emit mySignal(touchPoint);
    // qDebug() << "emit信号";
}

void View::wheelEvent(QWheelEvent *event)
{
    qDebug() << "wheelEvent";
    auto type = this->tempBarrier->get_type();
    if (type == BarrierType::horizontal) type = BarrierType::vertical;
    else type = BarrierType::horizontal;
    this->tempBarrier->set_type(type);
    update();
}

void View::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
      case Qt::Key_Up:
        emit keyPressSignal(Up);
        break;
      case Qt::Key_Down:
        emit keyPressSignal(Down);
        break;
      case Qt::Key_Left:
        emit keyPressSignal(Left);
        break;
      case Qt::Key_Right:
        emit keyPressSignal(Right);
        break;
    }
}


bool View::ClickedInMap(QPoint point) {
    if(point.x() >= 300 && point.x() <= 1200 && point.y() >= 0 && point.y() <= 900) return true;
    else return false;
}

bool View::ClickedInPlayer(PlayerId activePlayer, QPoint point) {
    if(activePlayer == FIRST) {
        if(point.x() >= player1->get_pos().x() && point.x() <= player1->get_pos().x() + 100
            && point.y() >= player1->get_pos().y() && point.y() <= player1->get_pos().y() + 100) {
            return true;
        }
    }
    else if(activePlayer == SECOND) {
        if(point.x() >= player2->get_pos().x() && point.x() <= player2->get_pos().x() + 100
            && point.y() >= player2->get_pos().y() && point.y() <= player2->get_pos().y() + 100) {
            return true;
        }
    }
    return false;
}

QPoint View::CorrectBarrierPosition(QPoint point) {
    point.setX(int((point.x() + 50) / 100) * 100);
    point.setY(int((point.y() + 50) / 100) * 100);
    return point;
}

void View::ShowArrowAround(QPoint point)
{
    qDebug() << "ShowArrowAround调用";
    this->arrow->setIfNeedToShow(true);
    this->arrow->setPoint(point);
//    arrow = QSharedPointer<Arrow_ui>::create(point);
//    arrow.data()->show();
//    arrow.data()->update();
    update();
}

void View::ShowPossibleBarrier(PlayerId id, QPoint pos, BarrierType type)
{
    qDebug() << "ShowPossibleBarrier调用";
    this->tempBarrier->set_playerId(id);
    this->tempBarrier->set_pos(pos);
    this->tempBarrier->set_needToShow(true);
    this->tempBarrier->set_type(type);

    update();
}

Direction View::GetDirectionFromKeyboard()
{
    // 创建一个事件循环
    QEventLoop loop;
    // 连接键盘信号到事件循环的退出槽函数
    QObject::connect(this, SIGNAL(keyPressSignal(Direction)), arrow.data(), SLOT(setDirection(Direction)));
    QObject::connect(this, SIGNAL(keyPressSignal(Direction)), &loop, SLOT(quit()));

    // 等待键盘信号
    loop.exec();
    // 接收到键盘信号
    qDebug() << "收到键盘信号";
    return this->arrow->getDirection();
}

void View::MoveActivePlayerPos(PlayerId activePlayer, Direction direction) {
    qDebug() << "player1: " << player1->x() << "," << player1->y();
    qDebug() << "player2: " << player2->x() << "," << player2->y();

    if(activePlayer == FIRST) {
        if(direction == Up) {
            QPoint point(player1->get_pos().x(), player1->get_pos().y() - 100);
            player1->set_pos(point);
        }
        else if(direction == Down) {
            QPoint point(player1->get_pos().x(), player1->get_pos().y() + 100);
            player1->set_pos(point);
        }
        else if(direction == Left) {
            QPoint point(player1->get_pos().x() - 100, player1->get_pos().y());
            player1->set_pos(point);
        }
        else if(direction == Right) {
            QPoint point(player1->get_pos().x() + 100, player1->get_pos().y());
            player1->set_pos(point);
        }
    }
    else if(activePlayer == SECOND) {
        if(direction == Up) {
            QPoint point(player2->get_pos().x(), player2->get_pos().y() - 100);
            player2->set_pos(point);
        }
        else if(direction == Down) {
            QPoint point(player2->get_pos().x(), player2->get_pos().y() + 100);
            player2->set_pos(point);
        }
        else if(direction == Left) {
            QPoint point(player2->get_pos().x() - 100, player2->get_pos().y());
            player2->set_pos(point);
        }
        else if(direction == Right) {
            QPoint point(player2->get_pos().x() + 100, player2->get_pos().y());
            player2->set_pos(point);
        }
    }
    this->arrow->setIfNeedToShow(false);
    qDebug() << "player1: " << player1->get_pos().x() << "," << player1->get_pos().y();
    qDebug() << "player2: " << player2->get_pos().x() << "," << player2->get_pos().y();
    update();
}

