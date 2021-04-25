#ifndef CARDSDATA_H
#define CARDSDATA_H

#include <QObject>


struct CardData
{
    int id = -1;
    QString number;
    QString month;
    QString year;
    QString name;
};

#endif // CARDSDATA_H
