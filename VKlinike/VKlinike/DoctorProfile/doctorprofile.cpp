#include "doctorprofile.h"
#include "packer.h"
#include "mainwidget.h"


DoctorProfile::DoctorProfile(DoctorProfileData _data, QWidget* _widget_parent, GlobalData::OutputType _outputType, QThread* _object_thread) : Object()
{
    my_baseProfile = new BaseProfile(_data.base, _widget_parent, _outputType, _object_thread);
    connect(my_baseProfile, &BaseProfile::updateAllBase, this, &DoctorProfile::updateBase);
    my_outputType = _outputType;
    my_widget_parent = _widget_parent;
    my_data = _data;
    DoctorProfile_initialize();
    if(_object_thread == nullptr)
    {
        _object_thread = new QThread();
        _object_thread->start();
    }
    my_doctorIsReady = true;
}


DoctorProfile::DoctorProfile(QString _login, QWidget* _widget_parent, GlobalData::OutputType _outputType, QThread* _object_thread) : Object()
{
    my_baseProfile = new BaseProfile(_login, _widget_parent, _outputType, _object_thread);
    connect(my_baseProfile, &BaseProfile::updateAllBase, this, &DoctorProfile::updateBase);
    my_baseProfile->waitForBaseReady();
    my_outputType = _outputType;
    my_widget_parent = _widget_parent;
    my_login = _login;
    DoctorProfile_initialize();
    if(_object_thread == nullptr)
    {
        _object_thread = new QThread();
        _object_thread->start();
    }
    QTimer::singleShot(10, this, &DoctorProfile::loadingData_doctor);
}

void DoctorProfile::DoctorProfile_initialize()
{
    using namespace GlobalData::query;
    qRegisterMetaType(&my_data);
    server_expextedReusableReply(prefix_reply + prefix_get + profile_doctor);

    my_achievements = new DoctorProfileAchievements(this, my_data, my_widget_parent, my_outputType);
    my_doctor_info = new DoctorProfileInfo(this, my_data, my_widget_parent, my_outputType);
    my_subscriptions = new DoctorProfileSubscriptions(this, my_data, my_widget_parent, my_outputType);
    my_comments = new DoctorProfileComments(this, my_data, my_widget_parent, my_outputType);

    connect(this, &DoctorProfile::updateAllDoctor, my_achievements, &DoctorProfileAchievements::setData);
    connect(this, &DoctorProfile::updateAllDoctor, my_doctor_info, &DoctorProfileInfo::setData);
    connect(this, &DoctorProfile::updateAllDoctor, my_subscriptions, &DoctorProfileSubscriptions::setData);
    connect(this, &DoctorProfile::updateAllDoctor, my_comments, &DoctorProfileComments::setData);
}

void DoctorProfile::loadingData_doctor()
{
    using namespace GlobalData::query;
    QString query;
    Packer packer;
    if(my_login == GlobalData::currentLogin)
    {
        packer << GlobalData::currentLogin;
        packer << GlobalData::currentPassword;
        query = prefix_get + profile_doctor;
    }
    else
    {
        packer << my_login;
        packer << my_login;
        query = prefix_get + profile_doctor + postfix_guest;
    }
    server_request(query, packer.result());
    server_request(prefix_get + specializations, QByteArray());
    server_waitForReady();
    my_doctorIsReady = true;
}

void DoctorProfile::readFromBytes(QByteArray array, GlobalData::OutputType mode)
{
    my_data.specializations.clear();
    my_data.comments.clear();
    my_data.achievements.clear();
    Unpacker unpacker(array);
    if(mode == GlobalData::Output_Owner)
    {
        int size = 0;
        unpacker >> my_data.id;
        unpacker >> my_data.replyInterval;
        unpacker >> my_data.workTime_begin;
        unpacker >> my_data.workTime_end;
        unpacker >> my_data.education;
        unpacker >> my_data.job;

        size = 0;
        unpacker >> size;
        for(int i = 0; i < size; i++)
        {
            Specialization new_spec;
            unpacker >> new_spec.id;
            unpacker >> new_spec.name;
            unpacker >> new_spec.info;

            int size_1 = 0;
            unpacker >> size_1;
            for(int i = 0; i < size_1; i++)
            {
               int sub_duration;
               ServicePackageGroup new_group;
               unpacker >> new_group.id;
               unpacker >> sub_duration;
               switch (sub_duration) {
               case (24 * 1) : {new_group.subscriptionType = GlobalData::Subscription_Day; break;}
               case (24 * 7) : {new_group.subscriptionType = GlobalData::Subscription_Week; break;}
               case (24 * 30) : {new_group.subscriptionType = GlobalData::Subscription_Month; break;}
               }

               int size_2 = 0;
               unpacker >> size_2;
               for(int i = 0; i < size_2; i++)
               {
                    QString valuta;
                    ServicePackage new_package;
                    unpacker >> new_package.id;
                    unpacker >> new_package.cost;
                    unpacker >> valuta;
                    for(int i = 0; i < GlobalData::valutes.size(); i++)
                        if(GlobalData::valutes[i].serviceName == valuta)
                            new_package.valuta = GlobalData::valutes[i];
                    unpacker >> new_package.consultationTime;
                    new_group << new_package;
               }
               new_spec << new_group;
            }

            my_data.specializations << new_spec;
        }

        size = 0;
        unpacker >> size;
        for(int i = 0; i < size; i++)
        {
            Comment new_comment;
            unpacker >> new_comment.id;
            unpacker >> new_comment.name;
            unpacker >> new_comment.surname;
            unpacker >> new_comment.patronimic;
            unpacker >> new_comment.mark;
            unpacker >> new_comment.timepoint;
            unpacker >> new_comment.message;
            my_data.comments << new_comment;
        }
    }
    ready();
    emit updateAllDoctor(my_data);
}

void DoctorProfile::updateBase(BaseProfileData data)
{
    my_data.base = data;
    updateAllDoctor(my_data);
}

void DoctorProfile::readFromBytes_Specializations(QByteArray array)
{
    my_specs.clear();
    int size;
    Unpacker unpacker(array);
    unpacker >> size;
    for(int i = 0; i < size; i++)
    {
        SpecializationData spec;
        unpacker >> spec.id;
        unpacker >> spec.name;
        unpacker >> spec.info;
        my_specs << spec;
    }

    emit updateSpecializations(my_specs);
}

void DoctorProfile::server_reply(QString header, QByteArray body)
{
    using namespace GlobalData::query;
    if(header == prefix_reply + prefix_get + profile_doctor)
        readFromBytes(body);
    if(header == prefix_reply + prefix_get + profile_doctor + postfix_guest)
        readFromBytes(body);
    if(header == prefix_reply + prefix_get + specializations)
        readFromBytes_Specializations(body);
}

void DoctorProfile::waitForDoctorReady()
{
    while(!my_doctorIsReady)
    {
        QApplication::processEvents();
    }
}

BaseProfile* DoctorProfile::baseProfile()
{
    return my_baseProfile;
}

DoctorProfileInfo* DoctorProfile::widget_doctor_info()
{
    return my_doctor_info;
}

DoctorProfileAchievements* DoctorProfile::widget_achievements()
{
    return my_achievements;
}

DoctorProfileComments* DoctorProfile::widget_comments()
{
    return my_comments;
}

DoctorProfileSubscriptions* DoctorProfile::widget_subscriptions()
{
    return my_subscriptions;
}

Button *DoctorProfile::widget_subscriptions_edit(DoctorProfile *_object)
{
    using namespace GlobalData;
    Button *edit_button = new Button("Редактировать");
    edit_button->setFixedSize(screen::geometry.width() - interface::indent * 2, interface::row_size * 1.5);
    edit_button->setFrame(true, GlobalData::Frame_Rounded, 3, interface::color::blue);

    connect(edit_button, &Button::clicked, _object, &DoctorProfile::subscriptions_edit);
    connect(_object, &DoctorProfile::editDoctorProfile, GlobalData::widget_main, &MainWidget::profile_doctor_edit);
    return edit_button;
}

void DoctorProfile::subscriptions_edit()
{
    emit editDoctorProfile(this, my_data, my_specs);
}

void DoctorProfile::package_create(SubscriptionData _data)
{
    using namespace GlobalData::query;
    Packer packer;
    packer << GlobalData::currentLogin;
    packer << GlobalData::currentPassword;
    packer << _data.specialization_id;
    packer << _data.type_interval;
    packer << _data.time;
    packer << _data.cost;
    packer << _data.valuta.serviceName;
    server_request(prefix_new + profile_doctor_tariff, packer.result());
}

void DoctorProfile::package_save(SubscriptionData _data)
{
    using namespace GlobalData::query;
    Packer packer;
    packer << GlobalData::currentLogin;
    packer << GlobalData::currentPassword;
    packer << _data.group_id;
    packer << _data.package_id;
    packer << _data.time;
    packer << _data.cost;
    packer << _data.valuta.serviceName;
    server_request(prefix_update + profile_doctor_tariff, packer.result());
}

void DoctorProfile::package_remove(int spec_id, int group_id, int package_id)
{
    using namespace GlobalData::query;
    Packer packer;
    packer << GlobalData::currentLogin;
    packer << GlobalData::currentPassword;
    packer << package_id;
    server_request(prefix_remove + profile_doctor_tariff, packer.result());
}

void DoctorProfile::updateWidget(DoctorProfileData _new_data)
{

}
