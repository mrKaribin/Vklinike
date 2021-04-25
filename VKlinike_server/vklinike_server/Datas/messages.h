#ifndef MESSAGES_H
#define MESSAGES_H

#include "global.h"

#include "QFile"
#include "QJsonArray"

#include <client.h>


class messages
{
public:
    messages(int _dialog_id, int _sender_id, QDateTime _timepoint, QString _message, bool _recd, bool _readed, QStringList _deleted = QStringList(), QString _attachment_type = GLOBAL::null_str, QByteArray _attachment_data = QByteArray(), bool create = true)
    {
        my_fullInit = true;
        setDatas(_dialog_id, _sender_id, _timepoint, _message, _recd, _readed, _deleted, _attachment_type, _attachment_data);
        if(create)
        {
            insert();
            my_id = sql::select(table_name, "id", "rowid = last_insert_rowid()").value(0).toInt();
        }
    }

    messages(int _id, bool fullInit = true)
    {
        my_fullInit = fullInit;
        my_id = _id;
        if(my_fullInit)
            load();
    }

    static QList <messages*> findMessages(int dialog_id)
    {
        QList <messages*> result;
        QString str = "SELECT * FROM messages WHERE dialog_id = " + QString::number(dialog_id) + ";";
        QSqlQuery query("CUSTOM_QUERY", *GLOBAL::database_current());
        DEBUG_LOG(str);
        if(!query.exec(str))
            GLOBAL::console_write("Ошибка выполнения SQL запроса: " + str + "\n");
        QSqlRecord record = query.record();
        while(query.next())
        {
            QByteArray attachment_data;
            QString _attachment_name = query.value(record.indexOf("attachment_name")).toString();
            if(_attachment_name != GLOBAL::null_str)
            {
                QFile file(GLOBAL::directory::attachment + _attachment_name);
                if(!file.open(QIODevice::ReadOnly))
                    GLOBAL::console_write("Не удалось загрузить вложение: " + GLOBAL::directory::attachment + record.value("attachment_name").toString());
                attachment_data = file.readAll();
            }

            QString _deleted = query.value(record.indexOf("deleted")).toString();
            QStringList deleted = (_deleted == "empty" ? QStringList() : _deleted.split(";"));
            messages *new_message = new messages(dialog_id,
                                   query.value(record.indexOf("sender_id")).toInt(),
                                   SqlDateTime_to_QDateTime(query.value(record.indexOf("timepoint")).toString()),
                                   query.value(record.indexOf("message")).toString(),
                                   query.value(record.indexOf("recd")).toBool(),
                                   query.value(record.indexOf("readed")).toBool(),
                                   deleted,
                                   query.value(record.indexOf("attachment_type")).toString(),
                                   attachment_data,
                                   false);
            new_message->setId(query.value(record.indexOf("id")).toInt());
            new_message->setAttachment_name(_attachment_name);
            result << new_message;
        }
        return result;
    }

    static messages findMessageByAttachment(QString attachment)
    {
        QSqlRecord record = sql::select("messages", "*", "attachment = " + quotes(attachment));

        QFile file(GLOBAL::directory::attachment + record.value("attachment_name").toString());
        if(!file.open(QIODevice::ReadOnly))
            GLOBAL::console_write("Не удалось загрузить вложение: " + GLOBAL::directory::attachment + record.value("attachment_name").toString());
        QByteArray attachment_data = file.readAll();

        QString _deleted = record.value("deleted").toString();
        QStringList deleted = (_deleted == "empty" ? QStringList() : _deleted.split(":"));

        messages _message(record.value("dialog_id").toInt(),
                            record.value("sender_id").toInt(),
                            SqlDateTime_to_QDateTime(record.value("timepoint").toString()),
                            record.value("message").toString(),
                            record.value("recd").toBool(),
                            record.value("readed").toBool(),
                            deleted,
                            record.value("attachment_type").toString(),
                            attachment_data,
                            false);
        _message.setId(record.value("id").toInt());
        return _message;
    }


    void load()
    {
        QSqlRecord record = sql::select(table_name, "*", "id = " + QString::number(my_id));

        my_attachment_directory = GLOBAL::directory::attachment + record.value("attachment_name").toString();
        QFile file(my_attachment_directory);
        if(!file.open(QIODevice::ReadOnly))
            GLOBAL::console_write("Не удалось загрузить вложение: " + GLOBAL::directory::attachment + record.value("attachment_name").toString());
        QByteArray attachment_data = file.readAll();

        QString _deleted = record.value("deleted").toString();
        QStringList deleted = (_deleted == "empty" ? QStringList() : _deleted.split(separator));

        setDatas(record.value("dialog_id").toInt(),
                 record.value("sender_id").toInt(),
                 SqlDateTime_to_QDateTime(record.value("timepoint").toString()),
                 record.value("message").toString(),
                 record.value("recd").toBool(),
                 record.value("readed").toBool(),
                 deleted,
                 record.value("attachment_type").toString(),
                 attachment_data);
    }

    void insert()
    {
        using namespace sql;
        QVector <Value> values;
        values << Value("dialog_id", QString::number(my_dialog_id));
        values << Value("sender_id", QString::number(my_sender_id));
        values << Value("timepoint", QDateTime_to_SqlDateTime(my_timepoint));
        values << Value("message", quotes(my_message));
        values << Value("recd", bool_to_QString(my_recd));
        values << Value("readed", bool_to_QString(my_readed));
        values << Value("deleted", quotes(listToString(my_deleted)));
        values << Value("attachment_type", quotes(my_attachment_type));
        sql::insert(table_name, values);

        my_id = sql::select(table_name, "id", "rowid = last_insert_rowid()").value(0).toInt();
        if(!my_attachment_data.isEmpty())
            attachment_save(my_attachment_data, my_attachment_type);
        update();
    }

    void update()
    {
        using namespace sql;
        if(!my_attachment_data.isEmpty())
            attachment_save(my_attachment_data, my_attachment_type);
        QVector <Value> values;
        values << Value("dialog_id", QString::number(my_dialog_id));
        values << Value("sender_id", QString::number(my_sender_id));
        values << Value("timepoint", QDateTime_to_SqlDateTime(my_timepoint));
        values << Value("message", quotes(my_message));
        values << Value("recd", bool_to_QString(my_recd));
        values << Value("readed", bool_to_QString(my_readed));
        values << Value("deleted", quotes(listToString(my_deleted)));
        values << Value("attachment_name", quotes(my_attachment_name));
        values << Value("attachment_type", quotes(my_attachment_type));
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

    int dialog_id()
    {
        if(!my_fullInit && my_dialog_id == -1)
            my_dialog_id = sql::select(table_name, "dialog_id", "id = " + QString::number(my_id)).value("dialog_id").toInt();
        return my_dialog_id;
    }

    int sender_id()
    {
        if(!my_fullInit && my_sender_id == -1)
            my_sender_id = sql::select(table_name, "sender_id", "id = " + QString::number(my_id)).value("sender_id").toInt();
        return my_sender_id;
    }

    QDateTime timepoint()
    {
        if(!my_fullInit && my_timepoint == QDateTime())
            my_timepoint = SqlDateTime_to_QDateTime(sql::select(table_name, "timepoint", "id = " + QString::number(my_id)).value("timepoint").toString());
        return my_timepoint;
    }

    QString message()
    {
        if(!my_fullInit && my_message == GLOBAL::null_str)
            my_message = sql::select(table_name, "message", "id = " + QString::number(my_id)).value("message").toString();
        return my_message;
    }

    bool recd()
    {
        if(!my_fullInit)
            my_recd = sql::select(table_name, "recd", "id = " + QString::number(my_id)).value("recd").toBool();
        return my_recd;
    }

    bool readed()
    {
        if(!my_fullInit)
            my_readed = sql::select(table_name, "readed", "id = " + QString::number(my_id)).value("readed").toBool();
        return my_readed;
    }

    QStringList deleted()
    {
        if(!my_fullInit)
            my_deleted = sql::select(table_name, "deleted", "id = " + QString::number(my_id)).value("deleted").toString().split(separator);
        return my_deleted;
    }

    QString attachment_name()
    {
        if(!my_fullInit && my_attachment_name == GLOBAL::null_str)
            my_attachment_name = sql::select(table_name, "attachment_name", "id = " + QString::number(my_id)).value("attachment_name").toString();
        return my_attachment_name;
    }

    QString attachment_type()
    {
        if(!my_fullInit && my_attachment_type == GLOBAL::null_str)
            my_attachment_type = sql::select(table_name, "attachment_type", "id = " + QString::number(my_id)).value("attachment_type").toString();
        return my_attachment_type;
    }

    void setId(int id)
    {
        my_id = id;
    }

    void setAttachment_name(QString _name)
    {
        my_attachment_name = _name;
    }

    void deleted_add(QString email)
    {
        my_deleted << email;
    }

    bool isDeletedForUser(QString login)
    {
        for(int i = 0; i < my_deleted.size(); i++)
            if(login == my_deleted[i])
                return true;
        return false;
    }

    QString listToString(QStringList list)
    {
        QString str = "";
        for(int i = 0; i < list.size(); i++)
            str += list[i] + separator;
        if(!str.isEmpty())
            str.remove(str.size() - 1);
        if(str.isEmpty() || str == GLOBAL::null_str)
            str = "empty";
        return str;
    }

    QByteArray attachment_data()
    {
        if(my_attachment_data.isEmpty() && attachment_name() != GLOBAL::null_str)
        {
            QString adress = GLOBAL::directory::attachment + attachment_name();
            QFile file(adress);
            if(!file.open(QIODevice::ReadOnly))
                GLOBAL::console_write("Не удалось загрузить вложение: " + adress);
            my_attachment_data = file.readAll();
        }
        return my_attachment_data;
    }

    void attachment_save(QByteArray _attachment, QString _type)
    {
        my_attachment_type = _type;
        my_attachment_name = "file_" + QString::number(my_id) + "." + _type;
        my_attachment_directory = GLOBAL::directory::attachment + my_attachment_name;
        QFile file(my_attachment_directory);
        if(!file.open(QIODevice::WriteOnly))
            GLOBAL::console_write("Не удалось сохранить вложение: " + my_attachment_name);
        file.write(_attachment);
        //update();
    }


    void setDatas(int _dialog_id, int _sender_id, QDateTime _timepoint, QString _message, bool _recd, bool _readed, QStringList _deleted = QStringList(), QString _attachment_type = GLOBAL::null_str, QByteArray _attachment_data = QByteArray())
    {
        my_dialog_id = _dialog_id;
        my_sender_id = _sender_id;
        my_timepoint = _timepoint;
        my_message = _message;
        my_recd = _recd;
        my_readed = _readed;
        my_deleted = _deleted;
        my_attachment_type = _attachment_type;
        my_attachment_data = _attachment_data;
    }

    static messages& createFromJson(Client* client, QJsonObject object, bool autocreate = false)
    {
        QJsonObject::iterator itr_dialog_id = object.find("dialog_id");
        QJsonObject::iterator itr_sender_id = object.find("sender_id");
        QJsonObject::iterator itr_timepoint = object.find("timepoint");
        QJsonObject::iterator itr_message = object.find("message");
        QJsonObject::iterator itr_recd = object.find("recd");
        QJsonObject::iterator itr_readed = object.find("readed");
        QJsonObject::iterator itr_deleted = object.find("deleted");
        QJsonObject::iterator itr_attachment_type = object.find("attachment_type");
        QJsonObject::iterator itr_attachment_name = object.find("attachment_name");

        QByteArray attachment;
        if(itr_attachment_name != object.end())
            attachment = client->getEnclosure(itr_attachment_name.value().toString());

        QStringList list;
        if(itr_deleted != object.end())
            for(auto str : itr_deleted.value().toArray())
                list.append(str.toString());

        QString type = (itr_attachment_type != object.end()) ? (itr_attachment_type.value().toString()) : ("empty");
        return *new messages(
                   (itr_dialog_id != object.end()) ? (itr_dialog_id.value().toInt()) : (-1),
                   (itr_sender_id != object.end()) ? (itr_sender_id.value().toInt()) : (-1),
                   (itr_timepoint != object.end()) ? (Json_to_QDateTime(itr_timepoint.value().toObject())) : (QDateTime()),
                   (itr_message != object.end()) ? (itr_message.value().toString()) : (""),
                   (itr_recd != object.end()) ? (itr_recd.value().toBool()) : (false),
                   (itr_readed != object.end()) ? (itr_readed.value().toBool()) : (-false),
                   list,
                   type,
                   attachment,
                   autocreate);
    }

    QJsonObject toJson(Client *client)
    {
        QJsonArray array;
        QStringList list = deleted();
        for(auto str : list)
            array.append(str);

        QJsonObject object
        {
            {"id", id()},
            {"dialog_id", dialog_id()},
            {"sender_id", sender_id()},
            {"timepoint", QDateTime_to_Json(timepoint())},
            {"message", message()},
            {"recd", recd()},
            {"readed", readed()},
            {"deleted", array}
        };
        if(!attachment_data().isEmpty())
        {
            object.insert("attachment_type", attachment_type());
            object.insert("attachment_name", attachment_name());
            client->socket_write(attachment_name(), attachment_data());
            //my_attachment_directory = GLOBAL::directory::attachment + my_attachment_name;
            //client->socket_write(attachment_name(), my_attachment_directory);
        }
        return object;
    }

private:
    QString             table_name              = "messages";
    QString             separator               = ";";
    bool                my_fullInit;

    int                 my_id                   = -1;
    int                 my_dialog_id            = -1;
    int                 my_sender_id            = -1;
    QDateTime           my_timepoint            = QDateTime();
    QString             my_message              = GLOBAL::null_str;
    bool                my_recd;
    bool                my_readed;
    QStringList         my_deleted;
    QString             my_attachment_name           = GLOBAL::null_str;
    QString             my_attachment_type           = GLOBAL::null_str;
    QString             my_attachment_directory      = GLOBAL::null_str;
    QByteArray          my_attachment_data;
};

#endif // MESSAGES_H
