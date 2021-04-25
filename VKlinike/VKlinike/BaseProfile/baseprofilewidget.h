#ifndef BASEPROFILEWIDGET_H
#define BASEPROFILEWIDGET_H

#include "baseprofiledata.h"
#include "widget.h"

#include <QPushButton>
#include <QLabel>

#include <QApplication>
#include <QBoxLayout>


class BaseProfile;
struct BaseProfileData;


class BaseProfileHeader : public Widget
{
    Q_OBJECT
public:
    BaseProfileHeader(BaseProfile* _object, BaseProfileData _data, QWidget* parent = nullptr, GlobalData::OutputType _outputType = GlobalData::Output_Guest);

private:
    BaseProfile* my_object;
    QLabel* my_photo;
    QLabel* my_name;
    QLabel* my_surname;
    QLabel* my_patronymic;

public slots:
    void photo_Change(QPixmap _photo);
    void name_Change(QString _name);
    void surname_Change(QString _surname);
    void patronymic_Change(QString _patronymic);

    void setData(BaseProfileData _data);
};


class BaseProfileInfo : public Widget
{
    Q_OBJECT
public:
    BaseProfileInfo(BaseProfile* _object, BaseProfileData _data, QWidget* parent = nullptr, GlobalData::OutputType _outputType = GlobalData::Output_Guest);

private:
    BaseProfile* my_object;
    QLabel* my_age;
    QLabel* my_email;
    QLabel* my_phone;
    QLabel* my_age_header;
    QLabel* my_email_header;
    QLabel* my_phone_header;
    GlobalData::OutputType my_outputType;

public slots:
    void age_Change(int _age);
    void email_Change(QString _email);
    void phone_Change(QString _phone);

    void setData(BaseProfileData _data);

signals:


};

#endif // BASEPROFILEWIDGET_H
