#ifndef PATIENTPROFILEDATA_H
#define PATIENTPROFILEDATA_H

#include "globaldata.h"
#include "BaseProfile/baseprofile.h"

#include <QObject>
#include <QDateTime>


struct FinalServicePackage
{
    FinalServicePackage() {};
    FinalServicePackage(QString _specialization, GlobalData::SubscriptionType _subscriptionType, QDateTime _startTimepoint, QDateTime _finishTimepoint, int _cost, GlobalData::Valuta _val, int _consTime)
    {
        specialization = _specialization;
        subscriptionType = _subscriptionType;
        startTimepoint = _startTimepoint;
        finishTimepoint = _finishTimepoint;
        cost = _cost;
        valuta = _val;
        consultationTime = _consTime;
    }

    int id;
    QString specialization;
    QString specialization_info;
    QDateTime startTimepoint;
    QDateTime finishTimepoint;
    GlobalData::SubscriptionType subscriptionType;
    int interval;
    int cost;
    GlobalData::Valuta valuta;
    int consultationTime;
};


struct PatientProfileData
{

    void operator <<(FinalServicePackage _package)
    {
        packages << _package;
    }

    int id;
    BaseProfileData base;
    QVector <FinalServicePackage> packages;
};

Q_DECLARE_METATYPE(PatientProfileData);

#endif // PATIENTPROFILEDATA_H
