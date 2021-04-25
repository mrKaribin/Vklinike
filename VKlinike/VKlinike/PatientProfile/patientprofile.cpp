#include "patientprofile.h"


PatientProfile::PatientProfile(PatientProfileData _data, QWidget* _widget_parent, GlobalData::OutputType _outputType, QThread* _object_thread) : Object()
{
    my_outputType = _outputType;
    my_widget_parent = _widget_parent;
    my_data = _data;
    my_baseProfile = new BaseProfile(_data.base, _widget_parent, _outputType, _object_thread);
    my_baseProfile->waitForBaseReady();
    PatientProfile_initialize();
    if(_object_thread == nullptr)
    {
        _object_thread = new QThread();
        _object_thread->start();
    }
    my_patientIsReady = true;
}

PatientProfile::PatientProfile(QString _login, QWidget* _widget_parent, GlobalData::OutputType _outputType, QThread* _object_thread)
{
    my_login = _login;
    my_outputType = _outputType;
    my_widget_parent = _widget_parent;
    my_baseProfile = new BaseProfile(_login, _widget_parent, _outputType, _object_thread);
    my_baseProfile->waitForBaseReady();
    PatientProfile_initialize();
    if(_object_thread == nullptr)
    {
        _object_thread = new QThread();
        _object_thread->start();
    }
    QTimer::singleShot(10, this, &PatientProfile::load);
}

void PatientProfile::PatientProfile_initialize()
{
    qRegisterMetaType(&my_data);

    my_subscriptions = new PatientProfileSubscriptions(this, my_data, my_widget_parent, my_outputType);

    connect(this, &PatientProfile::update_all_widgets, my_subscriptions, &PatientProfileSubscriptions::setData);
}

BaseProfile* PatientProfile::baseProfile()
{
    return my_baseProfile;
}

PatientProfileSubscriptions* PatientProfile::subscriptions()
{
    return my_subscriptions;
}

void PatientProfile::load()
{
    using namespace GlobalData::query;
    QString query;
    Packer packer;
    if(my_login == GlobalData::currentLogin)
    {
        packer << GlobalData::currentLogin;
        packer << GlobalData::currentPassword;
        query = prefix_get + profile_patient;
    }
    else
    {
        packer << my_login;
        query = prefix_get + profile_patient + postfix_guest;
    }
    server_request(query, packer.result());
    server_waitForReady();
    emit update_all_widgets(my_data);
    my_patientIsReady = true;
}

void PatientProfile::readFromBytes(QByteArray array, GlobalData::OutputType mode)
{
    Unpacker unpacker(array);
    if(mode == GlobalData::Output_Owner)
    {
        unpacker >> my_data.id;
        int size = 0;
        unpacker >> size;
        for(int i = 0; i < size; i++)
        {
            FinalServicePackage new_sub;
            QString valuta;
            int interval;
            unpacker >> new_sub.id;
            unpacker >> new_sub.cost;

            unpacker >> valuta;
            for(int i = 0; i < GlobalData::valutes.size(); i++)
                if(GlobalData::valutes[i].serviceName == valuta)
                    new_sub.valuta = GlobalData::valutes[i];

            unpacker >> interval;
            switch (interval) {
            case (24 * 1) : {new_sub.subscriptionType = GlobalData::Subscription_Day; break;}
            case (24 * 7) : {new_sub.subscriptionType = GlobalData::Subscription_Week; break;}
            case (24 * 30) : {new_sub.subscriptionType = GlobalData::Subscription_Month; break;}}

            unpacker >> new_sub.consultationTime;
            unpacker >> new_sub.startTimepoint;
            unpacker >> new_sub.finishTimepoint;
        }
    }
    ready();
}

void PatientProfile::server_reply(QString header, QByteArray body)
{
    using namespace GlobalData::query;
    if(header == prefix_reply + prefix_get + profile_doctor)
        readFromBytes(body);
    if(header == prefix_reply + prefix_get + profile_doctor + postfix_guest)
        readFromBytes(body);
}

void PatientProfile::waitForPatientReady()
{
    while(!my_patientIsReady)
    {
        QApplication::processEvents();
    }
}
