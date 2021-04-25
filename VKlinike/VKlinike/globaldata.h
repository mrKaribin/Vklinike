#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <QObject>
#include <QApplication>
#include <QScreen>
#include <QMessageBox>
#include <QEasingCurve>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QTcpSocket>

class MainWidget;
class Widget;
class Socket;


namespace GlobalData
{
    enum Mode {Mode_Doctor = 0, Mode_Patient};
    enum OutputType {Output_Owner = 0, Output_Friend, Output_Guest};
    enum SubscriptionType {Subscription_Day = 0, Subscription_Week, Subscription_Month};
    enum FrameForm {Frame_Null = 0, Frame_Rectangle, Frame_Rounded, Frame_Circular};

    struct Valuta
    {
        Valuta() {};
        Valuta(QString _name, QString _abbreviation, QString _serviceName)
        {
            name = _name;
            abbreviation = _abbreviation;
            serviceName = _serviceName;
        }

        QString name;
        QString abbreviation;
        QString serviceName;
    };

    namespace strings
    {
        namespace database
        {
            extern QString                          DATABASE_CREATE;
            extern QString                          DATABASE_SELECT;
            extern QString                          DATABASE_INSERT;
            extern QString                          DATABASE_UPDATE;
            extern QString                          DATABASE_DELETE;
        }
        namespace error
        {
            extern QString                          database_header;
            extern QString                          database_cantOpen;
            extern QString                          database_cantRead;
            extern QString                          database_cantWrite;
        }

        extern QMap <SubscriptionType, QString>     subscriptionTypeNames;
        extern QMap <SubscriptionType, QString>     subscriptionTypeDurations;
        extern QMap <SubscriptionType, int>         subscriptionTypeValue;
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
    namespace query
    {
        extern QString                              prefix_reply;
        extern QString                              prefix_get;
        extern QString                              prefix_set;
        extern QString                              prefix_new;
        extern QString                              prefix_update;
        extern QString                              prefix_find;
        extern QString                              prefix_remove;

        extern QString                              postfix_guest;

        extern QString                              autorization;
        extern QString                              profile_base;
        extern QString                              profile_doctor;
        extern QString                              profile_doctor_tariff;
        extern QString                              profile_patient;
        extern QString                              dialogs;
        extern QString                              dialog;
        extern QString                              message;
        extern QString                              message_attachment;
        extern QString                              card;
        extern QString                              specializations;
        extern QString                              list_doctor;
        extern QString                              datas;
        extern QString                              data_icon;
        extern QString                              data_image;
        extern QString                              payment_paypal;
        extern QString                              payment_complete;
        extern QString                              redirection_web;

        extern QString                              confirmation;
        extern QString                              negation;
    }
    namespace interface
    {
        namespace color
        {
            extern QColor                           lightBlue;
            extern QColor                           blue;
            extern QColor                           lightRed;
            extern QColor                           red;
            extern QColor                           gray;
            extern QColor                           black;
        }

        extern QEasingCurve                         animation_curve;
        extern int                                  animation_duration,

                                                    indent,
                                                    indent_medium,
                                                    indent_small,
                                                    spacing,

                                                    row_size,
                                                    text_size,
                                                    photo_size,

                                                    menuBar_height;
    }
    namespace screen
    {
        extern QScreen*                             screen;
        extern QRect                                geometry;
        extern int                                  geometry_shortSide;
        extern int                                  geometry_longSide;

    }


    extern Mode                                     currentMode;
    extern Valuta                                   currentValuta;
    extern QString                                  currentName;
    extern QString                                  currentLogin;
    extern QString                                  currentPassword;

    extern MainWidget                              *widget_main;
    extern Widget                                  *widget_mainArea;

    extern QSqlDatabase                            *database;
    extern QString                                  database_password;
    extern QList <Valuta>                           valutes;

    extern Socket                                  *socket;
    extern QString                                  server_host;
    extern quint16                                  server_port;
    extern QString                                  server_reply_prefix;
    extern wchar_t                                  separator;


    extern void initialize();
    extern void connectToServer();
    extern void checkContent();
    extern void error_Critical(QString _header, QString _message);
    extern void error_Show(QString _header, QString _message);
    extern void database_Open();
    extern void database_Check();
    extern void database_Read();
    extern void database_Write();
};

#endif // GLOBALDATA_H
