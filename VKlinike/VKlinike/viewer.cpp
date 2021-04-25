#include "viewer.h"
#include "mainwidget.h"


Viewer::Viewer(Widget *body) : Widget(GlobalData::widget_main)
{
    using namespace GlobalData::interface;
    using namespace GlobalData;
    my_body = body;
    my_body_area = new Widget(this);
    my_header = new Widget(this);
    my_header_back = new Button(my_header);
    my_body->setParent(my_body_area);
    size_header = QSize(screen::geometry.width(), screen::geometry.height() * 0.09);
    geometry_body.setRect(0, size_header.height(), screen::geometry.width(), screen::geometry.height() - size_header.height());
    geometry_picture.setRect(spacing, indent, size_header.height() - indent * 2, size_header.height() - indent * 2);

    my_header_back->setPixmap(QPixmap(directory::icon + directory::icons::back).scaled(row_size, row_size));
    my_header_back->setFixedSize(row_size, row_size);
    my_header_back->setGeometry(geometry_picture);

    my_header->setFixedSize(size_header);
    my_body_area->setFixedSize(geometry_body.size());
    my_body_area->setGeometry(geometry_body);
    my_body->move(0, 0);
    my_body->setMovable_vertical(true);
    my_body->setMoveableBorder(QRect(QPoint(0, 0), geometry_body.size()));
    setFixedSize(screen::geometry.size());
    show();

    GlobalData::widget_main->menuBar_Close();
    GlobalData::widget_main->widgets_Swift(this, MainWidget::Swift_toTop);

    connect(my_header_back, &Button::clicked, this, &Viewer::back);
    connect(this, &Viewer::returned, GlobalData::widget_main, &MainWidget::returning);
}

void Viewer::back()
{
    emit returned();
    QTimer::singleShot(1000, this, &Viewer::deleteLater);
}
