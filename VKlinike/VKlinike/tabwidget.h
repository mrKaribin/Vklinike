#ifndef TABWIDGET_H
#define TABWIDGET_H

#include "widget.h"
#include "button.h"

#include <QThread>
#include <QLayout>
#include <QPropertyAnimation>


struct Place
{
    Place(){}
    Place(Button* _header, Widget* _body)
    {
        header = _header;
        body = _body;
    }

    Button* header;
    Widget* body;
};


class TabWidget : public Widget
{
    Q_OBJECT
public:
    TabWidget(QWidget* parent = nullptr);

    void addTab(QString name, Widget* place);
    void selectedTab(Place* place);

private:
    QVector <Place>             places;

    Place                      *currentPlace;

    QThread                    *service_thread;

    QHBoxLayout                *header_layout;

    Widget                     *header,
                               *body,
                               *marker;

    QRect                       header_scroll_geometry,
                                marker_geometry_null;

    int                         header_height,
                                header_width,
                                header_indent,
                                header_frame_thick;

    int                         tab_header_height;

    int                         marker_indent;

public slots:
    void selectedTab();
    void selectedTab(QString name);

};

#endif // TABWIDGET_H
