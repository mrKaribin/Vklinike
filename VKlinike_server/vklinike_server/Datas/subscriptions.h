#ifndef SUBSCRIPTIONS_H
#define SUBSCRIPTIONS_H

#include "global.h"
#include "doctors.h"
#include "specializations.h"


class subscriptions
{
public:
    subscriptions(int _patient_id, int _doctor_id, int _specialization_id, int _interval, int _cost, QString _valuta, int _time, QDateTime _timepoint_begin, QDateTime _timepoint_end, bool create = true)
    {
        my_fullInit = true;
        setDatas(_patient_id, _doctor_id, _specialization_id, _interval, _cost, _valuta, _time, _timepoint_begin, _timepoint_end);
        if(create)
            insert();
        my_id = sql::select(table_name, "id", "rowid = last_insert_rowid()").value(0).toInt();
    }

    subscriptions(int _id, bool fullInit = true)
    {
        my_fullInit = fullInit;
        my_id = _id;
        if(my_fullInit)
            load();
    }

    static QList <subscriptions*> findSubscriptionsToPatient(int patient_id)
    {
        QList <subscriptions*> result;
        QString str = "SELECT id FROM subscriptions WHERE patient_id = " + QString::number(patient_id) + ";";
        QSqlQuery query("CUSTOM_QUERY", *GLOBAL::database_current());
        DEBUG_LOG(str);
        if(!query.exec(str))
            GLOBAL::console_write("Ошибка выполнения SQL запроса: " + str + "\n");
        QSqlRecord record = query.record();
        while(query.next())
        {
            result << new subscriptions(query.value(record.indexOf("patient_id")).toInt(),
                                        query.value(record.indexOf("doctor_id")).toInt(),
                                        query.value(record.indexOf("specialization_id")).toInt(),
                                        query.value(record.indexOf("interval")).toInt(),
                                        query.value(record.indexOf("cost")).toInt(),
                                        query.value(record.indexOf("valuta")).toString(),
                                        query.value(record.indexOf("time")).toInt(),
                                        SqlDateTime_to_QDateTime(query.value(record.indexOf("timepoint_begin")).toString()),
                                        SqlDateTime_to_QDateTime(query.value(record.indexOf("timepoint_end")).toString()));
        }
        return result;
    }


    void load()
    {
        QSqlRecord record = sql::select(table_name, "*", "id = " + QString::number(my_id));
        setDatas(record.value("patient_id").toInt(),
                 record.value("doctor_id").toInt(),
                 record.value("specialization_id").toInt(),
                 record.value("interval").toInt(),
                 record.value("cost").toInt(),
                 record.value("valuta").toString(),
                 record.value("time").toInt(),
                 SqlDateTime_to_QDateTime(record.value("timepoint_begin").toString()),
                 SqlDateTime_to_QDateTime(record.value("timepoint_end").toString()));
    }

    void insert()
    {
        using namespace sql;
        QVector <Value> values;
        values << Value("patient_id", QString::number(my_patient_id));
        values << Value("doctor_id", QString::number(my_doctor_id));
        values << Value("specialization_id", QString::number(my_specialization_id));
        values << Value("interval", QString::number(my_interval));
        values << Value("cost", QString::number(my_cost));
        values << Value("valuta", quotes(my_valuta));
        values << Value("time", QString::number(my_time));
        values << Value("timepoint_begin", QDateTime_to_SqlDateTime(my_timepoint_begin));
        values << Value("timepoint_end", QDateTime_to_SqlDateTime(my_timepoint_begin));
        sql::insert(table_name, values);
    }

    void update()
    {
        using namespace sql;
        QVector <Value> values;
        values << Value("patient_id", QString::number(my_patient_id));
        values << Value("doctor_id", QString::number(my_doctor_id));
        values << Value("specialization_id", QString::number(my_specialization_id));
        values << Value("interval", QString::number(my_interval));
        values << Value("cost", QString::number(my_cost));
        values << Value("valuta", quotes(my_valuta));
        values << Value("time", QString::number(my_time));
        values << Value("timepoint_begin", QDateTime_to_SqlDateTime(my_timepoint_begin));
        values << Value("timepoint_end", QDateTime_to_SqlDateTime(my_timepoint_begin));
        sql::update(table_name, values, "id = " + QString::number(my_id));
    }

    void remove()
    {
        sql::remove(table_name, "id = " + QString::number(my_id));
    }


    int id()
    {
        return my_id;
    }

    int patient_id()
    {
        if(!my_fullInit && my_patient_id == -1)
            my_patient_id = sql::select(table_name, "patient_id", "id = " + QString::number(my_id)).value("patient_id").toInt();
        return my_patient_id;
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

    int cost()
    {
        if(!my_fullInit && my_cost == -1)
            my_cost = sql::select(table_name, "cost", "id = " + QString::number(my_id)).value("cost").toInt();
        return my_cost;
    }

    QString valuta()
    {
        if(!my_fullInit && my_valuta == GLOBAL::null_str)
            my_valuta = sql::select(table_name, "valuta", "id = " + QString::number(my_id)).value("valuta").toString();
        return my_valuta;
    }

    int time()
    {
        if(!my_fullInit && my_time == -1)
            my_time = sql::select(table_name, "time", "id = " + QString::number(my_id)).value("time").toInt();
        return my_time;
    }

    QDateTime timepoint_begin()
    {
        if(!my_fullInit && my_timepoint_begin == QDateTime())
            my_timepoint_begin = SqlDateTime_to_QDateTime(sql::select(table_name, "timepoint_begin", "id = " + QString::number(my_id)).value("timepoint_begin").toString());
        return my_timepoint_begin;
    }

    QDateTime timepoint_end()
    {
        if(!my_fullInit && my_timepoint_end == QDateTime())
            my_timepoint_end = SqlDateTime_to_QDateTime(sql::select(table_name, "timepoint_end", "id = " + QString::number(my_id)).value("timepoint_end").toString());
        return my_timepoint_end;
    }


    void setDatas(int _patient_id, int _doctor_id, int _specialization_id, int _interval, int _cost, QString _valuta, int _time, QDateTime _timepoint_begin, QDateTime _timepoint_end)
    {
        my_patient_id = _patient_id;
        my_doctor_id = _doctor_id;
        my_specialization_id = _specialization_id;
        my_interval = _interval;
        my_cost = _cost;
        my_valuta = _valuta;
        my_time = _time;
        my_timepoint_begin = _timepoint_begin;
        my_timepoint_end = _timepoint_end;
    }

    QJsonObject toJson()
    {
        specializations specialization(specialization_id());
        QJsonObject object
        {
            {"id", id()},
            {"doctor", doctors(doctor_id()).toJson()},
            {"specializatio", specialization.toJson()},
            {"duration", interval()},
            {"cost", cost()},
            {"valuta", valuta()},
            {"time", time()},
            {"timepoint_begin", QDateTime_to_Json(timepoint_begin())},
            {"timepoint_end", QDateTime_to_Json(timepoint_end())}
        };
        return object;
    }

private:
    QString             table_name              = "subscriptions";
    bool                my_fullInit;

    int                 my_id                   = -1;
    int                 my_patient_id           = -1;
    int                 my_doctor_id            = -1;
    int                 my_specialization_id    = -1;
    int                 my_interval             = -1;
    int                 my_cost                 = -1;
    QString             my_valuta               = GLOBAL::null_str;
    int                 my_time                 = -1;
    QDateTime           my_timepoint_begin      = QDateTime();
    QDateTime           my_timepoint_end        = QDateTime();
};

#endif // SUBSCRIPTIONS_H
