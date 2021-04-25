#include "users.h"

#include <QBuffer>
#include <QFile>
#include <QJsonDocument>
#include <client.h>
#include <server.h>


users::users(QByteArray _photo, QByteArray _miniature, QString _name, QString _surname, QString _patronimic, int _sex, QDate _birthday, QString _email, QString _phone, QString _password, bool autocreate)
{
    my_fullInit = true;
    setDatas(_photo, _miniature, _name, _surname, _patronimic, _sex, _birthday, _email, _phone, _password);
    if(autocreate)
        insert();
    id();
}

users::users(QString _email, bool fullInitialize)
{
    my_fullInit = fullInitialize;
    my_email = _email;
    id();
    if(fullInitialize)
        load();
}

users::users(int _id, bool fullInitialize)
{
    my_fullInit = fullInitialize;
    my_id = _id;
    if(fullInitialize)
        load();
}

bool users::search(QString text)
{
    QString FIO = surname() + " " + name() + " " + patronimic();
    QString IO = name() + " " + patronimic();
    QString FI = surname() + " " + name();
    if(FIO.contains(text) || FIO == text ||
       IO.contains(text) || IO == text ||
       FI.contains(text) || FI == text ||
       name().contains(text) || name() == text ||
       surname().contains(text) || surname() == text ||
       patronimic().contains(text) || patronimic() == text)
    {
        return true;
    }
    else
        return false;
}

void users::load()
{
    QSqlRecord record = sql::select(table_name, "*", "id = " + QString::number(my_id));
    QByteArray photo_array;
    QByteArray miniature_array;
    my_photo_adress = record.value("photo").toString();
    QFile file(my_photo_adress + ".png");
    if(file.open(QIODevice::ReadOnly))
    {
        photo_array = file.readAll();

        QFile file2(my_photo_adress + "_mini" + ".png");
        if(file2.open(QIODevice::ReadOnly))
            miniature_array = file2.readAll();

        file.close();
        file2.close();
    }

    if(photo_array.isEmpty()){
        file.setFileName(GLOBAL::directory::image + "null_patient.png");
        if(file.open(QIODevice::ReadOnly))
        {
            photo_array = file.readAll();
            miniature_array = file.readAll();
            file.close();
            file.setFileName(my_photo_adress + ".png");
            if(file.open(QIODevice::WriteOnly))
                file.write(photo_array);
            QFile file2(my_photo_adress + "_mini" + ".png");
            if(file2.open(QIODevice::WriteOnly))
                file2.write(miniature_array);

            file.close();
            file2.close();
        }
    }

    setDatas(photo_array,
             miniature_array,
             record.value("name").toString(),
             record.value("surname").toString(),
             record.value("patronimic").toString(),
             record.value("sex").toInt(),
             SqlDate_to_QDate(record.value("birthday").toString()),
             record.value("email").toString(),
             record.value("phone").toString(),
             record.value("password").toString());
}

void users::insert()
{
    using namespace sql;
    if(my_photo.isEmpty())
    {
        QFile file(GLOBAL::directory::image + "null_patient.png");
        if(file.open(QIODevice::ReadOnly)){
            my_photo = file.readAll();
            file.close();
        }
    }

    QString photo_adress = "Photo_" + my_email;
    QFile file(photo_adress + ".png");
    if(file.open(QIODevice::WriteOnly))
        file.write(my_photo);

    QFile file2(photo_adress + "_mini" + ".png");
    if(file2.open(QIODevice::WriteOnly))
        file2.write(my_miniature);

    file.close();
    file2.close();

    QVector <Value> values;
    values << Value("photo", quotes(photo_adress));
    values << Value("name", quotes(my_name));
    values << Value("surname", quotes(my_surname));
    values << Value("patronimic", quotes(my_patronimic));
    values << Value("sex", QString::number(my_sex));
    values << Value("birthday", QDate_to_SqlDate(my_birthday));
    values << Value("email", quotes(my_email));
    values << Value("phone", quotes(my_phone));
    values << Value("password", quotes(my_password));
    sql::insert(table_name, values);
}

void users::update()
{
    using namespace sql;
    QString photo_adress = "Photo_" + my_email;
    if(photo_adress != my_photo_adress && my_photo_adress != GLOBAL::null_str && my_photo_adress != "")
        QFile(my_photo_adress).remove();
    my_photo_adress = photo_adress;

    QFile file(my_photo_adress + ".png");
    if(file.open(QIODevice::WriteOnly))
        file.write(my_photo);

    QFile file2(photo_adress + "_mini" + ".png");
    if(file2.open(QIODevice::WriteOnly))
        file2.write(my_miniature);

    QVector <Value> values;
    values << Value("photo", quotes(my_photo_adress));
    values << Value("name", quotes(my_name));
    values << Value("surname", quotes(my_surname));
    values << Value("patronimic", quotes(my_patronimic));
    values << Value("sex", QString::number(my_sex));
    values << Value("birthday", QDate_to_SqlDate(my_birthday));
    values << Value("email", quotes(my_email));
    values << Value("phone", quotes(my_phone));
    values << Value("password", quotes(my_password));
    sql::update(table_name, values, "id = " + QString::number(my_id));
}

void users::remove()
{
    if(my_photo_adress != GLOBAL::null_str && my_photo_adress != "")
    {
        QFile(my_photo_adress).remove();
        QFile(my_photo_adress + "_mini").remove();
    }
    sql::remove(table_name, "id = " + QString::number(my_id));
}

int users::id()
{
    if(my_id == -1)
    {
        if(my_email != GLOBAL::null_str)
            my_id = sql::select(table_name, "id", "email = " + quotes(my_email)).value("id").toInt();
        else
            GLOBAL::console_write("Невозможно идентифицировать данные таблицы '" + table_name + "'");
    }
    return my_id;
}

QByteArray users::photo()
{
    if(!my_fullInit && my_photo.isEmpty())
    {
        photo_adress();
        QFile file(my_photo_adress + ".png");
        if(file.open(QIODevice::ReadOnly)){
            my_photo = file.readAll();
            file.close();
        }
    }
    if(my_photo.isEmpty())
    {
        QFile file(GLOBAL::directory::image + "null_patient.png");
        if(file.open(QIODevice::ReadOnly)){
            my_photo = file.readAll();
            file.close();
        }
    }
    return my_photo;
}

QByteArray users::miniature()
{
    if(!my_fullInit && my_photo.isEmpty())
    {
        QString adress = photo_adress() + "_mini" + ".png";
        QFile file(adress);
        if(file.open(QIODevice::ReadOnly))
            my_miniature = file.readAll();
    }
    if(my_miniature.isEmpty())
    {
        QFile file(GLOBAL::directory::image + "null_patient.png");
        if(file.open(QIODevice::ReadOnly)){
            my_miniature = file.readAll();
            file.close();
        }
    }
    return my_miniature;
}

QString users::photo_adress()
{
    if(!my_fullInit && my_photo_adress == GLOBAL::null_str)
    {
        my_photo_adress = sql::select(table_name, "photo", "id = " + QString::number(my_id)).value("photo").toString();
    }
    return my_photo_adress;
}

QString users::name()
{
    if(!my_fullInit && my_name == GLOBAL::null_str)
        my_name = sql::select(table_name, "name", "id = " + QString::number(my_id)).value("name").toString();
    return my_name;
}

QString users::surname()
{
    if(!my_fullInit && my_surname == GLOBAL::null_str)
        my_surname = sql::select(table_name, "surname", "id = " + QString::number(my_id)).value("surname").toString();
    return my_surname;
}

QString users::patronimic()
{
    if(!my_fullInit && my_patronimic == GLOBAL::null_str)
        my_patronimic = sql::select(table_name, "patronimic", "id = " + QString::number(my_id)).value("patronimic").toString();
    return my_patronimic;
}

int users::sex()
{
    if(!my_fullInit && my_sex == -1)
        my_sex = sql::select(table_name, "sex", "id = " + QString::number(my_id)).value("sex").toInt();
    return my_sex;
}

QDate users::birthday()
{
    if(!my_fullInit && my_birthday.year() == 0)
    {
        my_birthday = SqlDate_to_QDate(sql::select(table_name, "birthday", "id = " + QString::number(my_id)).value("birthday").toString());
    }
    return my_birthday;
}

QString users::email()
{
    if(!my_fullInit && my_email == GLOBAL::null_str)
        my_email = sql::select(table_name, "email", "id = " + QString::number(my_id)).value("email").toString();
    return my_email;
}

QString users::phone()
{
    if(!my_fullInit && my_phone == GLOBAL::null_str)
        my_phone = sql::select(table_name, "phone", "id = " + QString::number(my_id)).value("phone").toString();
    return my_phone;
}

QString users::password()
{
    if(!my_fullInit && my_password == GLOBAL::null_str)
        my_password = sql::select(table_name, "password", "id = " + QString::number(my_id)).value("password").toString();
    return my_password;
}

void users::setDatas(QByteArray _photo, QByteArray _miniature, QString _name, QString _surname, QString _patronimic, int _sex, QDate _birthday, QString _email, QString _phone, QString _password)
{
    my_photo = _photo;
    my_miniature = _miniature;
    my_name = _name;
    my_surname = _surname;
    my_patronimic = _patronimic;
    my_sex = _sex;
    my_birthday = _birthday;
    my_email = _email;
    my_phone = _phone;
    my_password = _password;
}

users users::createFromJson(QJsonObject object, Client* client, bool autocreate)
{
    QByteArray avatar = client->getEnclosure(object.find("avatar").value().toString());
    QByteArray miniature = client->getEnclosure(object.find("miniature").value().toString());

    return users(
                avatar,
                miniature,
                object.find("name").value().toString(),
                object.find("surname").value().toString(),
                object.find("patronymic").value().toString(),
                object.find("sex").value().toInt(),
                Json_to_QDate(object.find("birthday").value().toObject()),
                object.find("email").value().toString(),
                object.find("phone").value().toString(),
                object.find("password").value().toString(),
                autocreate
                );
}

QJsonObject users::toJson(Client* client)
{
    QString photo_name = "profile_miniature_" + QString::number(id());
    client->socket_write(photo_name, miniature());

    QJsonObject object
    {
        {"id", id()},
        {"miniature", photo_name},
        {"name", name()},
        {"surname", surname()},
        {"patronymic", patronimic()},
        {"sex", sex()},
        {"birthday", QDate_to_Json(birthday())},
        {"email", email()},
        {"phone", phone()},
        {"password", password()}
    };

    return object;
}

QJsonObject users::toJsonLimited(Client* client)
{
    QString photo_name = "profile_miniature_" + QString::number(id());
    client->socket_write(photo_name, miniature());

    QJsonObject object
    {
        {"miniature", photo_name},
        {"name", name()},
        {"surname", surname()},
        {"patronimic", patronimic()},
        {"sex", sex()},
        {"birthday", QDate_to_Json(birthday())},
        {"email", email()},
        {"phone", phone()},
    };
    return object;
}

QJsonObject users::toJsonPreview(Client* client)
{
    QString photo_name = "profile_miniature_" + QString::number(id());
    client->socket_write(photo_name, miniature());

    QJsonObject object
    {
        {"miniature", photo_name},
        {"name", name()},
        {"surname", surname()},
        {"patronimic", patronimic()},
        {"email", email()},
    };
    return object;
}
