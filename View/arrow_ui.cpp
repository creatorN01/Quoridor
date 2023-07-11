#include <QDebug>
#include "arrow_ui.h"
#include "qpainter.h"

Arrow_ui::Arrow_ui(QWidget *parent, QPoint point_, bool needtoShow_) : point(point_), needtoShow(needtoShow_), QWidget(parent)
{
    qDebug() << "调用Arrow_ui::Arrow_ui";
    img_arrow_up.load("://images//GameKit//arrow_up.png");
    img_arrow_down.load("://images//GameKit//arrow_down.png");
    img_arrow_left.load("://images//GameKit//arrow_left.png");
    img_arrow_right.load("://images//GameKit//arrow_right.png");

//    this->point = point_;
//    this->needtoShow = needtoShow_;
}

QPoint Arrow_ui::getPoint()
{
    return this->point;
}

void Arrow_ui::setPoint(QPoint point)
{
    this->point = point;
}

bool Arrow_ui::IfNeedToShow()
{
    return this->needtoShow;
}

void Arrow_ui::setIfNeedToShow(bool need)
{
    this->needtoShow = need;
}
void Arrow_ui::paint(QPainter &painter)
{
    QPoint point = this->getPoint();
    if(point.y() != 0) painter.drawPixmap(point.x(), point.y() - 100, img_arrow_up.scaled(100, 100, Qt::KeepAspectRatio));
    if(point.y() != 900) painter.drawPixmap(point.x(), point.y() + 100, img_arrow_down.scaled(100, 100, Qt::KeepAspectRatio));
    if(point.x() != 300) painter.drawPixmap(point.x() - 100, point.y(), img_arrow_left.scaled(100, 100, Qt::KeepAspectRatio));
    if(point.x() != 1100) painter.drawPixmap(point.x() + 100, point.y(), img_arrow_right.scaled(100, 100, Qt::KeepAspectRatio));

}

//void Arrow_ui::paintEvent(QPaintEvent *event)
//{
//    qDebug() << "调用Arrow_ui::paintEvent";
//    Q_UNUSED(event);
//    QPainter painter(this);

//}
