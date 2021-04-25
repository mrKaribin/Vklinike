#ifndef BUTTON_H
#define BUTTON_H

#include "globaldata.h"

#include <QLabel>
#include <QPainter>
#include <QApplication>


class Button : public QLabel
{
    Q_OBJECT
public:
    Button(QWidget* parent = nullptr);
    Button(QString text);
    Button(QPixmap pix);

    bool isFrame();

    void setFrame(bool b, GlobalData::FrameForm form = GlobalData::Frame_Null, int width = -1, QColor color = nullptr);
    void setColor(QPalette::ColorRole _role, QColor _color);
    void setTextSize(QLabel* lbl, int size);

private:
    void my_Initialize();

    bool                        frame = false;
    GlobalData::FrameForm       frame_form = GlobalData::Frame_Rectangle;
    int                         frame_width = 1;
    QColor                      frame_color = Qt::black;

    QPoint my_clickPoint;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;

signals:
    void clicked();

};

#endif // BUTTON_H
