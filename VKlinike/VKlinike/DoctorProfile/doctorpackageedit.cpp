#include "doctorpackageedit.h"
#include "doctorprofile.h"
#include "viewer.h"


DPL_Package::DPL_Package(SubscriptionData _data)
{
    using namespace GlobalData;
    using namespace GlobalData::directory;
    my_data = _data;

    lay_main = new QHBoxLayout();
    lay_header = new QVBoxLayout();
    lay_body = new QGridLayout();
    wgt_specialization = new QLabel();
    wgt_type = new QLabel();
    wgt_time = new QLabel();
    wgt_cost = new QLabel();
    wgt_cost_icon = new QLabel();
    wgt_time_icon = new QLabel();
    wgt_remove = new Button();

    formating_label(wgt_specialization);
    formating_label(wgt_type);
    formating_label(wgt_time);
    formating_label(wgt_cost);

    wgt_cost_icon->setFixedSize(interface::row_size, interface::row_size);
    wgt_cost_icon->setPixmap(QPixmap(icon + icons::clock).scaled(interface::row_size, interface::row_size));
    wgt_time_icon->setFixedSize(interface::row_size, interface::row_size);
    wgt_time_icon->setPixmap(QPixmap(icon + icons::money).scaled(interface::row_size, interface::row_size));

    wgt_remove->setFixedSize(interface::row_size * 2 + interface::indent, interface::row_size * 2 + interface::indent);
    wgt_remove->setPixmap(QPixmap(icon + icons::cross).scaled(interface::row_size * 1.5, interface::row_size * 1.5));
    Widget::setTextSize(wgt_remove, interface::text_size);
    setFixedSize(screen::geometry.width() - interface::indent * 2, interface::row_size * 4 + interface::indent * 3);
    setFrame(true, GlobalData::Frame_Rounded, 3, interface::color::blue);

    wgt_specialization->setText(my_data.specialization_name);
    wgt_type->setText(my_data.type_name);
    wgt_time->setText(QString::number(my_data.time));
    wgt_cost->setText(QString::number(my_data.cost) + " " + my_data.valuta.abbreviation);

    lay_header->addWidget(wgt_specialization);
    lay_header->addWidget(wgt_type);
    lay_header->setMargin(0);
    lay_header->setSpacing(interface::indent);
    lay_body->addWidget(wgt_cost_icon, 0, 0);
    lay_body->addWidget(wgt_cost, 0, 1);
    lay_body->addWidget(wgt_time_icon, 1, 0);
    lay_body->addWidget(wgt_time, 1, 1);
    lay_body->setMargin(0);
    lay_body->setSpacing(interface::indent);
    lay_main->addLayout(lay_header);
    lay_main->addStretch(0);
    lay_main->addLayout(lay_body);
    lay_main->addWidget(wgt_remove);
    lay_main->setMargin(interface::indent);
    lay_main->setSpacing(interface::indent);
    setLayout(lay_main);

    connect(this, &DPL_Package::clicked, this, &DPL_Package::edit);
    connect(wgt_remove, &Button::clicked, this, &DPL_Package::remove);
}

void DPL_Package::formating_label(QLabel *label)
{
    using namespace GlobalData::interface;
    label->setFixedHeight(row_size);
    Widget::setTextSize(label, text_size);
}

void DPL_Package::edit()
{
    emit edited(my_data.specialization_id, my_data.group_id, my_data.package_id);
}

void DPL_Package::remove()
{
    emit removed(my_data.specialization_id, my_data.group_id, my_data.package_id);
}


DoctorPackageList::DoctorPackageList(DoctorProfile *_object, Widget *_parent) : Widget(_parent)
{
    using namespace GlobalData;
    my_object = _object;
    lay_main = new QVBoxLayout();
    lay_packages = new QVBoxLayout();
    wgt_create = new Button("Добавить");

    wgt_create->setFixedSize(screen::geometry.width() - interface::indent * 2, interface::row_size * 1.5);
    wgt_create->setFrame(true, GlobalData::Frame_Rounded, 3, interface::color::blue);
    setMinimumSize(screen::geometry.width(), screen::geometry.height() * 0.9);

    lay_packages->setMargin(0);
    lay_packages->setSpacing(interface::spacing);
    lay_main->addLayout(lay_packages);
    lay_main->addWidget(wgt_create);
    lay_main->setMargin(interface::indent);
    lay_main->setSpacing(interface::spacing);
    lay_main->setSizeConstraint(QLayout::SetMinAndMaxSize);
    setLayout(lay_main);

    if(_parent == nullptr)
    {
        Viewer *viewer = new Viewer(this);
    }

    connect(wgt_create, &Button::clicked, this, &DoctorPackageList::package_create);
    connect(this, &DoctorPackageList::remove_package, my_object, &DoctorProfile::package_remove);
    connect(_object, &DoctorProfile::updateAllDoctor, this, &DoctorPackageList::setDatas);
    connect(_object, &DoctorProfile::updateSpecializations, this, &DoctorPackageList::setSpecializations);
}

void DoctorPackageList::setDatas(DoctorProfileData _data)
{
    my_data = _data;

    while(QLayoutItem *item = lay_packages->itemAt(0))
    {
        lay_packages->removeItem(item);
        lay_packages->removeWidget(item->widget());
        item->widget()->deleteLater();
        delete (item);
    }

    foreach(auto spec, _data.specializations)
        foreach(auto group, spec.groups)
            foreach(auto package, group.packages)
            {
                SubscriptionData new_data;
                new_data.setSpecializations(spec);
                new_data.setGroup(group);
                new_data.setPackage(package);
                DPL_Package *new_package = new DPL_Package(new_data);
                lay_packages->addWidget(new_package);
                connect(new_package, &DPL_Package::edited, this, &DoctorPackageList::package_edit);
                connect(new_package, &DPL_Package::removed, this, &DoctorPackageList::package_remove);
            }
    lay_packages->update();
}

void DoctorPackageList::setSpecializations(QList <SpecializationData> _specs)
{
    my_specs = _specs;
}

void DoctorPackageList::package_edit(int spec_id, int group_id, int package_id)
{
    SubscriptionData new_data(my_data, spec_id, group_id, package_id);
    DoctorPackageEdit *new_edit = new DoctorPackageEdit(my_object, new_data, my_specs);
}

void DoctorPackageList::package_remove(int spec_id, int group_id, int package_id)
{
    emit remove_package(spec_id, group_id, package_id);
    foreach(auto spec, my_data.specializations)
        foreach(auto group, spec.groups)
            for(int i = 0; i < group.packages.size(); i++)
                if(spec_id == spec.id && group_id == group.id && package_id == group.packages[i].id)
                    group.packages.remove(i);
    setDatas(my_data);
}

void DoctorPackageList::package_create()
{
    SubscriptionData new_data;
    DoctorPackageEdit *new_edit = new DoctorPackageEdit(my_object, new_data, my_specs);
}


DoctorPackageEdit::DoctorPackageEdit(DoctorProfile *_object, SubscriptionData _data, QList <SpecializationData> _specs)
{
    my_object = _object;
    my_data = _data;
    my_specs = _specs;
    initializing();
    formating();
    filling();
    linking();
    Viewer *viewer = new Viewer(this);

    connect(this, &DoctorPackageEdit::returned, viewer, &Viewer::back);
    connect(this, &DoctorPackageEdit::saved, my_object, &DoctorProfile::package_save);
    connect(this, &DoctorPackageEdit::created, my_object, &DoctorProfile::package_create);
}

void DoctorPackageEdit::initializing()
{
    using namespace GlobalData;
    lay_main = new QVBoxLayout();
    lay_body = new QGridLayout();

    wgt_specializations = new QComboBox();
    wgt_specializations_header = new QLabel("Специализация:");
    wgt_type = new QComboBox();
    wgt_type_header = new QLabel("Длительность:");
    wgt_time = new QLineEdit();
    wgt_time_header = new QLabel("Время видеосвязи:");
    wgt_cost = new QLineEdit();
    wgt_cost_header = new QLabel("Стоимость");
    wgt_valuta = new QComboBox();
    wgt_valuta_header = new QLabel("Валюта платежей");
    wgt_save = new Button("Сохранить");

    margin = interface::indent;
    spacing = interface::spacing;
    size_line = QSize((screen::geometry.width() - margin * 2) / 2, interface::row_size);
    size_button = QSize(screen::geometry.width() - margin * 2, interface::row_size * 1.5);

    connect(wgt_save, &Button::clicked, this, &DoctorPackageEdit::save);
    connect(wgt_time, &QLineEdit::textEdited, this, &DoctorPackageEdit::timeChanged);
    connect(wgt_cost, &QLineEdit::textEdited, this, &DoctorPackageEdit::costChanged);
}

void DoctorPackageEdit::formating()
{
    using namespace GlobalData;
    formating_line(wgt_specializations, wgt_specializations_header);
    formating_line(wgt_type, wgt_type_header);
    formating_line(wgt_time, wgt_time_header);
    formating_line(wgt_cost, wgt_cost_header);
    formating_line(wgt_valuta, wgt_valuta_header);
    wgt_save->setFixedSize(size_button);
    Widget::setTextSize(wgt_save, text_size);
    wgt_save->setFrame(true, Frame_Rounded, 3, interface::color::blue);
}

void DoctorPackageEdit::formating_line(QWidget *wgt, QLabel *header)
{
    wgt->setFixedSize(size_line);
    Widget::setTextSize(wgt, text_size);

    header->setFixedSize(size_line);
    Widget::setTextSize(header, text_size);
}

void DoctorPackageEdit::filling()
{
    foreach(auto specialization, my_specs)
        wgt_specializations->addItem(specialization.name);
    if(my_specs.size() != 0)
        wgt_specializations->setCurrentText(my_data.specialization_name);

    foreach(auto type, GlobalData::strings::subscriptionTypeNames.values())
        wgt_type->addItem(type);
    if(GlobalData::strings::subscriptionTypeNames.size() != 0 && my_data.type_name != -1)
        wgt_type->setCurrentText(my_data.type_name);

    foreach(auto valuta, GlobalData::valutes)
        wgt_valuta->addItem(valuta.name);
    if(GlobalData::valutes.size() != 0 && !my_data.valuta.name.isEmpty())
        wgt_valuta->setCurrentText(my_data.valuta.name);

    wgt_time->setText(QString::number(my_data.time));
    wgt_cost->setText(QString::number(my_data.cost));
}

void DoctorPackageEdit::linking()
{
    using namespace GlobalData::interface;
    lay_body->addWidget(wgt_specializations, 0, 1);
    lay_body->addWidget(wgt_specializations_header, 0, 0);
    lay_body->addWidget(wgt_type, 1, 1);
    lay_body->addWidget(wgt_type_header, 1, 0);
    lay_body->addWidget(wgt_time, 2, 1);
    lay_body->addWidget(wgt_time_header, 2, 0);
    lay_body->addWidget(wgt_cost, 3, 1);
    lay_body->addWidget(wgt_cost_header, 3, 0);
    lay_body->addWidget(wgt_valuta, 4, 1);
    lay_body->addWidget(wgt_valuta_header, 4, 0);
    lay_body->setMargin(0);
    lay_body->setSpacing(spacing);
    lay_main->addLayout(lay_body);
    lay_main->addWidget(wgt_save);
    lay_main->setMargin(indent);
    lay_main->setSpacing(spacing);
    setLayout(lay_main);
}

void DoctorPackageEdit::timeChanged(QString time)
{

}

void DoctorPackageEdit::costChanged(QString cost)
{

}

void DoctorPackageEdit::save()
{
    bool create = my_data.specialization_id == -1 ? true : false;
    foreach(auto specialization, my_specs)
        if(specialization.name == wgt_specializations->currentText())
        {
            my_data.specialization_id = specialization.id;
            my_data.specialization_name = specialization.name;
            my_data.specialization_info = specialization.info;
        }
    foreach(auto type_name, GlobalData::strings::subscriptionTypeNames.values())
        if(type_name == wgt_type->currentText())
        {
            my_data.type_name = type_name;
            my_data.type_interval = GlobalData::strings::subscriptionTypeValue.find(GlobalData::strings::subscriptionTypeNames.key(type_name)).value();
        }
    foreach(auto valuta, GlobalData::valutes)
        if(valuta.name == wgt_valuta->currentText())
        {
            my_data.valuta = valuta;
        }

    my_data.time = wgt_time->text().toInt();
    my_data.cost = wgt_cost->text().toInt();

    if(create)
        emit created(my_data);
    else
        emit saved(my_data);
    emit returned();
}
