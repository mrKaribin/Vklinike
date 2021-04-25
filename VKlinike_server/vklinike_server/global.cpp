#include "global.h"
#include "server.h"


QJsonObject QDate_to_Json(QDate date)
{
    QJsonObject object
    {
        {"year", date.year()},
        {"month", date.month()},
        {"day", date.day()},
        {"hour", 0},
        {"minute", 0},
        {"second", 0},
    };
    return object;
}

QDate Json_to_QDate(QJsonObject date)
{
    QDate result(
                date.find("year").value().toInt(),
                date.find("month").value().toInt(),
                date.find("day").value().toInt()
                );
    return result;
}

QJsonObject QTime_to_Json(QTime time)
{
    QJsonObject object
    {
        {"year", 0},
        {"month", 0},
        {"day", 0},
        {"hour", time.hour()},
        {"minute", time.minute()},
        {"second", time.second()},
    };
    return object;
}

QTime Json_to_QTime(QJsonObject date)
{
    QTime result(
                date.find("hour").value().toInt(),
                date.find("minute").value().toInt(),
                date.find("second").value().toInt()
                );
    return result;
}

QJsonObject QDateTime_to_Json(QDateTime timepoint)
{
    QJsonObject object
    {
        {"year", timepoint.date().year()},
        {"month", timepoint.date().month()},
        {"day", timepoint.date().day()},
        {"hour", timepoint.time().hour()},
        {"minute", timepoint.time().minute()},
        {"second", timepoint.time().second()},
    };
    return object;
}

QDateTime Json_to_QDateTime(QJsonObject date)
{
    QDateTime result(
                QDate(
                    date.find("year").value().toInt(),
                    date.find("month").value().toInt(),
                    date.find("day").value().toInt()),
                QTime(
                    date.find("hour").value().toInt(),
                    date.find("minute").value().toInt(),
                    date.find("second").value().toInt())
                );
    return result;
}

QString QDateTime_to_SqlDateTime(QDateTime timepoint)
{
    return quotes(QString::number(timepoint.date().year()) + "-" + QString::number(timepoint.date().month()) + "-" + QString::number(timepoint.date().day()) + "T" +
                  QString::number(timepoint.time().hour()) + "-" + QString::number(timepoint.time().minute()) + "-" + QString::number(timepoint.time().second()));
}

QDateTime SqlDateTime_to_QDateTime(QString timepoint)
{
    if(timepoint.indexOf("T") == -1)
        return QDateTime();
    QStringList list = timepoint.split("T");
    return QDateTime(SqlDate_to_QDate(list[0]), SqlTime_to_QTime(list[1]));
}

QString QDate_to_SqlDate(QDate date)
{
    return quotes(QString::number(date.year()) + "-" + QString::number(date.month()) + "-" + QString::number(date.day()));
}

QDate SqlDate_to_QDate(QString date)
{
    QStringList list = date.split("-");
    if(list.size() >= 3)
        return QDate(list[0].toInt(), list[1].toInt(), list[2].toInt());
    else
        return QDate(0, 0, 0);
}

QString QTime_to_SqlTime(QTime time)
{
    return quotes(QString::number(time.hour()) + "-" + QString::number(time.minute()) + "-" + QString::number(time.second()));
}

QTime SqlTime_to_QTime(QString time)
{
    QStringList list = time.split("-");
    if(list.size() >= 3)
        return QTime(list[0].toInt(), list[1].toInt(), list[2].toInt());
    else
        return QTime(0, 0, 0);
}

QString bool_to_QString(bool boolean)
{
    if(boolean)
        return "true";
    else
        return "false";
}

QString quotes(QString str)
{
    return "'" + str + "'";
}

QString unquotes(QString str)
{
    if(str[str.size() - 1] == '\'')
        str.remove(str.size() - 1, 1);
    if(str[0] == QString("'")[0])
        str.remove(0, 1);
    return str;
}


namespace GLOBAL
{
    namespace query
    {
        QString                 prefix_reply                    = "Reply:";
        QString                 prefix_get                      = "Get_";
        QString                 prefix_set                      = "Set_";
        QString                 prefix_new                      = "New_";
        QString                 prefix_update                   = "Update_";
        QString                 prefix_find                     = "Find_";
        QString                 prefix_remove                   = "Remove_";

        QString                 postfix_guest                   = "_Guest";
        QString                 postfix_friend                  = "_Friend";

        QString                 autorization                    = "Autorization";
        QString                 profile_base                    = "BaseProfile";
        QString                 profile_doctor                  = "DoctorProfile";
        QString                 profile_doctor_tariffs          = "DoctorProfileTariff";
        QString                 profile_patient                 = "PatientProfile";
        QString                 dialogs_prewiev                 = "DialogsPreview";
        QString                 dialog_full                     = "Dialog";
        QString                 message_full                    = "Message";
        QString                 message_attachment              = "MessageAttachment";
        QString                 card_full                       = "Card";
        QString                 specializations_full            = "Specializations";
        QString                 list_doctor                     = "ListDoctor";
        QString                 datas                           = "Datas";
        QString                 data_icon                       = "DataIcon";
        QString                 data_image                      = "DataImage";
        QString                 payment_paypal                  = "PaymentPayPal";
        QString                 payment_complete                = "PaymentComplete";
        QString                 redirection_web                 = "RedirectionWeb";

        QString                 confirmation                    = "CONFIRMATION";
        QString                 negation                        = "NEGATION";
    }
    namespace directory
    {
        namespace icons
        {
            QString             profile                         = "profile.png",
                                profile_active                  = "profile_active.png",
                                messages                        = "message.png",
                                messages_active                 = "message_active.png",
                                search                          = "search.png",
                                search_active                   = "search_active.png",
                                preferences                     = "prefs.png";

            QString             clock                           = "clock.png";
            QString             money                           = "money.png";

            QString             star                            = "star.png",
                                gold_star                       = "gold_star.png";

            QString             expand                          = "expand.png";
            QString             turn                            = "turn.png";
            QString             affix                           = "affix.png";
            QString             back                            = "back.png";
            QString             call_audio                      = "call_audio.png";
            QString             call_video                      = "call_video.png";
            QString             check                           = "check.png";
            QString             check_double                    = "check_double.png";
            QString             loading                         = "loading.png";
            QString             unread                          = "unread.png";
            QString             send                            = "send.png";
            QString             photo                           = "photo.png";
            QString             video                           = "video.png";
            QString             document                        = "document.png";
            QString             settings                        = "settings.png";
            QString             cross                           = "cross.png";

            QString             search_patient                  = "search_patient.png";
        }
        namespace images
        {
            QString             patient                         = "null_patient.png";
            QString             doctor                          = "null_doctor.png";
        }

        QString                 path                            = "";
        QString                 image                           = "";
        QString                 icon                            = "";
        QString                 attachment                      = "";
    }
    QMap <QThread*, QSqlDatabase*>  databases;
    QString                         database_name                   = "vklinike_database.db";
    QString                         database_host                   = "localhost";
    QString                         database_user                   = "server";
    QString                         database_password               = "topsecretpassword";
    int                             database_count                  = 1;

    Server*                         server;
    QString                         server_host                     = "localhost"; //"http://vklinike.ddnsking.com" "93.81.248.7"
    quint16                         server_port                     = 10228;

    wchar_t                         separator                       = L'֎';
    QString                         null_str                        = "empty";

    bool                            debug                           ;
    bool                            testing                         ;
    int                             console_indent                  = 0;

    void initialize()
    {
        directory::path = "C:\\Projects\\Qt_Projects\\VKlinike_server\\build-vklinike_server-Desktop_Qt_5_12_3_MinGW_32_bit-Debug";
        directory::icon = directory::path + "\\Files\\Icon\\";
        directory::image = directory::path + "\\Files\\Picture\\";
        directory::attachment = directory::path + "\\Files\\Attachment\\";

        QSqlDatabase* database = new QSqlDatabase;
        database_connect(*database);
        database_check(*database);
        server = new Server();
    }

    void database_connect(QSqlDatabase &_database)
    {
        _database = QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE", "thread_" + database_newIndex()));
        _database.setDatabaseName(database_name);
        _database.setHostName(database_host);
        _database.setUserName(database_user);
        _database.setPassword(database_password);
        bool ok = _database.open();
        if(ok)
        {
            console_write("Соединение с базой данных установлено.");
            databases.insert(QThread::currentThread(), &_database);
        }
        else
            console_write("Не удалось соединиться с базой данных. Ошибка: " + _database.lastError().text());
    }

    void database_disconnect(QSqlDatabase &_database)
    {

    }

    void database_check(QSqlDatabase &_database)
    {
        QString pragma = "PRAGMA foreign_keys = 1;";
        QMap <QString, QString> tables;
        tables.insert("users", "CREATE TABLE users ("
                      "id                   INTEGER    NOT NULL PRIMARY KEY AUTOINCREMENT,"
                      "photo                TEXT       UNIQUE NOT NULL DEFAULT ('empty'),"
                      "name                 CHAR (50)  NOT NULL DEFAULT ('empty'),"
                      "surname              CHAR (50)  NOT NULL DEFAULT ('empty'),"
                      "patronimic           CHAR (50)  NOT NULL DEFAULT ('empty'),"
                      "sex                  INTEGER    NOT NULL DEFAULT (1),"
                      "birthday             TEXT       NOT NULL DEFAULT ('0000-00-00'),"
                      "email                CHAR (100) UNIQUE NOT NULL DEFAULT ('empty'),"
                      "phone                CHAR (15)  NOT NULL DEFAULT ('empty'),"
                      "password             TEXT       NOT NULL DEFAULT ('empty')            );");

        tables.insert("doctors", "CREATE TABLE doctors ("
                      "id                   INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                      "user_id              INTEGER REFERENCES users (id) NOT NULL,"
                      "interval             INTEGER NOT NULL DEFAULT ( -1),"
                      "workday_begin        TEXT    NOT NULL DEFAULT ('00:00:00'),"
                      "workday_end          TEXT    NOT NULL DEFAULT ('00:00:00'),"
                      "education            TEXT    NOT NULL DEFAULT ('empty'),"
                      "job                  TEXT    NOT NULL DEFAULT ('empty')          );");

        tables.insert("patients", "CREATE TABLE patients ("
                      "id                   INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                      "user_id              INTEGER REFERENCES users (id) NOT NULL      );");

        tables.insert("specializations", "CREATE TABLE specializations ("
                      "id                   INTEGER   PRIMARY KEY AUTOINCREMENT NOT NULL,"
                      "name                 CHAR (50) NOT NULL DEFAULT ('empty'),"
                      "info                 TEXT      NOT NULL DEFAULT ('empty')          );");

        tables.insert("packages", "CREATE TABLE packages ("
                      "id                   INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                      "doctor_id            INTEGER NOT NULL REFERENCES doctors (id),"
                      "specialization_id    INTEGER REFERENCES specializations (id) NOT NULL,"
                      "interval             INTEGER NOT NULL DEFAULT ( -1)                    );");

        tables.insert("tariffs", "CREATE TABLE tariffs ("
                      "id                   INTEGER  PRIMARY KEY AUTOINCREMENT NOT NULL,"
                      "package_id           INTEGER  REFERENCES packages (id) NOT NULL,"
                      "cost                 INTEGER  NOT NULL DEFAULT ( -1),"
                      "valuta               CHAR (4) NOT NULL DEFAULT ('rub'),"
                      "time                 INTEGER  NOT NULL DEFAULT ( -1)             );");

        tables.insert("subscriptions", "CREATE TABLE subscriptions ("
                      "id                   INTEGER  PRIMARY KEY AUTOINCREMENT NOT NULL,"
                      "patient_id           INTEGER  REFERENCES patients (id) NOT NULL,"
                      "doctor_id            INTEGER  REFERENCES doctors (id) NOT NULL,"
                      "interval             INTEGER  NOT NULL DEFAULT ( -1),"
                      "cost                 INTEGER  NOT NULL DEFAULT ( -1),"
                      "valuta               CHAR (4) NOT NULL DEFAULT ('rub'),"
                      "time                 INTEGER  NOT NULL DEFAULT ( -1)              );");

        tables.insert("dialogs", "CREATE TABLE dialogs ("
                      "id                   INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                      "specialization_id    INTEGER REFERENCES specializations (id) NOT NULL,"
                      "user1_id             INTEGER REFERENCES users (id) NOT NULL,"
                      "user2_id             INTEGER REFERENCES users (id) NOT NULL,"
                      "user1_doctor         BOOLEAN,"
                      "user2_doctor         BOOLEAN,"
                      "user1_muted          BOOLEAN NOT NULL DEFAULT (false),"
                      "user2_muted          BOOLEAN NOT NULL DEFAULT (false)                  );");

        tables.insert("messages", "CREATE TABLE messages ("
                      "id                   INTEGER  PRIMARY KEY AUTOINCREMENT NOT NULL,"
                      "dialog_id            INTEGER  REFERENCES dialogs (id) NOT NULL,"
                      "sender_id            INTEGER  REFERENCES users (id) NOT NULL,"
                      "timepoint            DATETIME NOT NULL DEFAULT (0 - 0 - 0),"
                      "recd                 BOOLEAN  NOT NULL DEFAULT (false),"
                      "readed               BOOLEAN  NOT NULL DEFAULT (false),"
                      "message              TEXT     NOT NULL DEFAULT ('empty'),"
                      "deleted              TEXT     NOT NULL DEFAULT ('empty'),"
                      "attachment           TEXT     NOT NULL UNIQUE DEFAULT ('empty')   );");

        tables.insert("comments", "CREATE TABLE comments ("
                      "id                   INTEGER  PRIMARY KEY AUTOINCREMENT NOT NULL,"
                      "patient_id           INTEGER  REFERENCES patients (id) NOT NULL,"
                      "doctor_id            INTEGER  REFERENCES doctors (id) NOT NULL,"
                      "rating               INTEGER  NOT NULL DEFAULT ( -1),"
                      "message              TEXT     NOT NULL DEFAULT ('empty'),"
                      "timepoint            TEXT     NOT NULL DEFAULT ('0000-00-00')                   );");

        tables.insert("cards", "CREATE TABLE cards ("
                       "id                  INTEGER  PRIMARY KEY AUTOINCREMENT NOT NULL DEFAULT ( -1),"
                       "user_id             INTEGER  REFERENCES users (id) NOT NULL DEFAULT ( -1),"
                       "number              TEXT     NOT NULL DEFAULT ('0000000000000000'),"
                       "month               CHAR (2) DEFAULT ('00') NOT NULL,"
                       "year                CHAR (4) NOT NULL DEFAULT ('0000')                         );");

        bool ok = true;
        QStringList tables_list = _database.tables();
        foreach(auto table_name, tables.keys())
        {
            bool exist = false;
            for(int i = 0; i < tables_list.size(); i++)
            {
                if(table_name == tables_list[i])
                    exist = true;
            }

            if(!exist)
            {
                QSqlQuery query("CREATE_TABLE_QUERY", *GLOBAL::database_current());
                if(!query.exec(tables.find(table_name).value()))
                {
                    console_write("Не удалось создать таблицу '" + table_name + "' в базе данных");
                    ok = false;
                }
                else
                    console_write("Создана таблица '" + table_name + "' в базе данных");
            }
        }

        if(ok)
            console_write("База данных скофигурирована корректно.");
        else
            console_write("Конфигурация базы данных некорректная.");
    }

    QSqlDatabase *database_current()
    {
        QMap <QThread*, QSqlDatabase*>::iterator iterator = databases.find(QThread::currentThread());
        if(iterator != databases.end())
            return iterator.value();
        else
        {
            QSqlDatabase* database = new QSqlDatabase();
            database_connect(*database);
            database_check(*database);
            return database;
        }
    }

    QString database_newIndex()
    {
        QString result = QString::number(database_count);
        database_count++;
        return result;
    }

    void console_write(QString message, bool newline)
    {
        QString indent;
        if(newline) indent += "\n";
        for(int i = 0; i < console_indent; i++) indent += "   ";
        qDebug().noquote() << indent << message;
    }
}


namespace sql
{
    void insert(QString table, QVector <Value> values)
    {
        QSqlQuery query("INSERT_QUERY", *GLOBAL::database_current());
        QString header = "INSERT INTO " + table + " (";
        QString body   = " VALUES (";

        for(int i = 0; i < values.size(); i++)
        {
            header += values[i].name;
            body += values[i].data;
            if(i != values.size() - 1)
            {
                header += ", ";
                body += ", ";
            }
        }
        header += ")";
        body += ");";

        DEBUG_LOG(header + body);
        if(!query.exec(header + body))
            GLOBAL::console_write("Ошибка выполнения SQL запроса: " + header + body + "\n", true);
    }

    QSqlRecord select(QString table, QString values, QString where, QString order, QString limit)
    {
        QSqlQuery query("SELECT_QUERY", *GLOBAL::database_current());
        QString result = "SELECT " + values + " FROM " + table;
        if(where != "")
            result += " WHERE " + where;
        if(order != "")
            order += " ORDER BY " + order;
        if(limit != "")
            limit += " LIMIT " + limit;
        result += ";";

        DEBUG_LOG(result);
        if(!query.exec(result))
            GLOBAL::console_write("Ошибка выполнения SQL запроса: " + result + "\n", true);

        query.next();
        return query.record();
    }

    void update(QString table, QVector <Value> values, QString where, QString order, QString limit)
    {
        QSqlQuery query("UPDATE_QUERY", *GLOBAL::database_current());
        QString result = "UPDATE " + table + " SET ";

        for(int i = 0; i < values.size(); i++)
        {
            result += values[i].name + " = " + values[i].data;
            if(i != values.size() - 1)
                result += ", ";
        }
        if(where != "")
            result += " WHERE " + where;
        if(order != "")
            order += " ORDER BY " + order;
        if(limit != "")
            limit += " LIMIT " + limit;
        result += ";";

        DEBUG_LOG(result);
        if(!query.exec(result))
            GLOBAL::console_write("Ошибка выполнения SQL запроса: " + result + "\n", true);
    }

    void remove(QString table, QString where)
    {
        QSqlQuery query("REMOVE_QUERY", *GLOBAL::database_current());
        QString result = "DELETE FROM " + table;
        if(where != "")
            result += " WHERE " + where;
        result += ";";

        DEBUG_LOG(result);
        if(!query.exec(result))
            GLOBAL::console_write("Ошибка выполнения SQL запроса: " + result + "\n", true);
    }
}
