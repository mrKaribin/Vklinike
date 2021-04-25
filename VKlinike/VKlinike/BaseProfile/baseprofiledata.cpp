#include "baseprofiledata.h"


BaseProfileData::BaseProfileData(BaseProfileData const &_data)
{
    operator=(_data);
}

void BaseProfileData::operator=(const BaseProfileData &data)
{
    photo = data.photo;
    name = data.name;
    surname = data.surname;
    patronymic = data.patronymic;
    sex = data.sex;
    birthday = data.birthday;
    email = data.email;
    phone = data.phone;
    password = data.password;
}
