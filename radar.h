#ifndef Radar_H
#define Radar_H

#include <QtWidgets/QWidget>

class Radar : public QWidget
{
    Q_OBJECT
public:
    explicit Radar(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void timerEvent(QTimerEvent *event);

private:
    QRect m_drawArea;
    int m_pieRotate;
    int m_timerId;
    int m_nSpeed;
    int target_r;
    int target_a;
    int r;
    bool show;
};

#endif // Radar_H
