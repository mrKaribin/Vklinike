#ifndef CARDS_H
#define CARDS_H

#include "object.h"
#include "Cards/cardsdata.h"


class Cards : public Object
{
    Q_OBJECT
public:
    Cards();

private:
    QList <CardData>            my_data;

public slots:
    void                        update();
    void                        server_reply(QString header, QByteArray body) override;
    void                        readFromBytes_Cards(QByteArray array);

    void                        card_create(CardData card);
    void                        card_update(CardData card);
    void                        card_remove(int id);

signals:
    void update_all_widgets(QList <CardData>);
};

#endif // CARDS_H
