#ifndef DOCTORPROFILEDATA_H
#define DOCTORPROFILEDATA_H

#include "BaseProfile/baseprofile.h"
#include "globaldata.h"
#include "object.h"

#include <QDateTime>


struct ServicePackage
{
    ServicePackage() {};
    ServicePackage(int _id, int _cost, GlobalData::Valuta _val, int _consTime)
    {
        id = _id;
        cost = _cost;
        valuta = _val;
        consultationTime = _consTime;
    }

    int id;
    int cost;
    GlobalData::Valuta valuta;
    int consultationTime;
};


struct ServicePackageGroup
{
    ServicePackageGroup() {};
    ServicePackageGroup(int _id, GlobalData::SubscriptionType _type)
    {
        id = _id;
        subscriptionType = _type;
    }

    void operator <<(ServicePackage package)
    {
        packages << package;
    }

    int id;
    GlobalData::SubscriptionType subscriptionType;
    QVector <ServicePackage> packages;
};


struct Specialization
{
    Specialization() {};
    Specialization(int _id, QString _name, QString _info)
    {
        id = _id;
        name = _name;
        info = _info;
    }

    void operator <<(ServicePackageGroup group)
    {
        groups << group;
    }

    int id;
    QString name;
    QString info;
    QVector <ServicePackageGroup> groups;
};


struct Achievement
{
    Achievement() {}
    Achievement(int _id, QString _header, QString _comment, QString _info)
    {
        id = _id;
        header = _header;
        comment = _comment;
        info = _info;
    }

    int id;
    QString header;
    QPixmap header_icon;
    QString comment;
    QString info;
};


struct Comment
{
    Comment() {}
    Comment(int _id, QString _name, int _mark, QString _message)
    {
        id = _id;
        name = _name;
        mark = _mark;
        message = _message;
    }

    int id;
    QString name;
    QString surname;
    QString patronimic;
    QDateTime timepoint;
    int mark;
    QString message;
};


struct DoctorProfileData
{
    DoctorProfileData() {};
    DoctorProfileData(DoctorProfileData const &data);

    void operator =(DoctorProfileData const &data);
    void operator <<(Specialization specialization)
    {
        specializations << specialization;
    }
    void operator <<(Achievement achieve)
    {
        achievements << achieve;
    }
    void operator <<(Comment comment)
    {
        comments << comment;
    }

    void load(QString login, bool waiting = true);
    void readFromBytes(QByteArray array, GlobalData::OutputType mode = GlobalData::Output_Owner);
    void save();

    BaseProfileData base;
    int id;
    QString education;
    QString job;
    QTime workTime_begin;
    QTime workTime_end;
    int replyInterval;
    QVector <Achievement> achievements;
    QVector <Comment> comments;
    QVector <Specialization> specializations;

};


struct SubscriptionData
{
    SubscriptionData() {};
    SubscriptionData(DoctorProfileData _data, int spec_id, int group_id, int package_id);

    void                setSpecializations(Specialization spec);
    void                setGroup(ServicePackageGroup group);
    void                setPackage(ServicePackage package);

    int                 specialization_id = -1;
    QString             specialization_name;
    QString             specialization_info;

    int                 group_id = -1;
    QString             type_name;
    int                 type_interval;

    int                 package_id = -1;
    int                 cost = 0;
    GlobalData::Valuta  valuta;
    int                 time = 0;
};

Q_DECLARE_METATYPE(DoctorProfileData);

#endif // DOCTORPROFILEDATA_H
