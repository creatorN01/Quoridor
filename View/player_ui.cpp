#include "player_ui.h"
#include <QDebug>
#include <QDir>

Player_ui::Player_ui(const PlayerId id, QWidget *parent) : QWidget(parent), id(id)
{
    QString path = "://images//GameKit//";
    if (id == FIRST) path += "FIRST_";
    else path += "SECOND_";
    // 静止图像
    img_player.load(path + "player.png");

//    img_arrow_up.load(":/images/GameKit/arrow_up.png");
//    img_arrow_down.load(":/images/GameKit/arrow_down.png");
//    img_arrow_left.load(":/images/GameKit/arrow_left.png");
//    img_arrow_right.load(":/images/GameKit/arrow_right.png");

//    // 设置鼠标跟踪，以接收鼠标事件
//    setMouseTracking(true);

    // 初始化 pos
    pos = QPoint(0, 0); // 根据实际情况设置初始坐标
}

void Player_ui::paint(QPainter &painter, const QPoint pos, int width, int height) {
    painter.drawPixmap(pos.x(), pos.y(), img_player.scaled(width, height, Qt::KeepAspectRatio));

//    if (isSelected) {
        // 绘制选中状态的边框
        // painter.setPen(Qt::black);  // 设置红色边框颜色
        // painter.drawRect(pos.x(), pos.y(), width, height);

        // 绘制箭头图片
//        int arrowWidth = width / 2;
//        int arrowHeight = height / 2;
//        QPoint arrowPos(pos.x() + width / 4, pos.y() - arrowHeight);
//        painter.drawPixmap(arrowPos.x(), arrowPos.y(), img_arrow_up.scaled(arrowWidth, arrowHeight, Qt::KeepAspectRatio));
//        painter.drawPixmap(arrowPos.x(), arrowPos.y() + height, img_arrow_down.scaled(arrowWidth, arrowHeight, Qt::KeepAspectRatio));
//        painter.drawPixmap(arrowPos.x() - arrowWidth, arrowPos.y() + height / 2, img_arrow_left.scaled(arrowWidth, arrowHeight, Qt::KeepAspectRatio));
//        painter.drawPixmap(arrowPos.x() + width, arrowPos.y() + height / 2, img_arrow_right.scaled(arrowWidth, arrowHeight, Qt::KeepAspectRatio));
//    }
}

//void Player_ui::mousePressEvent(QMouseEvent *event)
//{
//    qDebug() << "成功响应";
//    if (event->button() == Qt::LeftButton) {
//        // 判断点击位置是否在玩家图片区域内
//        QRect playerRect(pos.x(), pos.y(), img_player.width(), img_player.height());
//        if (playerRect.contains(event->pos()))
//         {
//            isSelected = !isSelected; // 切换选中状态

//            // 强制重绘以更新显示
//            update();
//        }
//    }

//    // 调用基类的鼠标点击事件处理函数
//    QWidget::mousePressEvent(event);
//}

void Player_ui::set_pos(const QPoint pos)
{
    this->pos = pos;
}

//void Player_ui::set_selected(const bool isSelected)
//{
//    this->isSelected = isSelected;
//}

void Player_ui::set_playerId(const PlayerId id) {
    this->id = id;
}

PlayerId& Player_ui::get_id() {
    return id;
}

//bool& Player_ui::get_isSelected() {
//    return this->isSelected;
//}

QPoint& Player_ui::get_pos() {
    return this->pos;
}
