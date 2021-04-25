#ifndef DOCTORS_H
#define DOCTORS_H

#include "global.h"

#include <QObject>
#include <QJsonObject>


class doctors
{
public:
    doctors(int user_id, int interval, QTime workday_begin, QTime workday_end, QString _education, QString _job, bool create = true);
    doctors(QString email, bool fullInitialize = true);
    doctors(int id, bool fullInitialize = true);

    static QList <doctors*> findDoctors(QString text = "", int specialization_id = -1);

    void                    load();
    void                    insert();
    void                    update();
    void                    remove();

    int                     id();
    int                     user_id();
    int                     interval();
    QTime                   workday_begin();
    QTime                   workday_end();
    QString                 education();
    QString                 job();
    float                   rating();

    void                    setId(int id);
    void                    setDatas(int user_id, int interval, QTime workday_begin, QTime workday_end, QString _education, QString _job);
    QJsonObject             toJson();
    QJsonObject             toJsonLimited();
    static doctors&         createFromJson(QJsonObject object, bool autocreate = false);

private:
    QString                 table_name              = "doctors";
    bool                    my_fullInit;

    int                     my_id                       = -1;
    int                     my_user_id                  = -1;
    int                     my_interval                 = -1;
    QTime                   my_workday_begin            = QTime(0, 0, 0);
    QTime                   my_workday_end              = QTime(0, 0, 0);
    QString                 my_education                = GLOBAL::null_str;
    QString                 my_job                      = GLOBAL::null_str;

};

#endif // DOCTORS_H
