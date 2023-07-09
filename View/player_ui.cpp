#include "player_ui.h"
#include <QDebug>
#include <QDir>

Player_ui::Player_ui(const PlayerId id, QWidget *parent) : QWidget{parent}, id(id)
{
    QString path = "://images//GameKit//";
    if (id == FIRST) path += "FIRST_";
    else path += "SECOND_";

    // 静止图像
    img_player.load(path + "player.png");

//    //选中后闪烁图像
//    img_select.load(path + "select.png");
}

void Player_ui::paint(QPainter &painter, const QPoint pos, int width, int height) {
//    if(isSelected) {
//        painter.drawPixmap(pos.x(), pos.y(), img_select.scaled(width, height, Qt::KeepAspectRatio));

//    }
    painter.drawPixmap(pos.x(), pos.y(), img_player.scaled(width, height, Qt::KeepAspectRatio));
}

void Player_ui::set_pos(const QPoint &pos)
{
    this->pos = pos;
}


void Player_ui::set_selected(const bool& isSelected)
{
    this->isSelected = isSelected;
}

void Player_ui::set_playerId(const PlayerId id) {
    this->id = id;
}

PlayerId& Player_ui::get_id() {
    return id;
}

bool& Player_ui::get_isSelected() {
    return this->isSelected;
}

QPoint& Player_ui::get_pos() {
    return this->pos;
}
