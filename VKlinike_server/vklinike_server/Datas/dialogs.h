#ifndef DIALOGS_H
#define DIALOGS_H

#include "global.h"
#include "users.h"
#include "specializations.h"

#include <QJsonArray>


class dialogs
{
public:
    dialogs(int _specialization_id, int _user1_id, int _user2_id, int _user1_doctor, int _user2_doctor, bool _user1_muted, bool _user2_muted, bool create = true)
    {
        my_fullInit = true;
        setDatas(_specialization_id, _user1_id, _user2_id, _user1_doctor, _user2_doctor, _user1_muted, _user2_muted);
        if(create)
            insert();
        id();
    }

    dialogs(int _id, bool fullInit = true)
    {
        my_fullInit = fullInit;
        my_id = _id;
        if(my_fullInit)
            load();
    }

    dialogs(int _user1_id, int _user2_id, bool fullInit = true)
    {
        my_fullInit = fullInit;
        my_user1_id = _user1_id;
        my_user2_id = _user2_id;
        id();
        if(my_fullInit)
            load();
    }

    static QVector <dialogs*> findDialogs(int user_id, int mode)
    {
        QVector <dialogs*> result;
        QString str = "SELECT * FROM dialogs WHERE user1_id = " + QString::number(user_id) + " AND user1_mode = " + QString::number(mode) + " OR user2_id = " + QString::number(user_id) + " AND user2_mode = " + QString::number(mode) + ";";
        QSqlQuery query("CUSTOM_QUERY", *GLOBAL::database_current());
        DEBUG_LOG(str);
        if(!query.exec(str))
            GLOBAL::console_write("Ошибка выполнения SQL запроса: " + str + "\n");
        QSqlRecord record = query.record();
        while(query.next())
        {
            result << new dialogs(query.value(record.indexOf("specialization_id")).toInt(),
                                  query.value(record.indexOf("user1_id")).toInt(),
                                  query.value(record.indexOf("user2_id")).toInt(),
                                  query.value(record.indexOf("user1_mode")).toInt(),
                                  query.value(record.indexOf("user2_mode")).toInt(),
                                  query.value(record.indexOf("user1_muted")).toBool(),
                                  query.value(record.indexOf("user2_muted")).toBool(),
                                  false);
        }
        return result;
    }


    void load()
    {
        QSqlRecord record = sql::select(table_name, "*", "id = " + QString::number(my_id));
        setDatas(record.value("specialization_id").toInt(),
                 record.value("user1_id").toInt(),
                 record.value("user2_id").toInt(),
                 record.value("user1_mode").toInt(),
                 record.value("user2_mode").toInt(),
                 record.value("user1_muted").toBool(),
                 record.value("user2_muted").toBool());
    }

    void insert()
    {
        using namespace sql;
        QVector <Value> values;
        values << Value("specialization_id", QString::number(my_specialization_id));
        values << Value("user1_id", QString::number(my_user1_id));
        values << Value("user2_id", QString::number(my_user2_id));
        values << Value("user1_mode", QString::number(my_user1_mode));
        values << Value("user2_mode", QString::number(my_user2_mode));
        values << Value("user1_muted", bool_to_QString(my_user1_muted));
        values << Value("user2_muted", bool_to_QString(my_user2_muted));
        sql::insert(table_name, values);
    }

    void update()
    {
        using namespace sql;
        QVector <Value> values;
        values << Value("specialization_id", QString::number(my_specialization_id));
        values << Value("user1_id", QString::number(my_user1_id));
        values << Value("user2_id", QString::number(my_user2_id));
        values << Value("user1_mode", QString::number(my_user1_mode));
        values << Value("user2_mode", QString::number(my_user2_mode));
        values << Value("user1_muted", bool_to_QString(my_user1_muted));
        values << Value("user2_muted", bool_to_QString(my_user2_muted));
        sql::update(table_name, values, "id = " + QString::number(my_id));
    }

    void remove()
    {
        sql::remove(table_name, "id = " + QString::number(my_id));
    }


    int id()
    {
        if(my_id == -1 && my_user1_id != -1 && my_user2_id != -1)
        {
            QString where = "user1_id = %1 AND user2_id = %2";
            where = where.arg(QString::number(my_user1_id))
                         .arg(QString::number(my_user2_id));
            my_id = sql::select(table_name, "id", where).value("id").toInt();
        }
        return my_id;
    }

    int specialization_id()
    {
        if(!my_fullInit && my_specialization_id == -1)
            my_specialization_id = sql::select(table_name, "specialization_id", "id = " + QString::number(my_id)).value("specialization_id").toInt();
        return my_specialization_id;
    }

    int user1_id()
    {
        if(!my_fullInit && my_user1_id == -1)
            my_user1_id = sql::select(table_name, "user1_id", "id = " + QString::number(my_id)).value("user1_id").toInt();
        return my_user1_id;
    }

    int user2_id()
    {
        if(!my_fullInit && my_user2_id == -1)
            my_user2_id = sql::select(table_name, "user2_id", "id = " + QString::number(my_id)).value("user2_id").toInt();
        return my_user2_id;
    }

    int user1_mode()
    {
        if(!my_fullInit && my_user1_mode == -1)
            my_user1_mode = sql::select(table_name, "user1_doctor", "id = " + QString::number(my_id)).value("user1_doctor").toBool();
        return my_user1_mode;
    }

    int user2_mode()
    {
        if(!my_fullInit && my_user2_mode == -1)
            my_user2_mode = sql::select(table_name, "user2_doctor", "id = " + QString::number(my_id)).value("user2_doctor").toBool();
        return my_user2_mode;
    }

    bool user1_muted()
    {
        if(!my_fullInit)
            my_user1_muted = sql::select(table_name, "user1_muted", "id = " + QString::number(my_id)).value("user1_muted").toBool();
        return my_user1_muted;
    }

    bool user2_muted()
    {
        if(!my_fullInit)
            my_user2_muted = sql::select(table_name, "user2_muted", "id = " + QString::number(my_id)).value("user2_muted").toBool();
        return my_user2_muted;
    }


    void setDatas(int _specialization_id, int _user1_id, int _user2_id, bool _user1_doctor, bool _user2_doctor, bool _user1_muted, bool _user2_muted)
    {
        my_specialization_id = _specialization_id;
        my_user1_id = _user1_id;
        my_user2_id = _user2_id;
        my_user1_mode = _user1_doctor;
        my_user2_mode = _user2_doctor;
        my_user1_muted = _user1_muted;
        my_user2_muted = _user2_muted;
    }

    QJsonObject toJson(Client* client, int user_id)
    {
        int opponent_id = (user_id == user1_id()) ? user2_id() : user1_id();
        QJsonObject object
        {
            {"id", id()},
            {"companion", users(opponent_id).toJsonPreview(client)},
            {"specialization", specializations(specialization_id()).toJson()},
            {"opponent_mode", (opponent_id == user1_id()) ? user1_mode() : user2_mode()},
            {"opponent_muted", (opponent_id == user1_id()) ? user1_muted() : user2_muted()},
            {"muted", (user_id == user1_id()) ? user1_muted() : user2_muted()}
        };
        return object;
    }

    static dialogs& createFromJson(QJsonObject object, bool autocreate = false);

private:
    QString             table_name              = "dialogs";
    bool                my_fullInit;

    int                 my_id                   = -1;
    int                 my_specialization_id    = -1;
    int                 my_user1_id             = -1;
    int                 my_user2_id             = -1;
    int                 my_user1_mode           = -1;
    int                 my_user2_mode           = -1;
    bool                my_user1_muted;
    bool                my_user2_muted;
};

#endif // DIALOGS_H
