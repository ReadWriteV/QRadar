#include "./widget.h"
#include "./radar.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    Radar *radar = new Radar(this);
    radar->setFixedSize(500, 500);
    radar->move(50, 50);
}

Widget::~Widget()
{
}
