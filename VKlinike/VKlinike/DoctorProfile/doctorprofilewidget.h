#ifndef DOCTORPROFILEWIDGET_H
#define DOCTORPROFILEWIDGET_H

#include "doctorprofiledata.h"
#include "widget.h"

#include <QLayout>


struct DoctorProfileData;
struct Specialization;
struct ServicePackage;
struct ServicePackageGroup;
class DPW_Specialization;
class DPW_ServicePackageGroup;
class DoctorProfileSubscriptions;
class DoctorProfile;


class DPW_ServicePackage : public Button
{
    Q_OBJECT
public:
    DPW_ServicePackage(DPW_ServicePackageGroup* parent, ServicePackage data, GlobalData::OutputType _outputType = GlobalData::Output_Guest);
    QLabel* my_cost;
    QLabel* my_consultationTime;
    ServicePackage my_data;

private:

public slots:
    void buy();

};


class DPW_ServicePackageGroup : public Widget
{
    Q_OBJECT
public:
    DPW_ServicePackageGroup(DPW_Specialization* parent, ServicePackageGroup data, GlobalData::OutputType _outputType = GlobalData::Output_Guest);

    QLabel* my_interval;
    QVector <DPW_ServicePackage*>   my_packages;
    ServicePackageGroup             my_data;

public slots:


};


class DPW_Specialization : public Widget
{
    Q_OBJECT
public:
    DPW_Specialization(DoctorProfileSubscriptions* parent, Specialization data, GlobalData::OutputType _outputType = GlobalData::Output_Guest);

    QLabel* my_name;
    QVector <DPW_ServicePackageGroup*> my_groups;
    Specialization                     my_data;

public slots:


signals:


};


class DoctorProfileSubscriptions : public Widget
{
    Q_OBJECT
public:
    DoctorProfileSubscriptions(DoctorProfile* _object, DoctorProfileData _data, QWidget* parent = nullptr, GlobalData::OutputType _outputType = GlobalData::Output_Guest);

    DoctorProfileData my_data;
private:
    DoctorProfile                  *my_object;
    GlobalData::OutputType          my_outputType;

    QVBoxLayout                    *layout;
    QVBoxLayout                    *layout_specs;
    Button                         *wgt_edit;
    QVector <DPW_Specialization*>   my_specializations;

public slots:
    void setData(DoctorProfileData _data);

};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct Comment;
class DoctorProfileComments;


class DPC_Comment : public Widget
{
    Q_OBJECT
public:
    DPC_Comment(DoctorProfileComments* _parent, Comment _data, GlobalData::OutputType _outputType);

    QLabel* header;
    QLabel* message;
    QLabel* star[5];
};


class DoctorProfileComments : public Widget
{
    Q_OBJECT
public:
    DoctorProfileComments(DoctorProfile* _object, DoctorProfileData _data, QWidget* parent = nullptr, GlobalData::OutputType _outputType = GlobalData::Output_Guest);

private:
    DoctorProfile              *my_object;
    QVBoxLayout                *layout_comments;
    GlobalData::OutputType      my_outputType;
    QLabel                     *averageMark;
    QVector <DPC_Comment*>      comments;

public slots:
    void setData(DoctorProfileData _data);

};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct Achievement;
class DoctorProfileAchievements;


class DPA_Achievement : public Widget
{
    Q_OBJECT
public:
    DPA_Achievement(DoctorProfileAchievements* _parent, Achievement _data, GlobalData::OutputType _outputType);

    QLabel* header;
    QLabel* message;
};


class DoctorProfileAchievements : public Widget
{
    Q_OBJECT
public:
    DoctorProfileAchievements(DoctorProfile* _object, DoctorProfileData _data, QWidget* parent = nullptr, GlobalData::OutputType _outputType = GlobalData::Output_Guest);

private:
    DoctorProfile*                  my_object;
    QHBoxLayout                    *layout;
    GlobalData::OutputType          my_outputType;
    QVector <DPA_Achievement*>      achievements;

public slots:
    void setData(DoctorProfileData _data);


};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class DoctorProfileInfo : public Widget
{
    Q_OBJECT
public:
    DoctorProfileInfo(DoctorProfile* _object, DoctorProfileData _data, QWidget* parent = nullptr, GlobalData::OutputType _outputType = GlobalData::Output_Guest);

private:
    DoctorProfile* my_object;
    QLabel* my_workTime;
    QLabel* my_replyInterval;
    QLabel* my_education;
    QLabel* my_job;

public slots:
    void setData(DoctorProfileData _data);


};

#endif // DOCTORPROFILEWIDGET_H
