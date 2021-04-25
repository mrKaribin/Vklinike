#ifndef PACKER_H
#define PACKER_H

#include "global.h"

#include <QObject>
#include <QIODevice>
#include <QDataStream>


class Packer
{
public:
    Packer()
    {
        my_array = new QByteArray();
        my_stream = new QDataStream(my_array, QIODevice::WriteOnly);
        my_stream->setVersion(QDataStream::Qt_5_12);
    }

    template <typename TYPE>
    void operator <<(TYPE value)
    {
        *my_stream << value << GLOBAL::separator;
    }

    QByteArray result()
    {
        QChar c;
        my_array->remove(my_array->size() - 4, 4);
        return *my_array;
    }

private:
    QByteArray         *my_array;
    QDataStream        *my_stream;

};


class Unpacker
{
public:
    Unpacker(QByteArray _array)
    {
        my_array = new QByteArray(_array);
        my_stream = new QDataStream(my_array, QIODevice::ReadOnly);
        my_stream->setVersion(QDataStream::Qt_5_12);

        QByteArray array;
        QDataStream stream(&array, QIODevice::WriteOnly);
        stream.setVersion(QDataStream::Qt_5_12);
        stream << GLOBAL::separator;
        int sector_start = 0;
        int base_index = array.size() - 1;

        if(my_array->size() > array.size())
        for(int i = base_index; i < my_array->size(); i++)
        {
            bool accordance = true;
            for(int j = base_index; j >= 0; j--)
            {
                char x1 = my_array->at(i - base_index + j),
                     x2 = array.at(j);
                if(x1 != x2)
                    accordance = false;
            }
            if(i == my_array->size() - 1)
            {
                accordance = true;
                i = i + 4;
            }
            if(accordance)
            {
                int sector_lenth = i - array.size() + 1 - sector_start;
                char *result = new char[sector_lenth];
                if(my_stream->readRawData(result, sector_lenth) != -1)
                {
                    my_sectors << QByteArray(result, sector_lenth);
                    my_stream->skipRawData(array.size());
                }
                sector_start = i + 1;
            }
        }
    }

    template <typename TYPE>
    void operator >>(TYPE &value)
    {
        if(my_sectors.isEmpty())
            return;
        QByteArray array = my_sectors.first();
        my_sectors.remove(0);
        QDataStream stream(&array, QIODevice::ReadOnly);
        stream.setVersion(QDataStream::Qt_5_12);
        stream >> value;
    }

private:
    QByteArray             *my_array;
    QVector <QByteArray>    my_sectors;
    QDataStream            *my_stream;

};

#endif // PACKER_H
