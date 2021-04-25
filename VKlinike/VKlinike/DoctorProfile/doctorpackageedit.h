#ifndef DOCTORPACKAGEEDIT_H
#define DOCTORPACKAGEEDIT_H

#include "widget.h"
#include "DoctorProfile/doctorprofiledata.h"
#include "Search/searchdata.h"
#include "button.h"

#include <QComboBox>
#include <QLineEdit>

class DoctorProfile;


class DPL_Package : public Button
{
    Q_OBJECT
public:
    DPL_Package(SubscriptionData _data);
    void formating_label(QLabel* label);

private:
    SubscriptionData                my_data;

    QHBoxLayout                    *lay_main;
    QVBoxLayout                    *lay_header;
    QGridLayout                    *lay_body;
    QLabel                         *wgt_specialization;
    QLabel                         *wgt_type;
    QLabel                         *wgt_time;
    QLabel                         *wgt_cost;
    QLabel                         *wgt_time_icon;
    QLabel                         *wgt_cost_icon;
    Button                         *wgt_remove;

public slots:
    void                            edit();
    void                            remove();

signals:
    void edited(int spec_id, int group_id, int package_id);
    void removed(int spec_id, int group_id, int package_id);
};


class DoctorPackageList : public Widget
{
    Q_OBJECT
public:
    DoctorPackageList(DoctorProfile *_object,  Widget *_parent = nullptr);

private:
    DoctorProfile                  *my_object;
    DoctorProfileData               my_data;
    QList <SpecializationData>      my_specs;

    QVBoxLayout                    *lay_main;
    QVBoxLayout                    *lay_packages;
    Button                         *wgt_create;

public slots:
    void                            setDatas(DoctorProfileData _data);
    void                            setSpecializations(QList <SpecializationData> _specs);

    void                            package_edit(int spec_id, int group_id, int package_id);
    void                            package_remove(int spec_id, int group_id, int package_id);
    void                            package_create();

signals:
    void remove_package(int spec_id, int group_id, int package_id);

};


class DoctorPackageEdit : public Widget
{
    Q_OBJECT
public:
    DoctorPackageEdit(DoctorProfile *_object, SubscriptionData _data, QList <SpecializationData> _specs);
    void initializing();
    void formating();
    void formating_line(QWidget *line, QLabel *header);
    void filling();
    void linking();

private:
    DoctorProfile                  *my_object;
    SubscriptionData                my_data;
    QList <SpecializationData>      my_specs;

    QVBoxLayout                    *lay_main;
    QGridLayout                    *lay_body;
    QComboBox                      *wgt_specializations;
    QLabel                         *wgt_specializations_header;
    QComboBox                      *wgt_type;
    QLabel                         *wgt_type_header;
    QLineEdit                      *wgt_time;
    QLabel                         *wgt_time_header;
    QLineEdit                      *wgt_cost;
    QLabel                         *wgt_cost_header;
    QComboBox                      *wgt_valuta;
    QLabel                         *wgt_valuta_header;
    Button                         *wgt_save;

    QSize                           size_line;
    QSize                           size_button;
    int                             text_size;
    int                             margin;
    int                             spacing;

public slots:
    void                            timeChanged(QString time);
    void                            costChanged(QString cost);

    void                            save();

signals:
    void created(SubscriptionData);
    void saved(SubscriptionData);
    void returned();
};


#endif // DOCTORPACKAGEEDIT_H
