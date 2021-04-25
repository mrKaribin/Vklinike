#ifndef SPECIALIZATIONS_H
#define SPECIALIZATIONS_H

#include "global.h"

#include <QObject>


class specializations
{
public:
    specializations(QString _name, QString _info, bool create = true)
    {
        my_fullInit = true;
        setDatas(_name, _info);
        if(create)
            insert();
        id();
    }

    specializations(QString _name, bool fullInit = false)
    {
        my_fullInit = fullInit;
        my_name = _name;
        id();
        if(my_fullInit)
            load();
    }

    specializations(int _id, bool fullInit = false)
    {
        my_fullInit = fullInit;
        my_id = _id;
        if(my_fullInit)
            load();
    }

    static QList <specializations*> loadAll()
    {
        QList <specializations*> result;
        QString str = "SELECT * FROM specializations ;";
        QSqlQuery query("CUSTOM_QUERY", *GLOBAL::database_current());
        DEBUG_LOG(str);
        if(!query.exec(str))
            GLOBAL::console_write("Ошибка выполнения SQL запроса: " + str + "\n");
        QSqlRecord record = query.record();
        while(query.next())
        {
            specializations* spec = new specializations(query.value(record.indexOf("name")).toString(),
                                                        query.value(record.indexOf("info")).toString(),
                                                        false);
            spec->setId(query.value(record.indexOf("id")).toInt());
            result << spec;
        }
        return result;
    }


    void load()
    {
        QSqlRecord record = sql::select(table_name, "*", "id = " + QString::number(my_id));
        setDatas(record.value("name").toString(),
                 record.value("info").toString());
    }

    void insert()
    {
        using namespace sql;
        QVector <Value> values;
        values << Value("name", quotes(my_name));
        values << Value("info", quotes(my_info));
        sql::insert(table_name, values);
    }

    void update()
    {
        using namespace sql;
        QVector <Value> values;
        values << Value("name", quotes(my_name));
        values << Value("info", quotes(my_info));
        sql::update(table_name, values, "id = " + QString::number(my_id));
    }

    void remove()
    {
        sql::remove(table_name, "id = " + QString::number(my_id));
    }



    void setId(int _id)
    {
        my_id = _id;
    }

    int id()
    {
        if(my_id == -1 && my_name != GLOBAL::null_str)
            my_id = sql::select(table_name, "id", "name = " + quotes(my_name)).value("id").toInt();
        return my_id;
    }

    QString name()
    {
        if(!my_fullInit && my_name == GLOBAL::null_str)
            my_name = sql::select(table_name, "name", "id = " + QString::number(my_id)).value("name").toString();
        return my_name;
    }

    QString info()
    {
        if(!my_fullInit && my_info == GLOBAL::null_str)
            my_info = sql::select(table_name, "info", "id = " + QString::number(my_id)).value("info").toString();
        return my_info;
    }


    void setDatas(QString _name, QString _info)
    {
        my_name = _name;
        my_info = _info;
    }

    QJsonObject toJson()
    {
        QJsonObject object
        {
            {"id", id()},
            {"name", name()}
            //,{"information", info()}
        };
        return object;
    }

private:
    QString             table_name          = "specializations";
    bool                my_fullInit;

    int                 my_id               = -1;
    QString             my_name             = GLOBAL::null_str;
    QString             my_info             = GLOBAL::null_str;
};

#endif // SPECIALIZATIONS_H
