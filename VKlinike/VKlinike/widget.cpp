#include "widget.h"

#include <QLabel>
#include <QMouseEvent>


Widget::Widget(QWidget *parent) : QWidget(parent)
{
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor(255, 255, 255));
    setPalette(pal);
    moveToThread(QApplication::instance()->thread());
}

bool Widget::isFrame()
{
    return frame;
}

bool Widget::isMovable_vertical()
{
    return my_movable_vertical;
}

bool Widget::isMovable_horizontal()
{
    return  my_movable_horizontal;
}

void Widget::setMovable_vertical(bool _movable)
{
    my_movable_vertical = _movable;
}

void Widget::setMovable_horizontal(bool _movable)
{
    my_movable_horizontal = _movable;
}

void Widget::setMoveableBorder(int _x, int _y, int _width, int _heigth)
{
    my_topBorder = _y;
    my_leftBorder = _x;
    my_rightBorder = _x + _width;
    my_bottomBorder = _y + _heigth;
}

void Widget::setMoveableBorder(QRect _border)
{
    setMoveableBorder(_border.x(), _border.y(), _border.width(), _border.height());
}

void Widget::setFrame(bool b, GlobalData::FrameForm form, int width, QColor color)
{
    frame = b;
    if(width != -1)
        frame_width = width;

    if(form != GlobalData::Frame_Null)
        frame_form = form;

    if(color != nullptr)
        frame_color = color;
}

void Widget::setColor(QPalette::ColorRole _role, QColor _color)
{
    QPalette pal = palette();
    pal.setColor(_role, _color);
    setPalette(pal);
}

void Widget::setColor(QWidget* wgt, QPalette::ColorRole _role, QColor _color)
{
    QPalette pal = wgt->palette();
    pal.setColor(_role, _color);
    wgt->setPalette(pal);
}

void Widget::setTextSize(QWidget *lbl, int size)
{
    QFont font = lbl->font();
    font.setPixelSize(size);
    lbl->setFont(font);
}

void Widget::setTextColor(QWidget *wgt, QColor color)
{
    QPalette palette = wgt->palette();
    palette.setColor(QPalette::Text, color);
    wgt->setPalette(palette);
}

QPropertyAnimation* Widget::createAnimation_geometry(QRect start, QRect finish, int duration, QObject *_parent)
{
    QPropertyAnimation* new_animation_geometry = new QPropertyAnimation(this, "geometry", _parent);
    new_animation_geometry->setDuration(duration);
    new_animation_geometry->setEasingCurve(GlobalData::interface::animation_curve);
    new_animation_geometry->setStartValue(start);
    new_animation_geometry->setEndValue(finish);
    connect(new_animation_geometry, &QPropertyAnimation::finished, new_animation_geometry, &QPropertyAnimation::deleteLater);
    return new_animation_geometry;
}

void Widget::mousePressEvent(QMouseEvent *ev)
{
    QWidget::mousePressEvent(ev);
    my_pressed = true;
    my_clickPoint = ev->pos();
}

void Widget::mouseReleaseEvent(QMouseEvent *ev)
{
    QWidget::mouseReleaseEvent(ev);
    if(my_pressed && my_clickPoint.x() + 20 < ev->x() && my_clickPoint.x() - 20 > ev->x() && my_clickPoint.y() + 20 < ev->y() && my_clickPoint.y() - 20 > ev->y())
    {
        emit clicked();
    }
    my_pressed = false;
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    bool moved = false;
    if(my_pressed)
    {
        if(my_movable_vertical)
        {
            moved = true;
            int resY = y() + (event->y() - my_clickPoint.y());
            if(my_topBorder == -1 || resY <= my_topBorder)
            {
                if(my_bottomBorder == -1 || resY + height() >= my_bottomBorder)
                    move(x(), resY);
                else
                    if(height() < my_bottomBorder - my_topBorder)
                        move(x(), 0);
                    else
                        move(x(), my_bottomBorder - height());
            }
            else
                move(x(), my_topBorder);
        }
        if(my_movable_horizontal)
        {
            moved = true;
            int resX = x() + (event->x() - my_clickPoint.x());
            if(my_leftBorder == -1 || resX <= my_leftBorder)
            {
                if(my_rightBorder == -1 || resX + width() >= my_rightBorder)
                    move(resX, y());
                else
                    if(width() < my_rightBorder - my_leftBorder)
                        move(0, y());
                    else
                        move(my_rightBorder - width(), y());
            }
            else
                move(my_leftBorder, y());
        }
    }
    if(!moved)
        QWidget::mouseMoveEvent(event);
}

void Widget::paintEvent(QPaintEvent *event)
{
    using namespace GlobalData;
    QPainter painter(this);
    QPalette pal = palette();

    // НАСТРОЙКА ПЕРА
    if(frame)
    {
        painter.setPen(QPen(frame_color, frame_width));
    }
    else
    {
        painter.setPen(pal.background().color());
    }
    // ---------------
    // НАСТРОЙКА КИСТИ
    if(parent() != nullptr && ((QWidget*)parent())->palette().background() != pal.background())
        painter.setBrush(QBrush(pal.background().color()));
    // ---------------
    // НАСТРОЙКА ФОРМЫ РАМКИ
    if(frame_form == Frame_Rectangle)
    {
        painter.drawRect(frame_width / 2, frame_width / 2, width() - frame_width, height() - frame_width);
    }
    else if(frame_form == Frame_Rounded)
    {
        int index = GlobalData::interface::indent / 2;
        painter.drawRoundedRect(frame_width / 2, frame_width / 2, width() - frame_width, height() - frame_width, index, index);
    }
    else if(frame_form == Frame_Circular)
    {
        painter.drawEllipse(frame_width / 2, frame_width / 2, width() - frame_width, height() - frame_width);
    }
    // ---------------
}
