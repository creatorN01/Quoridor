#ifndef MAP_UI_H
#define MAP_UI_H

#include <QPixmap>
#include <QWidget>
#include <QPainter>
#include "Common/common.h"


class Map_ui : public QWidget
{
    Q_OBJECT
public:
    explicit Map_ui(QWidget *parent = nullptr);
    void paint(QPainter &,int width, int height);
private:
    QPixmap img_map;
    QPixmap t1;
    QPixmap t2;

};

#endif // MAP_UI_H
