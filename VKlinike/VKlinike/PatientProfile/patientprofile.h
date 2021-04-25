#ifndef PATIENTPROFILE_H
#define PATIENTPROFILE_H

#include "object.h"
#include "patientprofiledata.h"
#include "PatientProfile/patientprofilewidget.h"


class PatientProfile : public Object
{
    Q_OBJECT
public:
    PatientProfile(PatientProfileData _data, QWidget* _widget_parent = nullptr, GlobalData::OutputType _outputType = GlobalData::Output_Guest, QThread* _object_thread = nullptr);
    PatientProfile(QString _login, QWidget* _widget_parent = nullptr, GlobalData::OutputType _outputType = GlobalData::Output_Guest, QThread* _object_thread = nullptr);
    void PatientProfile_initialize();

    BaseProfile                        *baseProfile();
    PatientProfileSubscriptions        *subscriptions();

private:
    BaseProfile                        *my_baseProfile;
    PatientProfileData                  my_data;
    PatientProfileSubscriptions*        my_subscriptions;

    QWidget                            *my_widget_parent;
    GlobalData::OutputType              my_outputType;
    QString                             my_login                        = "";
    bool                                my_patientIsReady               = false;

public slots:
    void                                server_reply(QString header, QByteArray body) override;

    void                                load();
    void                                readFromBytes(QByteArray array, GlobalData::OutputType mode = GlobalData::Output_Owner);
    void                                waitForPatientReady();


signals:
    void update_all_widgets(PatientProfileData);

};

#endif // PATIENTPROFILE_H
