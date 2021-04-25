#include "doctors.h"
#include "packages.h"
#include "comments.h"
#include "users.h"


doctors::doctors(int _user_id, int _interval, QTime _workday_begin, QTime _workday_end, QString _education, QString _job, bool create)
{
    my_fullInit = true;
    setDatas(_user_id, _interval, _workday_begin, _workday_end, _education, _job);
    if(create)
        insert();
    id();
}

doctors::doctors(QString _email, bool fullInitialize)
{
    my_fullInit = fullInitialize;
    users user(_email, false);
    my_user_id = user.id();
    id();
    if(fullInitialize)
        load();
}

doctors::doctors(int id, bool fullInitialize)
{
    my_fullInit = fullInitialize;
    my_id = id;
    if(fullInitialize)
        load();
}

QList <doctors*> doctors::findDoctors(QString text, int specialization_id){
    QList <doctors*> result;
    QString str = "SELECT * FROM doctors ;";
    QSqlQuery query("CUSTOM_QUERY", *GLOBAL::database_current());
    DEBUG_LOG(str);
    if(!query.exec(str))
        GLOBAL::console_write("Ошибка выполнения SQL запроса: " + str + "\n");
    QSqlRecord record = query.record();
    while(query.next())
    {
        bool ok = false;
        int doctor_id = query.value(record.indexOf("id")).toInt();
        users user(doctors(doctor_id).user_id());
        if(text.isEmpty() || user.search(text))
        {
            QMultiMap <int, packages*> packs = packages::findPackages(doctor_id);
            if(packs.size() == 0 && specialization_id == -1)
                ok = true;
            foreach(auto key, packs.uniqueKeys())
                if(key == specialization_id || specialization_id == -1)
                {
                    ok = true;
                    break;
                }
            if(ok)
            {
                result << new doctors(query.value(record.indexOf("user_id")).toInt(),
                                      query.value(record.indexOf("interval")).toInt(),
                                      SqlTime_to_QTime(query.value(record.indexOf("workday_begin")).toString()),
                                      SqlTime_to_QTime(query.value(record.indexOf("workday_end")).toString()),
                                      query.value(record.indexOf("education")).toString(),
                                      query.value(record.indexOf("job")).toString(),
                                      false);
            }
        }
    }
    return result;
}

void doctors::load()
{
    QSqlRecord record = sql::select(table_name, "*", "id = " + QString::number(my_id));
    setDatas(record.value("user_id").toInt(),
             record.value("interval").toInt(),
             SqlTime_to_QTime(record.value("workday_begin").toString()),
             SqlTime_to_QTime(record.value("workday_end").toString()),
             record.value("education").toString(),
             record.value("job").toString());
}

void doctors::insert()
{
    using namespace sql;
    QVector <Value> values;
    values << Value("user_id", QString::number(my_user_id));
    values << Value("interval", QString::number(my_interval));
    values << Value("workday_begin", QTime_to_SqlTime(my_workday_begin));
    values << Value("workday_end", QTime_to_SqlTime(my_workday_end));
    values << Value("education", quotes(my_education));
    values << Value("job", quotes(my_job));
    sql::insert(table_name, values);
}

void doctors::update()
{
    using namespace sql;
    QVector <Value> values;
    values << Value("user_id", QString::number(my_user_id));
    values << Value("interval", QString::number(my_interval));
    values << Value("workday_begin", QTime_to_SqlTime(my_workday_begin));
    values << Value("workday_end", QTime_to_SqlTime(my_workday_end));
    values << Value("education", quotes(my_education));
    values << Value("job", quotes(my_job));
    sql::update(table_name, values, "id = " + QString::number(my_id));
}

void doctors::remove()
{
    sql::remove(table_name, "id = " + QString::number(my_id));
}

int doctors::id()
{
    if(my_id == -1 && my_user_id != -1)
    {
        my_id = sql::select(table_name, "id", "user_id = " + QString::number(my_user_id)).value("id").toInt();
    }
    return my_id;
}

int doctors::user_id()
{
    if(!my_fullInit && my_user_id == -1)
        my_user_id = sql::select(table_name, "user_id", "id = " + QString::number(my_id)).value("user_id").toInt();
    return my_user_id;
}

int doctors::interval()
{
    if(!my_fullInit && my_interval == -1)
        my_interval = sql::select(table_name, "interval", "id = " + QString::number(my_id)).value("interval").toInt();
    return my_interval;
}

QTime doctors::workday_begin()
{
    if(!my_fullInit && my_workday_begin.hour() == 0)
        my_workday_begin = SqlTime_to_QTime(sql::select(table_name, "workday_begin", "id = " + QString::number(my_id)).value("workday_begin").toString());
    return my_workday_begin;
}

QTime doctors::workday_end()
{
    if(!my_fullInit && my_workday_end.hour() == 0)
        my_workday_end = SqlTime_to_QTime(sql::select(table_name, "workday_end", "id = " + QString::number(my_id)).value("workday_end").toString());
    return my_workday_end;
}

QString doctors::education()
{
    if(!my_fullInit && my_education == GLOBAL::null_str)
        my_education = sql::select(table_name, "education", "id = " + QString::number(my_id)).value("education").toString();
    return my_education;
}

QString doctors::job()
{
    if(!my_fullInit && my_job == GLOBAL::null_str)
        my_job = sql::select(table_name, "job", "id = " + QString::number(my_id)).value("job").toString();
    return my_job;
}

float doctors::rating()
{
    QList <comments*> doctor_comments = comments::findCommentsByDoctor(id());
    if(doctor_comments.size() == 0)
        return 0;
    float summa = 0, result;
    foreach(auto comment, doctor_comments)
        summa += comment->rating();
    result = summa / doctor_comments.size();
    return result;
}


void doctors::setId(int _id)
{
    my_id = _id;
}

void doctors::setDatas(int _user_id, int _interval, QTime _workday_begin, QTime _workday_end, QString _education, QString _job)
{
    my_user_id = _user_id;
    my_interval = _interval;
    my_workday_begin = _workday_begin;
    my_workday_end = _workday_end;
    my_education = _education;
    my_job = _job;
}

doctors& doctors::createFromJson(QJsonObject object, bool autocreate)
{
    doctors* doctor = new doctors(object.find("user_id").value().toInt(),
                   object.find("replyInterval").value().toInt(),
                   Json_to_QTime(object.find("workTime_begin").value().toObject()),
                   Json_to_QTime(object.find("workTime_end").value().toObject()),
                   object.find("education").value().toString(),
                   object.find("job").value().toString(),
                   autocreate
                   );
    doctor->setId(object.find("id").value().toInt());
    return *doctor;
}

QJsonObject doctors::toJson()
{
    QJsonObject object
    {
        {"id", id()},
        {"user_id", user_id()},
        {"replyInterval", interval()},
        {"workTime_begin", QTime_to_Json(workday_begin())},
        {"workTime_end", QTime_to_Json(workday_end())},
        {"education", education()},
        {"job", job()}
    };
    return object;
}

QJsonObject doctors::toJsonLimited()
{
    QJsonObject object
    {
        {"id", id()},
        {"user_id", user_id()},
        {"replyInterval", interval()},
        {"workTime_begin", QTime_to_Json(workday_begin())},
        {"workTime_end", QTime_to_Json(workday_end())},
        {"education", education()},
        {"job", job()}
    };
    return object;
}
