#ifndef BASEPROFILE_H
#define BASEPROFILE_H

#include "BaseProfile/baseprofiledata.h"
#include "BaseProfile/baseprofilewidget.h"
#include "BaseProfile/baseprofileeditor.h"
#include "object.h"

#include <QThread>
#include <QPicture>
#include <QDate>


class BaseProfile : public Object
{
    Q_OBJECT
public:
    BaseProfile(BaseProfileData _data, QWidget *_widget_parent = nullptr, GlobalData::OutputType _outputType = GlobalData::Output_Guest, QThread* _object_thread = nullptr);
    BaseProfile(QString login, QWidget *_widget_parent = nullptr, GlobalData::OutputType _outputType = GlobalData::Output_Guest, QThread* _object_thread = nullptr);
    void BaseProfile_initialize();

    void                    loadingData_base();
    void                    waitForBaseReady();

    BaseProfileHeader              *widget_header();
    BaseProfileInfo                *widget_info();
    Button                         *widget_edit();

private:
    BaseProfileHeader              *my_header;
    BaseProfileInfo                *my_info;
    Button                         *my_editButton;
    BaseProfileData                 my_data_base;

protected:
    QWidget                        *my_widget_parent;
    GlobalData::OutputType          my_outputType;
    QString                         my_login                        = "";
    bool                            my_baseIsReady                  = false;

public slots:
    void                            edit();
    void                            edited(BaseProfileData);
    void                            created(BaseProfileData);

    void                            readFromBytes(QByteArray array, GlobalData::OutputType mode = GlobalData::Output_Owner);
    void                            server_reply(QString header, QByteArray body) override;
    void                            updateWidget(BaseProfileData _new_data);


signals:
    void updateAllBase(BaseProfileData _new_data);

    void photo_change(QPicture* photo);
    void name_change(QString name);
    void surname_change(QString surname);
    void patronymic_change(QString patronymic);
    void email_change(QString email);
    void phone_change(QString phone);

    void editing(BaseProfile*, BaseProfileData);
};


#endif // BASEPROFILE_H
