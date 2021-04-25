#ifndef PATIENTPROFILEWIDGET_H
#define PATIENTPROFILEWIDGET_H

#include "patientprofiledata.h"
#include "widget.h"


struct PatientProfileData;
struct FinalServicePackage;
class PatientProfileSubscriptions;
class PatientProfile;


class PPW_FullServicePackage : public Widget
{
    Q_OBJECT
public:
    PPW_FullServicePackage(PatientProfileSubscriptions* parent, FinalServicePackage data, GlobalData::OutputType _outputType = GlobalData::Output_Guest);

    void timeBalance_Change(QDate finishData, QTime finishTime);

    QLabel* my_specialization;
    QLabel* my_cost;
    QLabel* my_consultationBalance;
    QLabel* my_timeBalance;

public slots:


};


class PatientProfileSubscriptions : public Widget
{
    Q_OBJECT
public:
    PatientProfileSubscriptions(PatientProfile* _object, PatientProfileData _data, QWidget* parent = nullptr, GlobalData::OutputType _outputType = GlobalData::Output_Guest);


private:
    QVBoxLayout*                            layout;

    PatientProfile                         *my_object;
    PatientProfileData                      my_data;
    GlobalData::OutputType                  my_outputType;
    QVector <PPW_FullServicePackage*>       my_packages;

public slots:
    void setData(PatientProfileData _data);

signals:


};

#endif // PATIENTPROFILEWIDGET_H
