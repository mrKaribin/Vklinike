#include "tabwidget.h"


TabWidget::TabWidget(QWidget *parent) : Widget(parent)
{
    using namespace GlobalData;
    using namespace GlobalData::interface;
    //ИНИЦИАЛИЗАЦИЯ ПЕРЕМЕННЫХ
        header_height = row_size * 3;
        header_width = screen::geometry.width() - indent * 2;
        tab_header_height = row_size * 2;
        header_indent = (header_height - tab_header_height) / 2;
        header_frame_thick = 2;
        header_scroll_geometry.setRect(header_frame_thick, header_indent, header_width - header_frame_thick * 2, header_height - header_indent * 2);
        marker_indent = header_indent / 2;
        marker_geometry_null.setRect(-tab_header_height, header_indent, tab_header_height, tab_header_height);

        service_thread = new QThread();
        header = new Widget(this);
        body = new Widget(this);
        Widget *header_scroll = new Widget(header);
        QVBoxLayout *layout = new QVBoxLayout();
        marker = new Widget(header_scroll);
        header_layout = new QHBoxLayout();
        currentPlace = nullptr;
    //------------------------
    //ЗАПОЛНЕНИЕ ДАННЫМИ

    //------------------------
    //НАСТРОЙКИ ФОРМАТИРОВАНИЯ
        header->setFixedSize(header_width, header_height);
        header->setFrame(true, Frame_Rectangle, header_frame_thick, color::blue);
        header_scroll->setFixedHeight(header_scroll_geometry.height());
        header_scroll->setMinimumWidth(header_width);
        header_scroll->setMoveableBorder(header_scroll_geometry);
        header_scroll->setMovable_horizontal(true);
        header_scroll->move(header_scroll_geometry.topLeft());
        body->setFixedWidth(header_width);
        marker->setColor(QPalette::Window, QColor(224, 255, 255, 50));
        marker->setFrame(true, Frame_Rounded, 4, color::blue);
        marker->setGeometry(marker_geometry_null);
    //------------------------
    //ФОРМИРОВАНИЕ LAYOUT
        header_layout->addStretch(0);
        header_layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        header_layout->setContentsMargins(header_indent, 0, header_indent, 0);
        header_layout->setSpacing(spacing);
        header_scroll->setLayout(header_layout);
        layout->addWidget(header);
        layout->addWidget(body);
        layout->setMargin(0);
        layout->setSpacing(spacing);
        setLayout(layout);
    //------------------------
    service_thread->start();
}

void TabWidget::addTab(QString name, Widget *place)
{
    Button *new_header = new Button(name);
    new_header->setFixedHeight(tab_header_height);
    new_header->setAlignment(Qt::AlignCenter);
    new_header->setColor(QPalette::Window, QColor(0, 0, 0, 0));
    setColor(new_header, QPalette::WindowText, GlobalData::interface::color::blue);
    header_layout->addWidget(new_header);
    header_layout->addStretch(0);
    header_layout->update();
    place->setParent(body);
    place->move(-GlobalData::screen::geometry.width(), 0);
    place->hide();
    places << Place(new_header, place);

    connect(new_header, SIGNAL(clicked()), this, SLOT(selectedTab()));

    //if(currentPlace == nullptr)
    //    selectedTab(name);
}

void TabWidget::selectedTab()
{
    Place *place;
    Button *sndr = (Button*)sender();
    for(int i = 0; i < places.size(); i++)
    {
        if(sndr == places[i].header)
            place = &places[i];
    }
    selectedTab(place);
}

void TabWidget::selectedTab(QString name)
{
    Place *place = nullptr;
    for(int i = 0; i < places.size(); i++)
    {
        if(name == places[i].header->text())
            place = &places[i];
    }
    if(place != nullptr)
        selectedTab(place);
}

void TabWidget::selectedTab(Place *place)
{
    using namespace GlobalData::interface;
    using namespace GlobalData;
    if(place == currentPlace)
        return;

    bool before = false;
    for(int i = 0; i < places.size(); i++)
    {
        if(currentPlace == &places[i])
            before = true;
        if(place == &places[i])
            break;
    }

    QPropertyAnimation* marker_animation = new QPropertyAnimation(marker, "geometry", service_thread);
    QPropertyAnimation* new_body_animation = new QPropertyAnimation(place->body, "geometry", service_thread);
    QPropertyAnimation* current_body_animation = nullptr;
    if(currentPlace != nullptr)
        current_body_animation = new QPropertyAnimation(currentPlace->body, "geometry", service_thread);

    marker_animation->setDuration(animation_duration);
    marker_animation->setEasingCurve(animation_curve);

    if(currentPlace != nullptr)
        marker_animation->setStartValue(marker->geometry());
    else
        marker_animation->setStartValue(marker_geometry_null);
    marker_animation->setEndValue(QRect(place->header->x() - marker_indent, place->header->y(), place->header->width() + marker_indent * 2, place->header->height()));

    if(currentPlace != nullptr)
    {
        current_body_animation->setDuration(animation_duration);
        current_body_animation->setEasingCurve(animation_curve);
        current_body_animation->setStartValue(currentPlace->body->geometry());
    }

    new_body_animation->setDuration(animation_duration);
    new_body_animation->setEasingCurve(animation_curve);
    new_body_animation->setEndValue(QRect(0, 0, place->body->width(), place->body->height()));

    if(before)
    {
        new_body_animation->setStartValue(QRect(screen::geometry.width(), 0, place->body->width(), place->body->height()));
        if(currentPlace != nullptr)
            current_body_animation->setEndValue(QRect(-screen::geometry.width(), 0, currentPlace->body->width(), currentPlace->body->height()));
    }
    else
    {
        new_body_animation->setStartValue(QRect(-screen::geometry.width(), 0, place->body->width(), place->body->height()));
        if(currentPlace != nullptr)
            current_body_animation->setEndValue(QRect(screen::geometry.width(), 0, currentPlace->body->width(), currentPlace->body->height()));
    }

    connect(marker_animation, &QPropertyAnimation::finished, marker_animation, &QPropertyAnimation::deleteLater);
    connect(new_body_animation, &QPropertyAnimation::finished, marker_animation, &QPropertyAnimation::deleteLater);
    if(currentPlace != nullptr)
    {
        connect(current_body_animation, &QPropertyAnimation::finished, marker_animation, &QPropertyAnimation::deleteLater);
        connect(current_body_animation, &QPropertyAnimation::finished, currentPlace->body, &Widget::hide);
    }

    setFixedHeight(header_height + spacing + place->body->maximumHeight());
    place->body->show();
    marker_animation->start();
    new_body_animation->start();
    if(currentPlace != nullptr)
        current_body_animation->start();
    currentPlace = place;
}
