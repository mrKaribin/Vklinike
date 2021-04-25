#ifndef PATIENTS_H
#define PATIENTS_H

#include "global.h"

#include <QObject>
#include <QJsonObject>


class patients
{
public:
    patients(int user_id);
    patients(QString email, bool fullInit);
    patients(int id, bool fullInit);

    void                initialize();
    void                load();
    void                insert();
    void                update();
    void                remove();

    int                 id();
    int                 user_id();

    void                setDatas(int user_id);
    QJsonObject         toJson();
    QJsonObject         toJsonLimited();
    static patients&    createFromJson(QJsonObject object, bool autocreate = false);

private:
    QString             table_name              = "patients";
    bool                my_fullInit;
    int                 my_id                   = -1;
    int                 my_user_id              = -1;

};

#endif // PATIENTS_H
