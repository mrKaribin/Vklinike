#include "button.h"

#include <QMouseEvent>


Button::Button(QWidget *parent) : QLabel(parent)
{
    my_Initialize();
}

Button::Button(QString text)
{
    my_Initialize();
    setText(text);
}

Button::Button(QPixmap pix)
{
    my_Initialize();
    setPixmap(pix);
}

void Button::my_Initialize()
{
    setAlignment(Qt::AlignCenter);
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor(255, 255, 255));
    setPalette(pal);
    moveToThread(QApplication::instance()->thread());
}

bool Button::isFrame()
{
    return frame;
}

void Button::setFrame(bool b, GlobalData::FrameForm form, int width, QColor color)
{
    frame = b;
    if(width != -1)
        frame_width = width;

    if(form != GlobalData::Frame_Null)
        frame_form = form;

    if(color != nullptr)
        frame_color = color;
}

void Button::setColor(QPalette::ColorRole _role, QColor _color)
{
    QPalette pal = palette();
    pal.setColor(_role, _color);
    setPalette(pal);
}

void Button::setTextSize(QLabel *lbl, int size)
{
    QFont font = lbl->font();
    font.setPixelSize(size);
    lbl->setFont(font);
}

void Button::mousePressEvent(QMouseEvent *ev)
{
    my_clickPoint = ev->pos();
}

void Button::mouseReleaseEvent(QMouseEvent *ev)
{
    emit clicked();
}

void Button::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
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
    //painter.setBrush(QBrush(pal.background().color()));
    // ---------------
    // НАСТРОЙКА ФОРМЫ РАМКИ
    if(frame_form == Frame_Rectangle)
    {
        painter.drawRect(frame_width / 2, frame_width / 2, width() - frame_width, height() - frame_width);
    }
    else if(frame_form == Frame_Rounded)
    {
        painter.drawRoundedRect(frame_width / 2, frame_width / 2, width() - frame_width, height() - frame_width, 25, 25);
    }
    else if(frame_form == Frame_Circular)
    {
        painter.drawEllipse(frame_width / 2, frame_width / 2, width() - frame_width, height() - frame_width);
    }
    // ---------------
}
