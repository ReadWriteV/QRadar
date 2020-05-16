#include "./radar.h"
#include <QtGui/QPainter>
#include <QtCore/QTimerEvent>
#include <QtGui/QConicalGradient>
#include <QtCore/qmath.h>

Radar::Radar(QWidget *parent) : QWidget(parent)
{
    m_pieRotate = 0;
    m_timerId = -1;
    m_nSpeed = 25;
    target_r = 150;
    target_a = 156;
    r = 1;
    show = false;
    m_timerId = startTimer(m_nSpeed);
}

void Radar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), QColor(15, 45, 188));
    int len = m_drawArea.width();
    painter.setPen(QPen(Qt::green));
    painter.drawLine(m_drawArea.topLeft() + QPoint(0, len / 2), m_drawArea.topRight() + QPoint(0, len / 2));
    painter.drawLine(m_drawArea.topLeft() + QPoint(len / 2, 0), m_drawArea.bottomLeft() + QPoint(len / 2, 0));
    painter.drawEllipse(m_drawArea.center(), len / 2, len / 2);
    painter.drawEllipse(m_drawArea.center(), len / 3, len / 3);
    painter.drawEllipse(m_drawArea.center(), len / 6, len / 6);

    qreal x = m_drawArea.center().x() + (qreal)len / 2 * cos(m_pieRotate * 3.14159 / 180);
    qreal y = m_drawArea.center().y() + (qreal)len / 2 * sin(m_pieRotate * 3.14159 / 180);
    painter.setPen(QPen(Qt::green));
    painter.drawLine(m_drawArea.center(), QPointF(x, y));

    QPoint target(m_drawArea.center().x() + target_r * cos(target_a * 3.14159 / 180), m_drawArea.center().y() + target_r * sin(target_a * 3.14159 / 180));
    if (show == true)
    {
        painter.setPen(QPen(Qt::red));
        painter.drawPoint(target);
        int alpha = 255 * (1 - r / 20.0);
        painter.setPen(QPen(QColor(0, 255, 0, alpha)));
        painter.drawEllipse(target, r, r);
    }
    if (show == false)
    {
        if (abs(target_a - m_pieRotate) < 5)
        {
            show = true;
        }
    }

    QConicalGradient gradient;
    gradient.setCenter(m_drawArea.center());
    gradient.setAngle(-m_pieRotate + 180);
    gradient.setColorAt(0.4, QColor(0, 255, 0, 100));
    gradient.setColorAt(0.7, QColor(0, 255, 0, 0));
    painter.setBrush(QBrush(gradient));
    painter.setPen(Qt::NoPen);
    painter.drawPie(m_drawArea, -m_pieRotate * 16, 90 * 16);
}

void Radar::resizeEvent(QResizeEvent *)
{
    if (width() > height())
    {
        m_drawArea = QRect((width() - height()) / 2, 0, height(), height());
    }
    else
    {
        m_drawArea = QRect(0, (height() - width()) / 2, width(), width());
    }

    m_drawArea.adjust(10, 10, -10, -10);
}

void Radar::timerEvent(QTimerEvent *event)
{
    if (m_timerId == event->timerId())
    {
        m_pieRotate += 5;
        m_pieRotate %= 360;
        if (show == true)
        {
            r++;
            if (r == 20)
            {
                r = 1;
                show = false;
            }
        }
        update();
    }
}
