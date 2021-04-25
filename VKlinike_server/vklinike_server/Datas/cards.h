#ifndef CARDS_H
#define CARDS_H

#include "global.h"


class cards
{
public:
    cards(int _user_id, QString _number, QString _month, QString _year, QString _name, bool create = true)
    {
        my_fullInit = true;
        setDatas(_user_id, _number, _month, _year, _name);
        if(create)
        {
            insert();
            my_id = sql::select(table_name, "id", "rowid = last_insert_rowid()").value(0).toInt();
        }
    }

    cards(int _id, bool fullInit = true)
    {
        my_fullInit = fullInit;
        my_id = _id;
        if(my_fullInit)
            load();
    }

    static QList <cards*> findCards(int user_id)
    {
        QList <cards*> result;
        QString str = "SELECT * FROM cards WHERE user_id = " + QString::number(user_id) + " ;";
        QSqlQuery query("CUSTOM_QUERY", *GLOBAL::database_current());
        DEBUG_LOG(str);
        if(!query.exec(str))
            GLOBAL::console_write("Ошибка выполнения SQL запроса: " + str + "\n");
        QSqlRecord record = query.record();
        while(query.next())
        {
            cards *card = new cards(query.value(record.indexOf("user_id")).toInt(),
                                query.value(record.indexOf("number")).toString(),
                                query.value(record.indexOf("month")).toString(),
                                query.value(record.indexOf("year")).toString(),
                                query.value(record.indexOf("name")).toString(),
                                false);
            card->setId(query.value(record.indexOf("id")).toInt());
            result << card;
        }
        return result;
    }


    void load()
    {
        QSqlRecord record = sql::select(table_name, "*", "id = " + QString::number(my_id));
        setDatas(record.value("user_id").toInt(),
                 record.value("number").toString(),
                 record.value("month").toString(),
                 record.value("year").toString(),
                 record.value("name").toString());
    }

    void insert()
    {
        using namespace sql;
        QVector <Value> values;
        values << Value("user_id", QString::number(my_user_id));
        values << Value("number", quotes(my_number));
        values << Value("month", quotes(my_month));
        values << Value("year", quotes(my_year));
        values << Value("name", quotes(my_name));
        sql::insert(table_name, values);
    }

    void update()
    {
        using namespace sql;
        QVector <Value> values;
        values << Value("user_id", QString::number(my_user_id));
        values << Value("number", quotes(my_number));
        values << Value("month", quotes(my_month));
        values << Value("year", quotes(my_year));
        values << Value("name", quotes(my_name));
        sql::update(table_name, values, "id = " + QString::number(my_id));
    }

    void remove()
    {
        sql::remove(table_name, "id = " + QString::number(my_id));
    }


    void setId(int id)
    {
        my_id = id;
    }

    int id()
    {
        return my_id;
    }

    int user_id()
    {
        if(!my_fullInit && my_user_id == -1)
            my_user_id = sql::select(table_name, "user_id", "id = " + QString::number(my_id)).value("user_id").toInt();
        return my_user_id;
    }

    QString number()
    {
        if(!my_fullInit && my_number == GLOBAL::null_str)
            my_number = sql::select(table_name, "number", "id = " + QString::number(my_id)).value("number").toString();
        return my_number;
    }

    QString month()
    {
        if(!my_fullInit && my_month == GLOBAL::null_str)
            my_month = sql::select(table_name, "month", "id = " + QString::number(my_id)).value("month").toString();
        return my_month;
    }

    QString year()
    {
        if(!my_fullInit && my_year == GLOBAL::null_str)
            my_year = sql::select(table_name, "year", "id = " + QString::number(my_id)).value("year").toString();
        return my_year;
    }

    QString name()
    {
        if(!my_fullInit && my_name == GLOBAL::null_str)
            my_name = sql::select(table_name, "name", "id = " + QString::number(my_id)).value("name").toString();
        return my_name;
    }


    void setDatas(int _user_id, QString _number, QString _month, QString _year, QString _name)
    {
        my_user_id = _user_id;
        my_number = _number;
        my_month = _month;
        my_year = _year;
        my_name = _name;
    }

private:
    QString             table_name              = "cards";
    bool                my_fullInit;

    int                 my_id                   = -1;
    int                 my_user_id              = -1;
    QString             my_number               = GLOBAL::null_str;
    QString             my_month                = GLOBAL::null_str;
    QString             my_year                 = GLOBAL::null_str;
    QString             my_name                 = GLOBAL::null_str;
};

#endif // CARDS_H
