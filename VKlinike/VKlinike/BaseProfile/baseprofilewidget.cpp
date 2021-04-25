#include "baseprofilewidget.h"
#include "baseprofile.h"


BaseProfileHeader::BaseProfileHeader(BaseProfile* _object, BaseProfileData _data, QWidget* parent, GlobalData::OutputType _outputType) : Widget(parent)
{
    using namespace GlobalData::interface;
    using namespace GlobalData;

    my_object = _object;
    my_photo = new QLabel();
    my_name = new QLabel();
    my_surname = new QLabel();
    my_patronymic = new QLabel();
    QGridLayout* layout_header = new QGridLayout();

    my_photo->setFixedSize(interface::photo_size, interface::photo_size);
    my_photo->setPixmap(_data.photo);

    my_name->setFixedSize(screen::geometry.width() * 0.6, interface::row_size);
    setTextSize(my_name, text_size);
    my_surname->setFixedSize(screen::geometry.width() * 0.6, interface::row_size);
    setTextSize(my_surname, text_size);
    my_patronymic->setFixedSize(screen::geometry.width() * 0.6, interface::row_size);
    setTextSize(my_patronymic, text_size);
    setFixedWidth(screen::geometry.width() - indent * 2);
    setFrame(true, Frame_Rounded, 4, GlobalData::interface::color::blue);

    layout_header->addWidget(my_photo, 0, 0, 3, 1);
    if(!(GlobalData::currentMode == GlobalData::Mode_Doctor && _outputType != GlobalData::Output_Owner))
        layout_header->addWidget(my_surname, 0, 1, 1, 2);
    layout_header->addWidget(my_name, 1, 1, 1, 2);
    if(!(GlobalData::currentMode == GlobalData::Mode_Doctor && _outputType != GlobalData::Output_Owner))
        layout_header->addWidget(my_patronymic, 2, 1, 1, 2);
    layout_header->setSizeConstraint(QLayout::SetMinAndMaxSize);
    layout_header->setSpacing(indent);
    layout_header->setMargin(indent_medium);
    setLayout(layout_header);
    setData(_data);
}

void BaseProfileHeader::setData(BaseProfileData _data)
{
    using namespace GlobalData;
    photo_Change(_data.photo.scaled(interface::photo_size, interface::photo_size, Qt::KeepAspectRatioByExpanding));
    //photo_Change(QPixmap(directory::image + "photo.jpg").scaled(interface::photo_size, interface::photo_size));
    surname_Change(_data.surname);
    name_Change(_data.name);
    patronymic_Change(_data.patronymic);
}

void BaseProfileHeader::photo_Change(QPixmap _photo)
{
    using namespace GlobalData::interface;
    using namespace GlobalData;
    if(_photo.isNull())
        _photo.load(directory::image + ((currentMode == Mode_Doctor) ? directory::images::doctor : directory::images::patient));
    my_photo->setPixmap(_photo.scaled(photo_size, photo_size, Qt::KeepAspectRatioByExpanding));
}

void BaseProfileHeader::name_Change(QString _name)
{
    my_name->setText(_name);
}

void BaseProfileHeader::surname_Change(QString _surname)
{
    my_surname->setText(_surname);
}

void BaseProfileHeader::patronymic_Change(QString _patronymic)
{
    my_patronymic->setText(_patronymic);
}


BaseProfileInfo::BaseProfileInfo(BaseProfile* _object, BaseProfileData _data, QWidget* parent, GlobalData::OutputType _outputType) : Widget(parent)
{
    using namespace GlobalData::interface;
    using namespace GlobalData;

    my_object = _object;
    my_outputType = _outputType;
    my_age = new QLabel(this);
    my_email = new QLabel(this);
    my_phone = new QLabel(this);
    my_age_header = new QLabel("Возраст:", this);
    my_email_header = new QLabel("Эл. почта:", this);
    my_phone_header = new QLabel("Телефон:", this);

    my_age->setFixedSize(screen::geometry.width() * 0.6, interface::row_size);
    setTextSize(my_age, text_size);
    my_email->setFixedSize(screen::geometry.width() * 0.6, interface::row_size);
    setTextSize(my_email, text_size);
    my_phone->setFixedSize(screen::geometry.width() * 0.6, interface::row_size);
    setTextSize(my_phone, text_size);
    setTextSize(my_age_header, text_size);
    setTextSize(my_email_header, text_size);
    setTextSize(my_phone_header, text_size);
    setFixedWidth(screen::geometry.width() - indent * 2);

    QGridLayout* layout_list = new QGridLayout();

    // Список
    int i = 0;
    layout_list->addWidget(my_age_header, i, 0);
    layout_list->addWidget(my_age, i, 1, 1, 2);
    i++;

    if(my_outputType == GlobalData::Output_Owner)
    {
        layout_list->addWidget(my_email_header, i, 0);
        layout_list->addWidget(my_email, i, 1, 1, 2);
        i++;

        layout_list->addWidget(my_phone_header, i, 0);
        layout_list->addWidget(my_phone, i, 1, 1, 2);
        i++;
    }
    else
    {
        my_email_header->move(-1000, -1000);
        my_email->move(-1000, -1000);
        my_phone_header->move(-1000, -1000);
        my_phone->move(-1000, -1000);
    }
    layout_list->setSizeConstraint(QLayout::SetMinAndMaxSize);
    layout_list->setMargin(0);
    layout_list->setSpacing(spacing);
    setLayout(layout_list);
    setData(_data);
}

void BaseProfileInfo::setData(BaseProfileData _data)
{
    int age = QDate::currentDate().year() - _data.birthday.year();
    if(QDate::currentDate().month() < _data.birthday.month())
        age--;

    age_Change(age);
    email_Change(_data.email);
    phone_Change(_data.phone);
}

void BaseProfileInfo::age_Change(int _age)
{
    if(_age == 0)
    {
        my_age_header->hide();
        my_age->hide();
    }
    my_age->setText(QString::number(_age) + " лет");
    if(my_age_header->isHidden())
        my_age_header->show();
    if(my_age->isHidden())
        my_age->show();
}

void BaseProfileInfo::email_Change(QString _email)
{
    if(_email == "")
    {
        my_email_header->hide();
        my_email->hide();
    }
    my_email->setText(_email);
    if(my_email_header->isHidden())
        my_email_header->show();
    if(my_email->isHidden())
        my_email->show();
}

void BaseProfileInfo::phone_Change(QString _phone)
{
    if(_phone == "")
    {
        my_phone_header->hide();
        my_phone->hide();
    }
    for(int i = 0; i < _phone.size(); i++)
    {
        if( i > 4 && i < 11 )
            _phone[_phone.size() - i] = '*';
    }
    _phone.insert(_phone.size() - 10, ' ');
    _phone.insert(_phone.size() - 7, ' ');
    _phone.insert(_phone.size() - 4, ' ');
    _phone.insert(_phone.size() - 2, ' ');
            if(my_phone_header->isHidden())
                my_phone_header->show();
            if(my_phone->isHidden())
                my_phone->show();
    my_phone->setText(_phone);
    if(my_phone_header->isHidden())
        my_phone_header->show();
    if(my_phone->isHidden())
        my_phone->show();
}
