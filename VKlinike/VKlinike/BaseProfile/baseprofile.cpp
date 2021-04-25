#include "baseprofile.h"
#include "packer.h"
#include "mainwidget.h"



BaseProfile::BaseProfile(BaseProfileData _data, QWidget *_widget_parent, GlobalData::OutputType _outputType, QThread *_object_thread) : Object()
{
    my_outputType = _outputType;
    my_widget_parent = _widget_parent;
    my_data_base = _data;
    BaseProfile_initialize();
    if(_object_thread == nullptr)
    {
        _object_thread = new QThread();
        _object_thread->start();
    }
    moveToThread(_object_thread);
    my_baseIsReady = true;
}

BaseProfile::BaseProfile(QString _login, QWidget *_widget_parent, GlobalData::OutputType _outputType, QThread *_object_thread) : Object()
{
    my_outputType = _outputType;
    my_widget_parent = _widget_parent;
    my_login = _login;
    BaseProfile_initialize();
    if(_object_thread == nullptr)
    {
        _object_thread = new QThread();
        _object_thread->start();
    }
    moveToThread(_object_thread);
    QTimer::singleShot(10, this, &BaseProfile::loadingData_base);
}

void BaseProfile::BaseProfile_initialize()
{
    using namespace GlobalData;
    qRegisterMetaType(&my_data_base);

    my_header = new BaseProfileHeader(this, my_data_base, my_widget_parent, my_outputType);
    my_info = new BaseProfileInfo(this, my_data_base, my_widget_parent, my_outputType);
    my_editButton = new Button("Редактировать");
    my_editButton->setFixedSize(screen::geometry.width() - interface::indent * 2, interface::row_size * 1.5);
    my_editButton->setFrame(true, GlobalData::Frame_Rounded, 3, interface::color::blue);

    connect(this, &BaseProfile::updateAllBase, my_header, &BaseProfileHeader::setData);
    connect(this, &BaseProfile::updateAllBase, my_info, &BaseProfileInfo::setData);
    connect(my_editButton, &Button::clicked, this, &BaseProfile::edit);
    connect(this, &BaseProfile::editing, GlobalData::widget_main, &MainWidget::profile_base_edit);
}

void BaseProfile::loadingData_base()
{
    using namespace GlobalData::query;
    QString query;
    Packer packer;
    if(my_login == GlobalData::currentLogin)
    {
        packer << GlobalData::currentLogin;
        packer << GlobalData::currentPassword;
        query = prefix_get + profile_base;
    }
    else
    {
        packer << my_login;
        query = prefix_get + profile_base + postfix_guest;
    }
    server_request(query, packer.result());
    server_waitForReady();
    emit updateAllBase(my_data_base);
    my_baseIsReady = true;
}

void BaseProfile::waitForBaseReady()
{
    while(!my_baseIsReady)
    {
        QApplication::processEvents();
    }
}

BaseProfileHeader* BaseProfile::widget_header()
{
    return my_header;
}

BaseProfileInfo* BaseProfile::widget_info()
{
    return my_info;
}

Button* BaseProfile::widget_edit()
{
    return my_editButton;
}

void BaseProfile::readFromBytes(QByteArray array, GlobalData::OutputType mode)
{
    Unpacker unpacker(array);
    if(mode == GlobalData::Output_Owner)
    {
        QByteArray photo_arr;
        unpacker >> my_data_base.name;
        unpacker >> my_data_base.surname;
        unpacker >> my_data_base.patronymic;
        unpacker >> photo_arr;
        my_data_base.photo.loadFromData(photo_arr);
        unpacker >> my_data_base.sex;
        unpacker >> my_data_base.birthday;
        unpacker >> my_data_base.email;
        unpacker >> my_data_base.phone;
        unpacker >> my_data_base.password;
        GlobalData::currentName = my_data_base.name;
    }
    ready();
}

void BaseProfile::server_reply(QString header, QByteArray body)
{
    using namespace GlobalData::query;
    if(header == prefix_reply + prefix_get + profile_base)
        readFromBytes(body);
    if(header == prefix_reply + prefix_get + profile_base + postfix_guest)
        readFromBytes(body);
}

void BaseProfile::edit()
{
    emit editing(this, my_data_base);
}

void BaseProfile::edited(BaseProfileData _data)
{
    using namespace GlobalData::query;
    using namespace GlobalData::directory;
    QByteArray photo_array;
    QFile photo_file(image + "profile_photo.jpg");
    if(!photo_file.open(QIODevice::WriteOnly))
        GlobalData::error_Show("Фото", "Не удалось открыть файл");
    if(!_data.photo.save(&photo_file))
        GlobalData::error_Show("Фото", "Не удалось сохранить");
    photo_file.close();
    if(!photo_file.open(QIODevice::ReadOnly))
        GlobalData::error_Show("Фото", "Не удалось открыть файл 2");
    photo_array = photo_file.readAll();
    photo_file.remove();

    Packer packer;
    packer << _data.name;
    packer << _data.surname;
    packer << _data.patronymic;
    packer << photo_array;
    packer << _data.sex;
    packer << _data.birthday;
    packer << _data.email;
    packer << _data.phone;
    packer << GlobalData::currentPassword;
    server_request(prefix_update + profile_base, packer.result());
    my_data_base = _data;
    emit updateAllBase(my_data_base);
}

void BaseProfile::created(BaseProfileData _data)
{
    using namespace GlobalData::query;
    using namespace GlobalData::directory;
    QByteArray photo_array;
    QFile photo_file(image + "profile_photo.jpg");
    if(!photo_file.open(QIODevice::WriteOnly))
        GlobalData::error_Show("Фото", "Не удалось открыть файл");
    if(!_data.photo.save(&photo_file))
        GlobalData::error_Show("Фото", "Не удалось сохранить");
    photo_file.close();
    if(!photo_file.open(QIODevice::ReadOnly))
        GlobalData::error_Show("Фото", "Не удалось открыть файл 2");
    photo_array = photo_file.readAll();
    photo_file.remove();

    Packer packer;
    packer << _data.name;
    packer << _data.surname;
    packer << _data.patronymic;
    packer << photo_array;
    packer << _data.sex;
    packer << _data.birthday;
    packer << _data.email;
    packer << _data.phone;
    packer << _data.password;
    server_request(prefix_new + profile_base, packer.result());
    my_data_base = _data;
    emit updateAllBase(my_data_base);
}

void BaseProfile::updateWidget(BaseProfileData _new_data)
{
    if(my_data_base.name != _new_data.name)
    {
        my_data_base.name = _new_data.name;
        emit name_change(my_data_base.name);
    }
    if(my_data_base.surname != _new_data.surname)
    {
        my_data_base.surname = _new_data.surname;
        emit surname_change(my_data_base.surname);
    }
    if(my_data_base.patronymic != _new_data.patronymic)
    {
        my_data_base.patronymic = _new_data.patronymic;
        emit patronymic_change(my_data_base.patronymic);
    }
    if(my_data_base.email != _new_data.email)
    {
        my_data_base.email = _new_data.email;
        emit email_change(my_data_base.email);
    }
    if(my_data_base.phone != _new_data.phone && _new_data.phone.size() >= 11 && _new_data.phone.size() < 14)
    {
        my_data_base.phone = _new_data.phone;
        emit phone_change(my_data_base.phone);
    }
}
