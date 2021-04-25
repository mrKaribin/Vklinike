#ifndef ORDER_H
#define ORDER_H

#include "widget.h"
#include "button.h"
#include "Cards/cardslist.h"

#include <QLineEdit>
#include <QLayout>


struct OrderData
{
    int package_id = -1;
    int group_id = -1;
    int spec_id = -1;

    QString name;
    QString surname;
    QString patronimic;
    QString email;
    QString specialization;
    QString duration;
    int time;
    int cost;
    GlobalData::Valuta valuta;
};


class Order : public Widget
{
    Q_OBJECT
public:
    Order(OrderData _data);

private:
    void formating_label(QLabel *label);

    OrderData                       my_data;

    //CardsList                      *wgt_cards;
    QLabel                         *wgt_header;
    QLabel                         *wgt_fio;
    QLabel                         *wgt_specialization;
    QLabel                         *wgt_duration;
    QLabel                         *wgt_time;
    QLabel                         *wgt_cost;
    //QLabel                         *wgt_code_header;
    //QLineEdit                      *wgt_code;
    Button                         *wgt_accept;

    QSize                           size_label;

public slots:
    void pay();

signals:
    void returned();

};

#endif // ORDER_H
