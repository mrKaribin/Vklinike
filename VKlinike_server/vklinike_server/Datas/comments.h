#ifndef COMMENTS_H
#define COMMENTS_H

#include "global.h"
#include "users.h"


class comments
{
public:
    comments(int _patient_id, int _doctor_id, int _rating, QString _message, QDateTime _timepoint, bool create = true)
    {
        my_fullInit = true;
        setDatas(_patient_id, _doctor_id, _rating, _message, _timepoint);
        if(create)
            insert();
        id();
    }

    comments(int _id, bool fullInit = true)
    {
        my_fullInit = fullInit;
        my_id = _id;
        if(my_fullInit)
            load();
    }

    comments(int _patient_id, int _doctor_id, bool fullInit = true)
    {
        my_fullInit = fullInit;
        my_patient_id = _patient_id;
        my_doctor_id = _doctor_id;
        id();
        if(my_fullInit)
            load();
    }

    static QList <comments*> findCommentsByPatient(int patient_id)
    {
        QList <comments*> result;
        QString str = "SELECT * FROM comments WHERE patient_id = " + QString::number(patient_id) + ";";
        QSqlQuery query("CUSTOM_QUERY", *GLOBAL::database_current());
        DEBUG_LOG(str);
        if(!query.exec(str))
            GLOBAL::console_write("Ошибка выполнения SQL запроса: " + str + "\n");
        QSqlRecord record = query.record();
        while(query.next())
        {
            result << new comments(patient_id,
                                   query.value(record.indexOf("doctor_id")).toInt(),
                                   query.value(record.indexOf("rating")).toInt(),
                                   query.value(record.indexOf("message")).toString(),
                                   SqlDateTime_to_QDateTime(query.value(record.indexOf("timepoint")).toString()),
                                   false);
        }
        return result;
    }

    static QList <comments*> findCommentsByDoctor(int doctor_id)
    {
        QList <comments*> result;
        QString str = "SELECT * FROM comments WHERE doctor_id = " + QString::number(doctor_id) + ";";
        QSqlQuery query("CUSTOM_QUERY", *GLOBAL::database_current());
        DEBUG_LOG(str);
        if(!query.exec(str))
            GLOBAL::console_write("Ошибка выполнения SQL запроса: " + str + "\n");
        QSqlRecord record = query.record();
        while(query.next())
        {
            result << new comments(query.value(record.indexOf("patient_id")).toInt(),
                                   doctor_id,
                                   query.value(record.indexOf("rating")).toInt(),
                                   query.value(record.indexOf("message")).toString(),
                                   SqlDateTime_to_QDateTime(query.value(record.indexOf("timepoint")).toString()),
                                   false);
        }
        return result;
    }


    void load()
    {
        QSqlRecord record = sql::select(table_name, "*", "id = " + QString::number(my_id));
        setDatas(record.value("patient_id").toInt(),
                 record.value("doctor_id").toInt(),
                 record.value("rating").toInt(),
                 record.value("message").toString(),
                 SqlDateTime_to_QDateTime(record.value("timepoint").toString()));
    }

    void insert()
    {
        using namespace sql;
        QVector <Value> values;
        values << Value("patient_id", QString::number(my_patient_id));
        values << Value("doctor_id", QString::number(my_doctor_id));
        values << Value("rating", QString::number(my_rating));
        values << Value("message", quotes(my_message));
        values << Value("timepoint", QDateTime_to_SqlDateTime(my_timepoint));
        sql::insert(table_name, values);
    }

    void update()
    {
        using namespace sql;
        QVector <Value> values;
        values << Value("patient_id", QString::number(my_patient_id));
        values << Value("doctor_id", QString::number(my_doctor_id));
        values << Value("rating", QString::number(my_rating));
        values << Value("message", quotes(my_message));
        values << Value("timepoint", QDateTime_to_SqlDateTime(my_timepoint));
        sql::update(table_name, values, "id = " + QString::number(my_id));
    }

    void remove()
    {
        sql::remove(table_name, "id = " + QString::number(my_id));
    }


    int id()
    {
        if(my_id == -1 && my_doctor_id != -1 && my_patient_id != -1)
        {
            QString where = "patient_id = %1 AND doctor_id = %2";
            where = where.arg(QString::number(my_patient_id))
                         .arg(QString::number(my_doctor_id));
            my_id = sql::select(table_name, "id", where).value("id").toInt();
        }
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

    int rating()
    {
        if(!my_fullInit && my_rating == -1)
            my_rating = sql::select(table_name, "rating", "id = " + QString::number(my_id)).value("rating").toInt();
        return my_rating;
    }

    QString message()
    {
        if(!my_fullInit && my_message == GLOBAL::null_str)
            my_message = sql::select(table_name, "message", "id = " + QString::number(my_id)).value("message").toString();
        return my_message;
    }

    QDateTime timepoint()
    {
        if(!my_fullInit && my_timepoint == QDateTime())
            my_timepoint = SqlDateTime_to_QDateTime(sql::select(table_name, "timepoint", "id = " + QString::number(my_id)).value("timepoint").toString());
        return my_timepoint;
    }


    void setDatas(int _patient_id, int _doctor_id, int _rating, QString _message, QDateTime _timepoint)
    {
        my_patient_id = _patient_id;
        my_doctor_id = _doctor_id;
        my_rating = _rating;
        my_message = _message;
        my_timepoint = _timepoint;
    }

    comments& createFromJson(QJsonObject object)
    {
        return *new comments(0);
    }

    QJsonObject toJsonForDoctor(Client* client)
    {
        QJsonObject object
        {
            {"id", my_id},
            {"sender", users(my_patient_id).toJson(client)},
            {"rating", my_rating},
            {"timepoint", QDateTime_to_Json(my_timepoint)},
            {"message", my_message},
        };
        return object;
    }


private:
    QString             table_name              = "comments";
    bool                my_fullInit;

    int                 my_id                   = -1;
    int                 my_patient_id           = -1;
    int                 my_doctor_id            = -1;
    int                 my_rating              = -1;
    QString             my_message              = GLOBAL::null_str;
    QDateTime           my_timepoint            = QDateTime();
};

#endif // COMMENTS_H
