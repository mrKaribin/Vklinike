#ifndef BASEPROFILEDATA_H
#define BASEPROFILEDATA_H

#include "object.h"
#include "packer.h"

#include <QPixmap>
#include <QDate>


struct BaseProfileData
{
    BaseProfileData() {}
    BaseProfileData(BaseProfileData const &_data);

    void operator =(BaseProfileData const &_data);

    QPixmap photo;
    QString name;
    QString surname;
    QString patronymic;
    int sex;
    QDate birthday;
    QString email;
    QString phone;
    QString password;

};

Q_DECLARE_METATYPE(BaseProfileData);

#endif // BASEPROFILEDATA_H
