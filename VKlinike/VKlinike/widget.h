#ifndef WIDGET_H
#define WIDGET_H

#include "globaldata.h"

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QPropertyAnimation>


class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);

    bool isFrame();
    bool isMovable_vertical();
    bool isMovable_horizontal();

    void setFrame(bool b, GlobalData::FrameForm form = GlobalData::Frame_Null, int width = -1, QColor color = nullptr);

    void setColor(QPalette::ColorRole _role, QColor _color);
    static void setColor(QWidget* wgt, QPalette::ColorRole _role, QColor _color);

    static void setTextSize(QWidget *lbl, int size);
    static void setTextColor(QWidget *wgt, QColor color);

    void setMovable_vertical(bool _movable);
    void setMovable_horizontal(bool _movable);
    void setMoveableBorder(QRect _border);
    void setMoveableBorder(int _x, int _y, int _width, int _heigth);

    QPropertyAnimation* createAnimation_geometry(QRect start, QRect finish, int duration, QObject* parent);

private:

    bool                        frame = false;
    GlobalData::FrameForm       frame_form = GlobalData::Frame_Rectangle;
    int                         frame_width = 1;
    QColor                      frame_color = Qt::black;

    bool                        my_movable_vertical = false,
                                my_movable_horizontal = false,
                                my_pressed = false;
    int                         my_topBorder = -1,
                                my_bottomBorder = -1,
                                my_leftBorder = -1,
                                my_rightBorder = -1;
    QPoint                      my_clickPoint;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *event) override;

public slots:

signals:
    void clicked();

};

#endif // WIDGET_H
