#include "messageswidget.h"
#include "Messages/messages.h"
#include "mainwidget.h"
#include "Dialog/dialog.h"
#include "viewer.h"

#include <QLayout>
#include <QThread>


MW_Message::MW_Message(MessagesWidget* parent, DialogPreviewData data) : Button()
{
    using namespace GlobalData;
    using namespace GlobalData::directory;
    //ИНИЦИАЛИЗАЦИЯ ПЕРЕМЕННЫХ
        my_data = data;
        int my_height = interface::row_size * 3 + interface::spacing * 2;
        int image_size = my_height - interface::indent * 2;
        image = new Button();
        header = new QLabel();
        specialization = new QLabel();
        lastMessage = new QLabel();
        QHBoxLayout* layout = new QHBoxLayout();
        QVBoxLayout* layout_data = new QVBoxLayout();
    //------------------------
    //ЗАПОЛНЕНИЕ ДАННЫМИ
        if(data.photo.isNull())
        {
            if(currentMode == GlobalData::Mode_Doctor)
                data.photo = QPixmap(directory::image + images::patient);
            else
                data.photo = QPixmap(directory::image + images::doctor);
        }
        image->setPixmap(data.photo.scaled(image_size, image_size, Qt::KeepAspectRatioByExpanding));
        //image->setPixmap(QPixmap(GlobalData::directory::image + images::patient).scaled(image_size, image_size));
        header->setText(data.name + ((GlobalData::currentMode == GlobalData::Mode_Doctor) ? ("") : (" " + data.patronimic)));
        specialization->setText("Специализация: " + data.specialization);
        lastMessage->setText(data.lastMessage.sender_name + ": " + data.lastMessage.message);
    //------------------------
    //НАСТРОЙКИ ФОРМАТИРОВАНИЯ
        setTextSize(header, interface::text_size);
        setTextSize(specialization, interface::text_size * 0.7);
        setTextSize(lastMessage, interface::text_size * 0.7);
        header->setFixedHeight(interface::row_size);
        specialization->setFixedHeight(interface::row_size);
        lastMessage->setFixedHeight(interface::row_size);
        lastMessage->setMaximumWidth(screen::geometry.width() * 0.6);
        image->setFixedSize(image_size, image_size);
        setFrame(true, Frame_Rectangle, 4, interface::color::blue);
        setFixedWidth(screen::geometry.width() - interface::indent * 2);
        setFixedHeight(my_height);
    //------------------------
    //ФОРМИРОВАНИЕ LAYOUT
        layout_data->addWidget(header);
        layout_data->addWidget(specialization);
        layout_data->addWidget(lastMessage);
        layout_data->setAlignment(Qt::AlignLeft);
        layout_data->setMargin(0);
        layout_data->setSpacing(interface::indent_small);
        layout->addWidget(image);
        layout->addLayout(layout_data);
        layout->setMargin(interface::indent_small);
        layout->setSpacing(interface::indent_small);
        setLayout(layout);
    //------------------------
    connect(image, &Button::clicked, this, &MW_Message::profileOpen);
    connect(this, &Button::clicked, this, &MW_Message::dialogOpen);
}

void MW_Message::profileOpen()
{
    using namespace GlobalData;
    if(GlobalData::currentMode == GlobalData::Mode_Patient)
    {
        Widget *widget = new Widget();
        MainWidget::create_profile_doctor(widget, my_data.email, GlobalData::Output_Guest);
        Viewer *viewer = new Viewer(widget);
    }
    else if(GlobalData::currentMode == GlobalData::Mode_Doctor)
    {
        Widget *widget = new Widget();
        MainWidget::create_profile_patient(widget, my_data.email, GlobalData::Output_Guest);
        Viewer *viewer = new Viewer(widget);
    }
}

void MW_Message::dialogOpen()
{
    Dialog* new_dialog = new Dialog(my_data.id);
    connect(new_dialog->widget(), &DialogWidget::returning, GlobalData::widget_main, &MainWidget::returning);
}


MW_Filter::MW_Filter(MessagesWidget* parent)
{
    using namespace GlobalData;
    //ИНИЦИАЛИЗАЦИЯ ПЕРЕМЕННЫХ
        margin = interface::indent;
        spasing = interface::spacing;
        header_height = interface::row_size * 1.5;
        header_text_size = interface::text_size * 0.8;
        body_box_height = interface::row_size;
        body_text_size = interface::text_size * 0.8;
        body_margin = interface::indent * 2;
        body_spasing = interface::indent * 2;
        size_closed = QSize(screen::geometry.width() - interface::indent * 2, header_height + margin * 2);
        size_opened = QSize(screen::geometry.width() - interface::indent * 2, header_height + body_box_height + margin * 2 + body_margin * 2 + spasing);

        service_thread = new QThread();
        header = new Button(this);
        header_icon = new QLabel(header);
        header_text = new QLabel(header);
        body = new Widget(this);
        box_children = new QCheckBox(body);
        box_adult = new QCheckBox(body);
        layout_body_editable = new QGridLayout();
        QVBoxLayout* layout = new QVBoxLayout();
        QHBoxLayout* layout_header = new QHBoxLayout();
        QVBoxLayout* layout_body = new QVBoxLayout();
        QGridLayout* layout_body_main = new QGridLayout();
    //------------------------
    //ЗАПОЛНЕНИЕ ДАННЫМИ
        header_icon->setPixmap(QPixmap(directory::icon + directory::icons::expand).scaled(header_text_size, header_text_size));
        header_text->setText("Развернуть фильтры");
        box_children->setText("Детские");
        box_children->setChecked(true);
        box_adult->setText("Взрослые");
        box_adult->setChecked(true);
    //------------------------
    //НАСТРОЙКИ ФОРМАТИРОВАНИЯ
        header_icon->setFixedSize(header_text_size, header_text_size);
        header_text->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        configurateBox(box_children);
        configurateBox(box_adult);
        setTextSize(header_text, header_text_size);
        setMinimumSize(size_closed);
        setMaximumSize(size_closed.width()  , screen::geometry.height() / 2);
        setFixedWidth(size_closed.width());
        resize(size_closed);
        body->setFrame(true, Frame_Rectangle, 2, interface::color::blue);
        body->hide();
    //------------------------
    //ФОРМИРОВАНИЕ LAYOUT
        layout_header->addStretch(interface::spacing);
        layout_header->addWidget(header_icon);
        layout_header->addWidget(header_text);
        layout_header->addStretch(interface::spacing);
        layout_header->setMargin(0);
        layout_header->setSpacing(margin);
        header->setLayout(layout_header);
        layout_body_main->addWidget(box_children, 0, 0);
        layout_body_main->addWidget(box_adult, 0, 1);
        layout_body_main->setMargin(0);
        //layout_body_main->setSpacing(spasing);
        layout_body_editable->setMargin(0);
        //layout_body_editable->setSpacing(spasing);
        layout_body->addLayout(layout_body_main);
        layout_body->addLayout(layout_body_editable);
        layout_body->setMargin(body_margin);
        layout_body->setSpacing(body_spasing);
        body->setLayout(layout_body);
        layout->addWidget(header);
        layout->addStretch(0);
        layout->addWidget(body);
        layout->setMargin(margin);
        layout->setSpacing(spasing);
        setLayout(layout);
    //------------------------
        connect(header, &Button::clicked, this, &MW_Filter::open);
        connect(box_children, &QCheckBox::stateChanged, this, &MW_Filter::filterChanged);
        connect(box_adult, &QCheckBox::stateChanged, this, &MW_Filter::filterChanged);
}

void MW_Filter::configurateBox(QCheckBox *box)
{
    box->setFixedHeight(body_box_height);
    QFont font = box->font();
    font.setPixelSize(body_text_size);
    box->setFont(font);
}

void MW_Filter::updateFilters(QVector <QString> _filters)
{
    QVector <QCheckBox*> widgets;
    while(QLayoutItem* item = layout_body_editable->itemAt(0))
    {
        layout_body_editable->removeItem(item);
        layout_body_editable->removeWidget(item->widget());
        item->widget()->deleteLater();
        delete (item);
    }

    for(int i = 0; i < _filters.size(); i++)
    {
        QCheckBox* new_box = new QCheckBox(_filters[i], body);
        configurateBox(new_box);
        connect(new_box, &QCheckBox::stateChanged, this, &MW_Filter::filterChanged);
        widgets << new_box;
    }

    for(int i = 0; i < widgets.size(); i++)
    {
        layout_body_editable->addWidget(widgets[i], i / 2, i % 2);
    }
    layout_body_editable->update();
    checkBoxes = widgets;
    size_opened.setHeight(header_height + body_box_height + margin * 2 + spasing + (checkBoxes.size() / 2 + (checkBoxes.size() % 2) * 1) * (body_box_height + spasing));
}

void MW_Filter::filterChanged(int i)
{
    Filter filter;
    filter.forChild = box_children->isChecked();
    filter.forAdult = box_adult->isChecked();
    for(int i = 0; i < checkBoxes.size(); i++)
    {
        if(checkBoxes[i]->isChecked())
            filter.custom << checkBoxes[i]->text();
    }
    emit changed(filter);
}

void MW_Filter::open()
{
    using namespace GlobalData::interface;
    using namespace GlobalData::directory;
    disconnect(header, &Button::clicked, this, &MW_Filter::open);
    connect(header, &Button::clicked, this, &MW_Filter::close);

    header_text->setText("Свернуть фильтры");
    header_icon->setPixmap(QPixmap(icon + icons::turn).scaled(header_text_size, header_text_size));
    body->show();

    resize(size_closed);
    //QPropertyAnimation* animation = createAnimation_geometry(QRect(pos(), size_closed), QRect(pos(), size_opened), animation_duration, service_thread);
    //connect(animation, &QPropertyAnimation::finished, body, &Widget::show);
    //animation->start();
}

void MW_Filter::close()
{
    using namespace GlobalData::interface;
    using namespace GlobalData::directory;
    connect(header, &Button::clicked, this, &MW_Filter::open);
    disconnect(header, &Button::clicked, this, &MW_Filter::close);

    header_icon->setPixmap(QPixmap(icon + icons::expand).scaled(header_text_size, header_text_size));
    header_text->setText("Развернуть фильтры");
    body->hide();

    resize(size_opened);
    //QPropertyAnimation* animation = createAnimation_geometry(QRect(pos(), size_opened), QRect(pos(), size_closed), animation_duration, service_thread);
    //connect(animation, &QPropertyAnimation::finished, body, &Widget::hide);
    //animation->start();
}


MessagesWidget::MessagesWidget(Messages* _object, DialogsData _data, Widget* parent)
{
    using namespace GlobalData;
    my_data = _data;
    //ИНИЦИАЛИЗАЦИЯ ПЕРЕМЕННЫХ
        filter = new MW_Filter(this);
        layout = new QVBoxLayout();
        QVBoxLayout* layout_main = new QVBoxLayout();
    //------------------------
    //ЗАПОЛНЕНИЕ ДАННЫМИ
    //------------------------
    //НАСТРОЙКИ ФОРМАТИРОВАНИЯ
    //------------------------
    //ФОРМИРОВАНИЕ LAYOUT
        layout_main->addWidget(filter);
        layout_main->addStretch(0);
        layout_main->addLayout(layout);
        layout_main->setMargin(0);
        layout_main->setSpacing(interface::indent_small);
        layout_main->setAlignment(Qt::AlignHCenter);
        setLayout(layout_main);
    //------------------------
    connect(filter, &MW_Filter::changed, this, &MessagesWidget::filtersChanged);

    my_filter.custom << "ALL";
    my_filter.forAdult = true;
    my_filter.forChild = true;
    setData(_data);
    reloadLayout();
}

void MessagesWidget::setData(DialogsData _data)
{
    messagesChange(_data.messages);
}

void MessagesWidget::messagesChange(QVector <DialogPreviewData> _data)
{
    my_data.messages.clear();
    my_data.messages = _data;
    QVector <QString> filters;
    for(int i = 1; i < _data.size(); i++)
    {
        bool available = false;
        for(int j = 0; j < filters.size(); j++)
            if(_data[i].specialization == filters[j])
            {
                available = true;
                break;
            }
        if(!available)
            filters << _data[i].specialization;
    }
    reloadLayout();
    filter->updateFilters(filters);
}

void MessagesWidget::filtersChanged(Filter _filter)
{
    my_filter = _filter;
    if(my_filter.custom.size() == 0)
        my_filter.custom << "ALL";
    reloadLayout();
}

void MessagesWidget::reloadLayout()
{
    while(QLayoutItem* item = layout->itemAt(0))
    {
        layout->removeItem(item);
        layout->removeWidget(item->widget());
        item->widget()->deleteLater();
        delete (item);
    }

    for(int i = 0; i < my_data.messages.size(); i++)
        for(int j = 0; j < my_filter.custom.size(); j++)
            if(((my_data.messages[i].forChild && my_filter.forChild ) || (!my_data.messages[i].forChild && my_filter.forAdult)) && (my_data.messages[i].specialization == my_filter.custom[j] || my_filter.custom[j] == "ALL"))
            {
                MW_Message* new_message = new MW_Message(this, my_data.messages[i]);
                messages << new_message;
                layout->addWidget(new_message);
            }
    layout->update();
    repaint();
}
