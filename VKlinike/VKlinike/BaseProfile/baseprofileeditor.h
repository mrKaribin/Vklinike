#ifndef BASEPROFILEEDITOR_H
#define BASEPROFILEEDITOR_H

#include "widget.h"
#include "button.h"
#include "BaseProfile/baseprofiledata.h"

#include <QLineEdit>
#include <QCheckBox>
#include <QLayout>


class BaseProfile;

class BaseProfileEditor : public Widget
{
    Q_OBJECT
public:
    BaseProfileEditor(BaseProfile *_object, BaseProfileData _data, GlobalData::Mode _mode = GlobalData::Mode_Patient, bool _creating = false, QWidget *parent = nullptr);

private:
    void                        initializing();
    void                        formating();
    void                        formating_line(QLineEdit *line);
    void                        formating_status(QLabel *label);
    void                        filling();
    void                        linking();

    BaseProfile                *my_object;
    BaseProfileData             my_data;
    GlobalData::Mode            my_mode;
    QWidget                    *my_parent;
    QPixmap                     my_photo;

    QVBoxLayout                *layout;
    QGridLayout                *layout_photo;
    QHBoxLayout                *layout_sex;
    QLabel                     *wgt_photo;
    Button                     *wgt_photo_edit;
    Button                     *wgt_photo_remove;
    QLabel                     *wgt_photo_status;
    QLineEdit                  *wgt_name;
    QLabel                     *wgt_name_status;
    QLineEdit                  *wgt_surname;
    QLabel                     *wgt_surname_status;
    QLineEdit                  *wgt_patronimic;
    QLabel                     *wgt_patronimic_status;
    QCheckBox                  *wgt_sex_male;
    QCheckBox                  *wgt_sex_female;
    QLabel                     *wgt_sex_status;
    QLineEdit                  *wgt_birthday;
    QLabel                     *wgt_birthday_status;
    QLineEdit                  *wgt_email;
    QLabel                     *wgt_email_status;
    QLineEdit                  *wgt_phone;
    QLabel                     *wgt_phone_status;
    QLineEdit                  *wgt_password;
    QLabel                     *wgt_password_status;
    Button                     *wgt_save;

    int                         margin;
    int                         spacing;
    int                         text_main_size;
    int                         text_status_size;
    QSize                       size_photo;
    QSize                       size_line;
    QSize                       size_status;
    QString                     default_name                = "Иван";
    QString                     default_surname             = "Грозный";
    QString                     default_patronimic          = "Васильевич";
    QString                     default_birthday            = "03.12.1533";
    QString                     default_email               = "ivan.grozniy@yandex.ru";
    QString                     default_phone               = "+7 987 654 32 10";
    bool                        isDefault_name = false;
    bool                        isDefault_surname = false;
    bool                        isDefault_patronimic = false;
    bool                        isDefault_birthday = false;
    bool                        isDefault_email = false;
    bool                        isDefault_phone = false;
    bool                        isDefault_password = false;
    bool                        isCorrect_name;
    bool                        isCorrect_surname;
    bool                        isCorrect_patronimic;
    bool                        isCorrect_birthday;
    bool                        isCorrect_email;
    bool                        isCorrect_phone;
    bool                        isCorrect_poassword;
    bool                        creating;

public slots:
    void save();

    void photoChanged();
    void photoEdit();
    void photoRemove();
    void nameChanged(QString _text);
    void surnameChanged(QString _text);
    void maleChecked(int check);
    void femaleChecked(int check);
    void patronimicChanged(QString _text);
    void birthdayChanged(QString _text);
    void emailChanged(QString _text);
    void phoneChanged(QString _text);
    void passwordChanged(QString _text);

signals:
    void created(BaseProfileData);
    void saved(BaseProfileData);
    void returning();

};

#endif // BASEPROFILEEDITOR_H
