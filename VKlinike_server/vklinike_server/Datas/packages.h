#ifndef PACKAGES_H
#define PACKAGES_H

#include "global.h"


class packages
{
public:
    packages(int _doctor_id, int _specialization_id, int _interval, bool create = true)
    {
        my_fullInit = true;
        setDatas(_doctor_id, _specialization_id, _interval);
        if(create)
            insert();
        id();
    }

    packages(int _id, bool fullInit = true)
    {
        my_fullInit = fullInit;
        my_id = _id;
        if(my_fullInit)
            load();
    }

    static QMultiMap <int, packages*> findPackages(int doctor_id)
    {
        QMultiMap <int, packages*> result;
        QString str = "SELECT * FROM packages WHERE doctor_id = " + QString::number(doctor_id) + ";";
        QSqlQuery query("CUSTOM_QUERY", *GLOBAL::database_current());
        DEBUG_LOG(str);
        if(!query.exec(str))
            GLOBAL::console_write("Ошибка выполнения SQL запроса: " + str + "\n");
        QSqlRecord record = query.record();
        while(query.next())
        {
            int specialization_id = query.value(record.indexOf("specialization_id")).toInt();
            result.insert(specialization_id, new packages(doctor_id,
                                                          specialization_id,
                                                          query.value(record.indexOf("interval")).toInt(),
                                                          false));
        }
        return result;
    }


    void load()
    {
        QSqlRecord record = sql::select(table_name, "*", "id = " + QString::number(my_id));
        setDatas(record.value("doctor_id").toInt(),
                 record.value("specialization_id").toInt(),
                 record.value("interval").toInt());
    }

    void insert()
    {
        using namespace sql;
        QVector <Value> values;
        values << Value("doctor_id", QString::number(my_doctor_id));
        values << Value("specialization_id", QString::number(my_specialization_id));
        values << Value("interval", QString::number(my_interval));
        sql::insert(table_name, values);
    }

    void update()
    {
        using namespace sql;
        QVector <Value> values;
        values << Value("doctor_id", QString::number(my_doctor_id));
        values << Value("specialization_id", QString::number(my_specialization_id));
        values << Value("interval", QString::number(my_interval));
        sql::update(table_name, values, "id = " + QString::number(my_id));
    }

    void remove()
    {
        sql::remove(table_name, "id = " + QString::number(my_id));
    }


    int id()
    {
        if(my_id == -1 && my_doctor_id != -1 && my_specialization_id != -1 && my_interval != -1)
        {
            QString where = "doctor_id = %1 AND specialization_id = %2 AND interval = %3";
            where = where.arg(QString::number(my_doctor_id))
                         .arg(QString::number(my_specialization_id))
                         .arg(QString::number(my_interval));
            my_id = sql::select(table_name, "id", where).value("id").toInt();
        }
        return my_id;
    }

    int doctor_id()
    {
        if(!my_fullInit && my_doctor_id == -1)
            my_doctor_id = sql::select(table_name, "doctor_id", "id = " + QString::number(my_id)).value("doctor_id").toInt();
        return my_doctor_id;
    }

    int specialization_id()
    {
        if(!my_fullInit && my_specialization_id == -1)
            my_specialization_id = sql::select(table_name, "specialization_id", "id = " + QString::number(my_id)).value("specialization_id").toInt();
        return my_specialization_id;
    }

    int interval()
    {
        if(!my_fullInit && my_interval == -1)
            my_interval = sql::select(table_name, "interval", "id = " + QString::number(my_id)).value("interval").toInt();
        return my_interval;
    }


    void setDatas(int _doctor_id, int _specialization_id, int _interval)
    {
        my_doctor_id = _doctor_id;
        my_specialization_id = _specialization_id;
        my_interval = _interval;
    }

private:
    QString             table_name              = "packages";
    bool                my_fullInit;

    int                 my_id                   = -1;
    int                 my_doctor_id            = -1;
    int                 my_specialization_id    = -1;
    int                 my_interval             = -1;
};

#endif // PACKAGES_H
