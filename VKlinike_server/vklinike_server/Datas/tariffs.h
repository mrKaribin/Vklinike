#ifndef TARIFFS_H
#define TARIFFS_H

#include "global.h"


class tariffs
{
public:
    tariffs(int _package_id, int _cost, QString _valuta, int _time, bool create = true)
    {
        my_fullInit = true;
        setDatas(_package_id, _cost, _valuta, _time);
        if(create)
            insert();
        id();
    }

    tariffs(int _id, bool fullInit = true)
    {
        my_fullInit = fullInit;
        my_id = _id;
        if(my_fullInit)
            load();
    }

    static QList <tariffs*> findTariffs(int package_id)
    {
        QList <tariffs*> result;
        QString str = "SELECT * FROM tariffs WHERE package_id = " + QString::number(package_id) + ";";
        QSqlQuery query("CUSTOM_QUERY", *GLOBAL::database_current());
        DEBUG_LOG(str);
        if(!query.exec(str))
            GLOBAL::console_write("Ошибка выполнения SQL запроса: " + str + "\n");
        QSqlRecord record = query.record();
        while(query.next())
        {
            result << new tariffs(package_id,
                                  query.value(record.indexOf("cost")).toInt(),
                                  query.value(record.indexOf("valuta")).toString(),
                                  query.value(record.indexOf("time")).toInt(),
                                  false);
        }
        return result;
    }


    void load()
    {
        QSqlRecord record = sql::select(table_name, "*", "id = " + QString::number(my_id));
        setDatas(record.value("package_id").toInt(),
                 record.value("cost").toInt(),
                 record.value("valuta").toString(),
                 record.value("time").toInt());
    }

    void insert()
    {
        using namespace sql;
        QVector <Value> values;
        values << Value("package_id", QString::number(my_package_id));
        values << Value("cost", QString::number(my_cost));
        values << Value("valuta", quotes(my_valuta));
        values << Value("time", QString::number(my_time));
        sql::insert(table_name, values);
    }

    void update()
    {
        using namespace sql;
        QVector <Value> values;
        values << Value("package_id", QString::number(my_package_id));
        values << Value("cost", QString::number(my_cost));
        values << Value("valuta", quotes(my_valuta));
        values << Value("time", QString::number(my_time));
        sql::update(table_name, values, "id = " + QString::number(my_id));
    }

    void remove()
    {
        sql::remove(table_name, "id = " + QString::number(my_id));
    }


    int id()
    {
        if(my_id == -1 && my_package_id != -1 && my_cost != -1 && my_valuta != -1 && my_time != -1)
        {
            QString where = "package_id = %1 AND cost = %2 AND valuta = %3 AND time = %4";
            where = where.arg(QString::number(my_package_id))
                         .arg(QString::number(my_cost))
                         .arg(quotes(my_valuta))
                         .arg(QString::number(my_time));
            my_id = sql::select(table_name, "id", where).value("id").toInt();
        }
        return my_id;
    }

    void setId(int _id)
    {
        my_id = _id;
    }

    int package_id()
    {
        if(!my_fullInit && my_package_id == -1)
            my_package_id = sql::select(table_name, "package_id", "id = " + QString::number(my_id)).value("package_id").toInt();
        return my_package_id;
    }

    int cost()
    {
        if(!my_fullInit && my_cost == -1)
            my_cost = sql::select(table_name, "cost", "id = " + QString::number(my_id)).value("cost").toInt();
        return my_cost;
    }

    QString valuta()
    {
        if(!my_fullInit && my_valuta == -1)
            my_valuta = sql::select(table_name, "valuta", "id = " + QString::number(my_id)).value("valuta").toString();
        return my_valuta;
    }

    int time()
    {
        if(!my_fullInit && my_time == -1)
            my_time = sql::select(table_name, "time", "id = " + QString::number(my_id)).value("time").toInt();
        return my_time;
    }


    void setDatas(int _package_id, int _cost, QString _valuta, int _time)
    {
        my_package_id = _package_id;
        my_cost = _cost;
        my_valuta = _valuta;
        my_time = _time;
    }

    static tariffs& createFromJson(QJsonObject object, bool create = false)
    {
        QJsonObject::iterator itr_id = object.find("id");
        QJsonObject::iterator itr_package_id = object.find("package_id");
        QJsonObject::iterator itr_cost = object.find("cost");
        QJsonObject::iterator itr_valuta = object.find("valuta");
        QJsonObject::iterator itr_time = object.find("time");

        tariffs *tariff = new tariffs(
                    (itr_package_id != object.end()) ? (itr_package_id.value().toInt()) : (-1),
                    (itr_cost != object.end()) ? (itr_cost.value().toInt()) : (-1),
                    (itr_valuta != object.end()) ? (itr_valuta.value().toString()) : (GLOBAL::null_str),
                    (itr_time != object.end()) ? (itr_time.value().toInt()) : (-1),
                    create);
        if(!create && itr_id != object.end())
            tariff->setId(itr_id.value().toInt());
        return *tariff;
    }

    QJsonObject toJson()
    {
        QJsonObject object
        {
            {"id", id()},
            {"package_id", package_id()},
            {"cost", cost()},
            {"valuta", valuta()},
            {"time", time()}
        };
        return object;
    }

private:
    QString             table_name              = "tariffs";
    bool                my_fullInit;

    int                 my_id                   = -1;
    int                 my_package_id           = -1;
    int                 my_cost                 = -1;
    QString             my_valuta               = GLOBAL::null_str;
    int                 my_time                 = -1;
};

#endif // TARIFFS_H
