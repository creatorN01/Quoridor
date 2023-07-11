#include "view.h"
#include "ui_view.h"
#include "Common/common.h"
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QProcess>
#include <QPainter>
// 构造，跟随App::App()执行，智能指针
View::View(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::View), _clickTimer(new QTimer(this)), game_status(INIT)
{
    // 初始化
    ui->setupUi(this);
    map = QSharedPointer<Map_ui>::create(this);
    player1 = QSharedPointer<Player_ui>::create(PlayerId::FIRST, this);
    player2 = QSharedPointer<Player_ui>::create(PlayerId::SECOND, this);
    arrow = QSharedPointer<Arrow_ui>::create(this);
    tempBarrier = QSharedPointer<Barrier_ui>::create(this);
    Barrier_ui_List = QSharedPointer<std::vector<QSharedPointer<Barrier_ui>>>::create();
    info = new TextPrompt(this);

    // 连接信号和槽
    connect(_clickTimer, SIGNAL(timeout()), this, SLOT(slotClickTime()));
}
// 析构
View::~View()
{
    delete ui;
    delete info;
    delete _clickTimer;
}


// 初始化绘制
void View::initUI()
{
    // 设置尺寸
    this->setFixedSize(1500, 900);
    // 初始化玩家坐标
    QPoint point1(700, 800);
    QPoint point2(700, 0);
    player1->set_pos(point1);
    player2->set_pos(point2);
    // qDebug() << "after initUI";
    // qDebug() << "player1: " << player1->get_pos().x() << "," << player1->get_pos().y();
    // qDebug() << "player2: " << player2->get_pos().x() << "," << player2->get_pos().y();
    // qDebug() << "after initUI";
    // qDebug() << "player1: " << player1->get_pos().x() << "," << player1->get_pos().y();
    // qDebug() << "player2: " << player2->get_pos().x() << "," << player2->get_pos().y();

    // 设置游戏状态为PLAYING
    game_status = PLAYING;

    // 创建布局管理器
    QVBoxLayout *layout = new QVBoxLayout();

    // 将 TextPrompt 添加到布局中
    layout->addWidget(info);

    // 将布局设置给主窗口
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // 强制重绘
    update();
}
void View::wheelEvent(QWheelEvent *event)
{
    // tempBarrier is fixed
    if (tempBarrier->IfFixed())
    {
        return;
    }
    qDebug() << "wheelEvent";
    auto type = this->tempBarrier->get_type();
    if (type == BarrierType::horizontal)
        type = BarrierType::vertical;
    else
        type = BarrierType::horizontal;
    this->tempBarrier->set_type(type);
    update();
}
void View::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    map->paint(painter, this->width(), this->height());     // map
    player1->paint(painter, player1->get_pos(), 100, 100);  // player
    player2->paint(painter, player2->get_pos(), 100, 100);
    if (arrow->IfNeedToShow())                              // arrow
    {
        arrow->paint(painter);
    }
    if (tempBarrier->IfNeedToShow())                        // tempBarrier
    {
        tempBarrier->paint(painter);
    }
    auto vectorPtr = Barrier_ui_List.data();                // Barrier_ui_List
    // qDebug() << vectorPtr->size();
    for (int i = 0; i < (int)vectorPtr->size(); i++)
    {
        (*vectorPtr)[i].get()->paint(painter);
    }
    info->paint();                                          // info
}
void View::mousePressEvent(QMouseEvent *event)
{
    auto touchPoint = event->pos();
    this->clickedPosition = touchPoint;
    // change
    if (event->button() & Qt::LeftButton) {
        if (!_clickTimer->isActive()) {
            _clickTimer->start(300);
            _clickCount++;
        } else {
            _clickCount++;
        }
    }
}
void View::slotClickTime()
{
    _clickTimer->stop();
    if (_clickCount == 1) {
        qDebug() << QStringLiteral("Clicked ONCE");
        qDebug() << this->clickedPosition;
        emit singleClickedSignal(this->clickedPosition, ClickType::LeftSingleClicked);
    } else if (_clickCount == 2) {
        qDebug() << QStringLiteral("Clicked TWICE");
        qDebug() << this->clickedPosition;
        emit doubleClickedSignal(this->clickedPosition, ClickType::LeftDoubleClicked);
    }
    _clickCount = 0;
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
    case Qt::Key_Space:
        emit placeBarrierSignal(true);
        break;
    }
}
// 用于判断与修正
bool View::ClickedInMap(QPoint point)
{
    if (point.x() >= 300 && point.x() <= 1200 && point.y() >= 0 && point.y() <= 900)
        return true;
    else
        return false;
}
bool View::ClickedInPlayer(PlayerId activePlayer, QPoint point)
{
    if (activePlayer == FIRST)
    {
        if (point.x() >= player1->get_pos().x() && point.x() <= player1->get_pos().x() + 100 && point.y() >= player1->get_pos().y() && point.y() <= player1->get_pos().y() + 100)
        {
            return true;
        }
    }
    else if (activePlayer == SECOND)
    {
        if (point.x() >= player2->get_pos().x() && point.x() <= player2->get_pos().x() + 100 && point.y() >= player2->get_pos().y() && point.y() <= player2->get_pos().y() + 100)
        {
            return true;
        }
    }
    return false;
}
QPoint View::CorrectBarrierPosition(QPoint point)
{
    point.setX(int((point.x() + 50) / 100) * 100);
    point.setY(int((point.y() + 50) / 100) * 100);
    return point;
}

// 重绘并提供执行数据
void View::ShowArrowAround(QPoint point)
{
    qDebug() << "View::ShowArrowAround()";
    this->arrow->setIfNeedToShow(true);
    this->arrow->setPoint(point);
    //    arrow = QSharedPointer<Arrow_ui>::create(point);
    //    arrow.data()->show();
    //    arrow.data()->update();
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
BarrierType View::ShowPossibleBarrier(PlayerId id, QPoint pos, BarrierType type)
{
    qDebug() << "View::ShowPossibleBarrier()";
    this->tempBarrier->set_playerId(id);
    this->tempBarrier->set_pos(pos);
    this->tempBarrier->set_needToShow(true);
    this->tempBarrier->set_type(type);
    update();

    // 故技重施
    QEventLoop loop;
    QObject::connect(this, SIGNAL(placeBarrierSignal(bool)), tempBarrier.data(), SLOT(set_fixed(bool)));
    QObject::connect(this, SIGNAL(placeBarrierSignal(bool)), &loop, SLOT(quit()));

    loop.exec();
    qDebug() << "收到空格信号";
    return this->tempBarrier->get_type();
}

// view层面的执行函数
void View::MoveActivePlayerPos(PlayerId activePlayer, Direction direction)
{
    // qDebug() << "player1: " << player1->x() << "," << player1->y();
    // qDebug() << "player2: " << player2->x() << "," << player2->y();

    if (activePlayer == FIRST)
    {
        if (direction == Up)
        {
            QPoint point(player1->get_pos().x(), player1->get_pos().y() - 100);
            player1->set_pos(point);
        }
        else if (direction == Down)
        {
            QPoint point(player1->get_pos().x(), player1->get_pos().y() + 100);
            player1->set_pos(point);
        }
        else if (direction == Left)
        {
            QPoint point(player1->get_pos().x() - 100, player1->get_pos().y());
            player1->set_pos(point);
        }
        else if (direction == Right)
        {
            QPoint point(player1->get_pos().x() + 100, player1->get_pos().y());
            player1->set_pos(point);
        }
    }
    else if (activePlayer == SECOND)
    {
        if (direction == Up)
        {
            QPoint point(player2->get_pos().x(), player2->get_pos().y() - 100);
            player2->set_pos(point);
        }
        else if (direction == Down)
        {
            QPoint point(player2->get_pos().x(), player2->get_pos().y() + 100);
            player2->set_pos(point);
        }
        else if (direction == Left)
        {
            QPoint point(player2->get_pos().x() - 100, player2->get_pos().y());
            player2->set_pos(point);
        }
        else if (direction == Right)
        {
            QPoint point(player2->get_pos().x() + 100, player2->get_pos().y());
            player2->set_pos(point);
        }
    }
    this->arrow->setIfNeedToShow(false);
    // qDebug() << "player1: " << player1->get_pos().x() << "," << player1->get_pos().y();
    // qDebug() << "player2: " << player2->get_pos().x() << "," << player2->get_pos().y();
    update();
}
void View::PlaceBarrier_ui()
{
    Barrier_ui_List.data()->push_back(tempBarrier);
    // 深拷贝
    tempBarrier = QSharedPointer<Barrier_ui>::create();
    // tempBarrier->set_fixed(true);
    tempBarrier->set_needToShow(false);
    // 文字提示变更（待定）
    update();
}
void View::RemoveBarrier_ui()
{

}
