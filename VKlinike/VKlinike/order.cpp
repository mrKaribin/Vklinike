#include "order.h"
#include "Cards/cards.h"
#include "socket.h"
#include "packer.h"
#include "viewer.h"
#include "browser.h"

#include <QDateTime>


Order::Order(OrderData _data) : Widget()
{
    using namespace GlobalData::interface;
    my_data = _data;
    QVBoxLayout *layout = new QVBoxLayout();
    //QHBoxLayout *layout_code = new QHBoxLayout();
    Cards *cards = new Cards();
    wgt_header = new QLabel();
    wgt_fio = new QLabel();
    wgt_specialization = new QLabel();
    wgt_duration = new QLabel();
    wgt_time = new QLabel();
    wgt_cost = new QLabel();
    //wgt_cards = new CardsList(cards, this);
    //wgt_code_header = new QLabel();
    //wgt_code = new QLineEdit();
    wgt_accept = new Button();
    size_label = QSize(GlobalData::screen::geometry.width() - indent * 2, row_size);

    Widget::setTextSize(wgt_header, text_size * 1.2);
    wgt_header->setAlignment(Qt::AlignCenter);
    formating_label(wgt_fio);
    formating_label(wgt_specialization);
    formating_label(wgt_duration);
    formating_label(wgt_time);
    formating_label(wgt_cost);
    wgt_accept->setFrame(true, GlobalData::Frame_Rounded, 3, color::blue);
    wgt_accept->setFixedSize(size_label.width(), row_size * 1.5);
    setFixedWidth(GlobalData::screen::geometry.width());
    //setFixedHeight();

    wgt_header->setText("Вы собираетесь приобрести:");
    wgt_fio->setText("Подписку на врача: " + _data.surname + " " + _data.name + " " + _data.patronimic);
    wgt_specialization->setText("Специализация: " + _data.specialization);
    wgt_duration->setText("Длительность подписки: " + _data.duration);
    wgt_time->setText("Время видеосвязи: " + QTime(_data.time / 60 / 60, _data.time / 60 % 60, _data.time % 60).toString());
    wgt_cost->setText("Стоимость: " + QString::number(_data.cost) + " " + _data.valuta.abbreviation);
    //wgt_code_header->setText("Секретный код карты: ");
    wgt_accept->setText("Подтвердить");

    //layout_code->addWidget(wgt_code_header);
    //layout_code->addStretch(0);
    //layout_code->addWidget(wgt_code);
    //layout_code->setMargin(0);
    //layout->addWidget(wgt_cards);
    //layout->addLayout(layout_code);
    layout->addWidget(wgt_header);
    layout->addWidget(wgt_fio);
    layout->addWidget(wgt_specialization);
    layout->addWidget(wgt_duration);
    layout->addWidget(wgt_time);
    layout->addWidget(wgt_cost);
    layout->addWidget(wgt_accept);
    layout->setSpacing(spacing);
    layout->setMargin(indent);
    setLayout(layout);
    Viewer *viewer = new Viewer(this);

    connect(wgt_accept, &Button::clicked, this, &Order::pay);
    connect(this, &Order::returned, viewer, &Viewer::back);
}

void Order::formating_label(QLabel *label)
{
    label->setFixedWidth(size_label.width());
    label->setAlignment(Qt::AlignLeft);
    label->setWordWrap(true);
}

void Order::pay()
{
    using namespace GlobalData::query;
    Packer packer;
    packer << my_data.email;
    packer << my_data.package_id;
    packer << my_data.group_id;
    packer << my_data.spec_id;
    GlobalData::socket->socket_write(prefix_new + payment_paypal, packer.result());
}

