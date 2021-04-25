#ifndef USERS_H
#define USERS_H

#include "global.h"
#include "server.h"

#include <QObject>
#include <QPixmap>
#include <QGuiApplication>
#include <QJsonObject>

class Client;


class users
{
public:
    users(QByteArray _photo, QByteArray _miniature, QString _name, QString _surname, QString _patronimic, int _sex, QDate _birthday, QString _email, QString _phone, QString _password, bool autocreate = true);
    users(QString email, bool fullInitialize = true);
    users(int _id, bool fullInitialize = true);

    void                load();
    void                insert();
    void                update();
    void                remove();

    int                 id();
    QByteArray          photo();
    QByteArray          miniature();
    QString             photo_adress();
    QString             name();
    QString             surname();
    QString             patronimic();
    int                 sex();
    QDate               birthday();
    QString             email();
    QString             phone();
    QString             password();

    void                setDatas(QByteArray _photo, QByteArray _miniature, QString _name, QString _surname, QString _patronimic, int _sex, QDate _birthday, QString _email, QString _phone, QString _password);
    bool                search(QString text);

    static users        createFromJson(QJsonObject object, Client *clent, bool autocreate = false);
    QJsonObject         toJson(Client *client);
    QJsonObject         toJsonLimited(Client* client);
    QJsonObject         toJsonPreview(Client* client);

private:
    QString             table_name              = "users";
    bool                my_fullInit;

    int                 my_id                   = -1;
    QByteArray          my_photo                = QByteArray();
    QByteArray          my_miniature            = QByteArray();
    QString             my_photo_adress         = GLOBAL::null_str;
    QString             my_name                 = GLOBAL::null_str;
    QString             my_surname              = GLOBAL::null_str;
    QString             my_patronimic           = GLOBAL::null_str;
    int                 my_sex                  = -1;
    QDate               my_birthday             = QDate(0, 0, 0);
    QString             my_email                = GLOBAL::null_str;
    QString             my_phone                = GLOBAL::null_str;
    QString             my_password             = GLOBAL::null_str;

};

#endif // USERS_H
