#ifndef CARDEDITOR_H
#define CARDEDITOR_H

#include "Cards/cardsdata.h"
#include "widget.h"
#include "button.h"

#include <QLayout>
#include <QLineEdit>

class Cards;


class CardEditor : public Widget
{
    Q_OBJECT
public:
    CardEditor(Cards *_object, CardData _data = CardData(), Widget *parent = nullptr);

private:
    void                        initializing();
    void                        formating();
    void                        formating_line(QLineEdit *line, QLabel *label);
    void                        filling();
    void                        linking();

    Cards                      *my_object;
    CardData                    my_data;

    QVBoxLayout                *layout;
    QLineEdit                  *wgt_number;
    QLabel                     *wgt_number_header;
    QLineEdit                  *wgt_date;
    QLabel                     *wgt_date_header;
    QLineEdit                  *wgt_name;
    QLabel                     *wgt_name_header;
    Button                     *wgt_save;

    QString                     str_number_header               = "введите номер карты";
    QString                     str_date_header                 = "введите срок действия карты";
    QString                     str_name_header                 = "введите имя держателя карты";

    QSize                       size_line;
    QSize                       size_header;
    int                         text_line_size;
    int                         text_header_size;
    int                         margin;
    int                         spacing;

public slots:
    void                        save();

signals:
    void created(CardData);
    void updated(CardData);
    void returning();
};

#endif // CARDEDITOR_H
