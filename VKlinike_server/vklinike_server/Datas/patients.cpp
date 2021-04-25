#include "patients.h"
#include "users.h"


patients::patients(int _user_id)
{
    my_fullInit = true;
    setDatas(_user_id);
    insert();
    id();
}

patients::patients(QString email, bool fullInit)
{
    my_fullInit = fullInit;
    users user(email, false);
    my_user_id = user.id();
    id();
}

patients::patients(int id, bool fullInit)
{
    my_fullInit = fullInit;
    my_id = id;
    if(my_fullInit)
        load();
}

void patients::load()
{
    QSqlRecord record = sql::select(table_name, "*", "id = " + QString::number(my_id));
    setDatas(record.value("user_id").toInt());
}

void patients::insert()
{
    using namespace sql;
    QVector <Value> values;
    values << Value("user_id", QString::number(my_user_id));
    sql::insert(table_name, values);
}

void patients::update()
{
    using namespace sql;
    QVector <Value> values;
    values << Value("user_id", QString::number(my_user_id));
    sql::update(table_name, values, "id = " + QString::number(my_id));
}

void patients::remove()
{
    sql::remove(table_name, "id = " + QString::number(my_id));
}

int patients::id()
{
    if(my_id == -1 && my_user_id != -1)
    {
        my_id = sql::select(table_name, "id", "user_id = " + QString::number(my_user_id)).value("id").toInt();
    }
    return my_id;
}

int patients::user_id()
{
    if(my_user_id == -1)
        my_user_id = sql::select(table_name, "user_id", "id = " + QString::number(my_id)).value("user_id").toInt();
    return my_user_id;
}

void patients::setDatas(int user_id)
{
    my_user_id = user_id;
}

patients& patients::createFromJson(QJsonObject object, bool autocreate)
{
    return *new patients(object.find("id").value().toInt());
}

QJsonObject patients::toJson()
{
    QJsonObject object
    {
        {"id", id()}
    };
    return object;
}

QJsonObject patients::toJsonLimited()
{
    QJsonObject object
    {
        {"id", id()}
    };
    return object;
}
