#ifndef DOCTORPROFILE_H
#define DOCTORPROFILE_H

#include "doctorprofiledata.h"
#include "Search/searchdata.h"
#include "BaseProfile/baseprofile.h"
#include "DoctorProfile/doctorprofilewidget.h"
#include "DoctorProfile/doctorpackageedit.h"


class DoctorProfile : public Object
{
    Q_OBJECT
public:
    DoctorProfile(DoctorProfileData _data, QWidget* _widget_parent = nullptr, GlobalData::OutputType _outputType = GlobalData::Output_Guest, QThread* _object_thread = nullptr);
    DoctorProfile(QString _login, QWidget* _widget_parent = nullptr, GlobalData::OutputType _outputType = GlobalData::Output_Guest, QThread* _object_thread = nullptr);
    void                                DoctorProfile_initialize();

    void                                loadingData_doctor();
    void                                waitForDoctorReady();

    BaseProfile                        *baseProfile();
    DoctorProfileInfo                  *widget_doctor_info();
    DoctorProfileAchievements          *widget_achievements();
    DoctorProfileComments              *widget_comments();
    DoctorProfileSubscriptions         *widget_subscriptions();
    static Button                      *widget_subscriptions_edit(DoctorProfile *_object);

private:
    BaseProfile                        *my_baseProfile;
    DoctorProfileData                   my_data;
    QList <SpecializationData>          my_specs;
    DoctorProfileInfo*                  my_doctor_info;
    DoctorProfileAchievements*          my_achievements;
    DoctorProfileComments*              my_comments;
    DoctorProfileSubscriptions*         my_subscriptions;

    QWidget                            *my_widget_parent;
    GlobalData::OutputType              my_outputType;
    QString                             my_login                        = "";
    bool                                my_doctorIsReady                = false;

public slots:
    void updateWidget(DoctorProfileData _new_data);
    void updateBase(BaseProfileData data);
    void server_reply(QString header, QByteArray body) override;

    void readFromBytes(QByteArray array, GlobalData::OutputType mode = GlobalData::Output_Owner);
    void readFromBytes_Specializations(QByteArray array);

    void subscriptions_edit();

    void package_create(SubscriptionData _data);
    void package_save(SubscriptionData _data);
    void package_remove(int spec_id, int group_id, int package_id);

signals:
    void updateAllDoctor(DoctorProfileData _new_data);
    void updateSpecializations(QList <SpecializationData>);
    void editDoctorProfile(DoctorProfile *object, DoctorProfileData data, QList <SpecializationData> _specs);
};

#endif // DOCTORPROFILE_H
