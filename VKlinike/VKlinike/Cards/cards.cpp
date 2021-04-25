#include "cards.h"
#include "packer.h"


Cards::Cards() : Object()
{

}

void Cards::update()
{
    using namespace GlobalData::query;
    Packer packer;
    packer << GlobalData::currentLogin;
    packer << GlobalData::currentPassword;
    server_request(prefix_get + card, packer.result());
}

void Cards::server_reply(QString header, QByteArray body)
{
    using namespace GlobalData::query;
    if(header == prefix_reply + prefix_get + card)
        readFromBytes_Cards(body);
}

void Cards::readFromBytes_Cards(QByteArray array)
{
    int size = 0;
    my_data.clear();
    Unpacker unpacker(array);
    unpacker >> size;
    for(int i = 0; i < size; i++)
    {
        CardData new_data;
        unpacker >> new_data.id;
        unpacker >> new_data.number;
        unpacker >> new_data.month;
        unpacker >> new_data.year;
        unpacker >> new_data.name;
        my_data << new_data;
    }
    emit update_all_widgets(my_data);
}

void Cards::card_create(CardData _card)
{
    using namespace GlobalData::query;
    Packer packer;
    packer << GlobalData::currentLogin;
    packer << GlobalData::currentPassword;
    packer << _card.number;
    packer << _card.month;
    packer << _card.year;
    packer << _card.name;
    server_request(prefix_new + card, packer.result());

    my_data << _card;
    emit update_all_widgets(my_data);
}

void Cards::card_update(CardData _card)
{
    using namespace GlobalData::query;
    Packer packer;
    packer << GlobalData::currentLogin;
    packer << GlobalData::currentPassword;
    packer << _card.id;
    packer << _card.number;
    packer << _card.month;
    packer << _card.year;
    packer << _card.name;
    server_request(prefix_update + card, packer.result());

    for(int i = 0; i < my_data.size(); i++)
    {
        if(my_data[i].id == _card.id)
        {
            my_data[i].number = _card.number;
            my_data[i].month = _card.month;
            my_data[i].year = _card.year;
            my_data[i].name = _card.name;
        }
    }
    emit update_all_widgets(my_data);
}

void Cards::card_remove(int id)
{
    using namespace GlobalData::query;
    Packer packer;
    packer << GlobalData::currentLogin;
    packer << GlobalData::currentPassword;
    packer << id;
    server_request(prefix_remove + card, packer.result());

    for(int i = 0; i < my_data.size(); i++)
    {
        if(my_data[i].id == id)
            my_data.removeAt(i);
    }
    emit update_all_widgets(my_data);
}

