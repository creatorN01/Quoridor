
#ifndef ARROW_UI_H
#define ARROW_UI_H


#include <QWidget>
#include <QMainWindow>
#include <QPoint>
#include "Common/common.h"
#include <QDebug>

class Arrow_ui : public QWidget
{
    Q_OBJECT
public:
    explicit Arrow_ui(QWidget *parent = nullptr, QPoint point_ = QPoint(0,0), bool needtoShow_ = false);
    void paint(QPainter &);
    QPoint getPoint();
    void setPoint(QPoint point);
    void setIfNeedToShow(bool need);
    Direction getDirection() {return this->directionSelected;}
    bool IfNeedToShow();
public slots:
    void setDirection(Direction d) {qDebug() << "修改directionSelected"; this->directionSelected = d;}

protected:
    // void paintEvent(QPaintEvent *event) override;


private:
    // 箭头图像
    QPixmap img_arrow_up;
    QPixmap img_arrow_down;
    QPixmap img_arrow_left;
    QPixmap img_arrow_right;

    QPoint point;
    bool needtoShow;
    Direction directionSelected;
};

#endif // ARROW_UI_H
