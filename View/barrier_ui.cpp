
#include "barrier_ui.h"

Barrier_ui::Barrier_ui(QWidget *parent)
    : QWidget{parent}
{
    //为静态变量赋值
//    if(img_barrier1_row.isNull()) {
//        img_barrier1_row.load(":/GameKit/barrier1_row.jpg");
//    }
//    if(img_barrier1_column.isNull()) {
//        img_barrier1_column.load(":/GameKit/img_barrier1_column.jpg");
//    }
//    if(img_barrier1_row.isNull()) {
//        img_barrier2_row.load(":/GameKit/img_barrier2_row.jpg");
//    }
//    if(img_barrier1_row.isNull()) {
//        img_barrier2_column.load(":/GameKit/img_barrier2_column.jpg");
//    }
    img_barrier1_row.load(":/GameKit/barrier1_row.jpg");
    img_barrier1_column.load(":/GameKit/img_barrier1_column.jpg");
    img_barrier2_row.load(":/GameKit/img_barrier2_row.jpg");
    img_barrier2_column.load(":/GameKit/img_barrier2_column.jpg");
}

void Barrier_ui::paint(QPainter &painter, int width, int height, const QPoint& pos, const PlayerId& id, const BarrierType& type) {
    if(id == FIRST) {
        if(type == horizontal){
            painter.drawPixmap(pos.x(), pos.y(), img_barrier1_row.scaled(width, height, Qt::KeepAspectRatio));
        }
        else {
            painter.drawPixmap(pos.x(), pos.y(), img_barrier1_column.scaled(width, height, Qt::KeepAspectRatio));
        }
    }
    else {
        if(type == horizontal) {
            painter.drawPixmap(pos.x(), pos.y(), img_barrier2_row.scaled(width, height, Qt::KeepAspectRatio));
        }
        else {
            painter.drawPixmap(pos.x(), pos.y(), img_barrier2_column.scaled(width, height, Qt::KeepAspectRatio));
        }
    }
}

void Barrier_ui::set_pos(const QPoint& pos) {
    this->pos = pos;
}

void Barrier_ui::set_playerId(const PlayerId& id) {
    this->playerId = id;
}

void Barrier_ui::set_type(const BarrierType& type) {
    this->type = type;
}

QPoint& Barrier_ui::get_pos() {
    return this->pos;
}

PlayerId& Barrier_ui::get_playerId() {
    return this->playerId;
}

BarrierType& Barrier_ui::get_type() {
    return this->type;
}
