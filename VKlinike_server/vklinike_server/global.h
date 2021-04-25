#ifndef GLOBAL_H
#define GLOBAL_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QTimer>
#include <QDateTime>
#include <QJsonObject>
#include <QDebug>

class Server;


#define DEBUG_LOG(message) if(GLOBAL::debug) GLOBAL::console_write("   log: " + message);
#define DEBUG_PAUSE() if(GLOBAL::debug) system("pause");

#define DEBUG_ON() GLOBAL::debug = true;
#define DEBUG_OFF() GLOBAL::debug = false;


extern QJsonObject      QDate_to_Json(QDate date);
extern QDate            Json_to_QDate(QJsonObject date);

extern QJsonObject      QTime_to_Json(QTime time);
extern QTime            Json_to_QTime(QJsonObject time);

extern QJsonObject      QDateTime_to_Json(QDateTime timepoint);
extern QDateTime        Json_to_QDateTime(QJsonObject timepoint);

extern QString          QDateTime_to_SqlDateTime(QDateTime timepoint);
extern QDateTime        SqlDateTime_to_QDateTime(QString timepoint);

extern QString          QDate_to_SqlDate(QDate date);
extern QDate            SqlDate_to_QDate(QString date);

extern QString          QTime_to_SqlTime(QTime time);
extern QTime            SqlTime_to_QTime(QString time);

extern QString          bool_to_QString(bool b);

extern QString          quotes(QString str);
extern QString          unquotes(QString str);


namespace GLOBAL
{
    namespace query
    {
        extern QString                 prefix_reply;
        extern QString                 prefix_get;
        extern QString                 prefix_set;
        extern QString                 prefix_new;
        extern QString                 prefix_update;
        extern QString                 prefix_find;
        extern QString                 prefix_remove;

        extern QString                 postfix_guest;
        extern QString                 postfix_friend;

        extern QString                 autorization;
        extern QString                 profile_base;
        extern QString                 profile_doctor;
        extern QString                 profile_doctor_tariffs;
        extern QString                 profile_patient;
        extern QString                 dialogs_prewiev;
        extern QString                 dialog_full;
        extern QString                 message_full;
        extern QString                 message_attachment;
        extern QString                 card_full;
        extern QString                 specializations_full;
        extern QString                 list_doctor;
        extern QString                 datas;
        extern QString                 data_icon;
        extern QString                 data_image;
        extern QString                 payment_paypal;
        extern QString                 payment_complete;
        extern QString                 redirection_web;

        extern QString                 confirmation;
        extern QString                 negation;
    }
    namespace directory
    {
        namespace icons
        {
            extern QString                          profile,
                                                    profile_active,
                                                    messages,
                                                    messages_active,
                                                    search,
                                                    search_active,
                                                    preferences;

            extern QString                          clock;
            extern QString                          money;

            extern QString                          star,
                                                    gold_star;

            extern QString                          expand;
            extern QString                          turn;
            extern QString                          affix;
            extern QString                          back;
            extern QString                          call_audio;
            extern QString                          call_video;
            extern QString                          check;
            extern QString                          check_double;
            extern QString                          loading;
            extern QString                          unread;
            extern QString                          send;
            extern QString                          photo;
            extern QString                          video;
            extern QString                          document;
            extern QString                          settings;
            extern QString                          cross;

            extern QString                          search_patient;
        }
        namespace images
        {
            extern QString                          patient;
            extern QString                          doctor;
        }

        extern QString                              path;
        extern QString                              syspath;
        extern QString                              image;
        extern QString                              icon;
        extern QString                              attachment;
    }

    extern QMap <QThread*, QSqlDatabase*>   databases;
    extern QString                          database_name;
    extern QString                          database_host;
    extern QString                          database_user;
    extern QString                          database_password;

    extern Server*                          server;
    extern QString                          server_host;
    extern quint16                          server_port;

    extern wchar_t                          separator;
    extern QString                          null_str;

    extern bool                             debug;
    extern bool                             testing;
    extern int                              console_indent;

    extern QTcpSocket*                      connector;

    extern void                             initialize();
    extern void                             database_connect(QSqlDatabase &database);
    extern void                             database_disconnect(QSqlDatabase &database);
    extern void                             database_check(QSqlDatabase &database);
    extern QSqlDatabase                    *database_current();
    extern QString                          database_newIndex();

    extern void                             console_write(QString message, bool newline = false);
}


namespace sql
{
    struct Value
    {
        Value() {}
        Value(QString _name, QString _data)
        {
            name = _name;
            data = _data;
        }

        QString name;
        QString data;
    };

    extern void                     insert(QString table, QVector <Value> values);
    extern QSqlRecord               select(QString table, QString values = "*", QString where = "", QString order = "", QString limit = "");
    extern void                     update(QString table, QVector <Value> values, QString where = "", QString order = "", QString limit = "");
    extern void                     remove(QString table, QString where = "");
}

#endif // GLOBAL_H
