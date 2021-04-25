#include "cardeditor.h"
#include "Cards/cards.h"
#include "viewer.h"

CardEditor::CardEditor(Cards *_object, CardData _data, Widget *parent) : Widget(parent)
{
    my_object = _object;
    my_data = _data;
    initializing();
    formating();
    filling();
    linking();
    if(parent == nullptr)
    {
        Viewer* viewer = new Viewer(this);
        connect(this, &CardEditor::returning, viewer, &Viewer::back);
    }
}

void CardEditor::initializing()
{
    using namespace GlobalData;
    layout = new QVBoxLayout();
    wgt_number = new QLineEdit();
    wgt_number_header = new QLabel();
    wgt_date = new QLineEdit();
    wgt_date_header = new QLabel();
    wgt_name = new QLineEdit();
    wgt_name_header = new QLabel();
    wgt_save = new Button();

    size_line = QSize(screen::geometry.width() - interface::indent * 2, interface::row_size * 1.2);
    size_header = QSize(screen::geometry.width() - interface::indent * 2, interface::row_size * 0.6);
    text_line_size = interface::text_size;
    text_header_size = interface::text_size * 0.6;
    margin = interface::indent;
    spacing = interface::spacing;

    connect(wgt_save, &Button::clicked, this, &CardEditor::save);
    connect(this, &CardEditor::created, my_object, &Cards::card_create);
    connect(this, &CardEditor::updated, my_object, &Cards::card_update);
}

void CardEditor::formating()
{
    formating_line(wgt_number, wgt_number_header);
    formating_line(wgt_date, wgt_date_header);
    formating_line(wgt_name, wgt_name_header);
    wgt_date->setAlignment(Qt::AlignCenter);
    wgt_save->setFixedSize(size_line.width(), GlobalData::interface::row_size * 1.5);
    wgt_save->setFrame(true, GlobalData::Frame_Rounded, 3, GlobalData::interface::color::blue);
}

void CardEditor::formating_line(QLineEdit *line, QLabel *header)
{
    line->setFixedSize(size_line);
    Widget::setTextSize(line, text_line_size);

    header->setFixedSize(size_header);
    Widget::setTextSize(header, text_header_size);
}

void CardEditor::filling()
{
    wgt_save->setText("Сохранить");
    wgt_number->setText(my_data.number);
    wgt_date->setText(my_data.month + " / " + my_data.year);
    wgt_name->setText(my_data.name);

    wgt_number_header->setText(str_number_header);
    wgt_date_header->setText(str_date_header);
    wgt_name_header->setText(str_name_header);
}

void CardEditor::linking()
{
    layout->addStretch(0);
    layout->addWidget(wgt_number);
    layout->addWidget(wgt_number_header);
    layout->setAlignment(wgt_number_header, Qt::AlignCenter);
    layout->addSpacing(spacing);

    layout->addWidget(wgt_date);
    layout->addWidget(wgt_date_header);
    layout->setAlignment(wgt_date_header, Qt::AlignCenter);
    layout->addSpacing(spacing);

    layout->addWidget(wgt_name);
    layout->addWidget(wgt_name_header);
    layout->setAlignment(wgt_name_header, Qt::AlignCenter);
    layout->addSpacing(spacing);

    layout->addWidget(wgt_save);
    layout->addStretch(0);
    layout->setMargin(margin);
    setLayout(layout);
}

void CardEditor::save()
{
    my_data.number = wgt_number->text();
    my_data.month = wgt_date->text().mid(0, 2);
    my_data.year = wgt_date->text().mid(5, 2);
    my_data.name = wgt_name->text();

    if(my_data.id == -1)
        emit created(my_data);
    else
        emit updated(my_data);
    emit returning();
}
