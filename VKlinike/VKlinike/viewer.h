#ifndef VIEWER_H
#define VIEWER_H

#include "widget.h"
#include "button.h"


class Viewer : public Widget
{
    Q_OBJECT
public:
    Viewer(Widget *body);

private:
    Widget*                 my_header;
    Button*                 my_header_back;
    Widget*                 my_body;
    Widget*                 my_body_area;

    QSize                   size_header;
    QRect                   geometry_body;
    QRect                   geometry_picture;

public slots:
    void back();

signals:
    void returned();
};

#endif // VIEWER_H
