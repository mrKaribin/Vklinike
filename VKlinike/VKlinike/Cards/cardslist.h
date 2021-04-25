#ifndef CARDSLIST_H
#define CARDSLIST_H

#include "widget.h"
#include "cardsdata.h"
#include "button.h"

#include <QLayout>
#include <QCheckBox>

class Cards;
class CardsList;


class CardWidget : public Widget
{
    Q_OBJECT
public:
    CardWidget(CardData _data);

private:
    CardData                my_data;

    QCheckBox              *wgt_check;
    Button                 *wgt_remove;
    Button                 *wgt_edit;

public slots:
    void                    uncheckAllAlso(int id);
    void                    check(bool state);
    void                    edit();
    void                    remove();

signals:
    void checked(int);
    void removed(int);
    void edited(int);
};


class CardsList : public Widget
{
    Q_OBJECT
public:
    CardsList(Cards *_object, Widget *parent = nullptr);

    CardData                currentCard();

private:
    Cards                  *my_object;
    QList <CardData>        my_data;

    QVBoxLayout            *layout_cards;
    Button                 *wgt_create;

    int                     checked                 = -1;

public slots:
    void                    setData(QList <CardData> _data);

    void                    card_checked(int id);
    void                    card_edit(int id);
    void                    card_create();

signals:
    void                    checked_card_id(int id);
    void                    update();

};

#endif // CARDSLIST_H
