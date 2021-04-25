#include "doctorprofilewidget.h"
#include "DoctorProfile/doctorprofile.h"
#include "order.h"
#include "viewer.h"


DPW_ServicePackage::DPW_ServicePackage(DPW_ServicePackageGroup* parent, ServicePackage data, GlobalData::OutputType _outputType) : Button(parent)
{
    //ИНИЦИАЛИЗАЦИЯ ПЕРЕМЕННЫХ
        using namespace GlobalData;
        my_data = data;
        int minutes_total = data.consultationTime / 60,
            spacing = 10,
            margin = (interface::row_size * 1.4 - interface::text_size) / 2;
        my_cost                  = new QLabel();
        my_consultationTime      = new QLabel();
        QLabel* icon1            = new QLabel();
        QLabel* icon2            = new QLabel();
        QHBoxLayout* layout      = new QHBoxLayout(this);
    //------------------------
    //ЗАПОЛНЕНИЕ ДАННЫМИ
        my_consultationTime->setText(QString::number(minutes_total) + " мин");
        my_cost->setText(QString::number(data.cost) + " " + data.valuta.abbreviation);
        icon1->setPixmap(QPixmap(GlobalData::directory::icon + "clock.png").scaled(interface::text_size, interface::text_size));
        icon2->setPixmap(QPixmap(GlobalData::directory::icon + "money.png").scaled(interface::text_size, interface::text_size));
    //------------------------
    //НАСТРОЙКИ ФОРМАТИРОВАНИЯ
        my_consultationTime->setAlignment(Qt::AlignLeft | Qt::AlignCenter);
        setTextSize(my_consultationTime, interface::text_size);
        my_cost->setAlignment(Qt::AlignRight | Qt::AlignCenter);
        setTextSize(my_cost, interface::text_size);
        icon1->setFixedSize(interface::text_size , interface::text_size);
        icon2->setFixedSize(interface::text_size , interface::text_size);
    //------------------------
    //ФОРМИРОВАНИЕ LAYOUT
        layout->addWidget(icon1);
        layout->addWidget(my_consultationTime);
        layout->addStretch(0);
        layout->addWidget(icon2);
        layout->addWidget(my_cost);
        layout->setContentsMargins(interface::indent, margin, interface::indent, margin);
        layout->setSpacing(spacing);
    //------------------------

    setLayout(layout);
    if(_outputType == GlobalData::Output_Owner)
    {
        setColor(QPalette::Window, GlobalData::interface::color::lightBlue);
        setFrame(true, Frame_Rounded, 4, GlobalData::interface::color::blue);
    }
    else
    {
        setColor(QPalette::Window, GlobalData::interface::color::lightRed);
        setColor(QPalette::WindowText, Qt::black);
        setFrame(true, Frame_Rounded, 4, GlobalData::interface::color::red);
    }
    setFixedSize(screen::geometry.width() * 0.6, interface::row_size * 2);
    if(GlobalData::currentMode == Mode_Patient)
        connect(this, &DPW_ServicePackage::clicked, this, &DPW_ServicePackage::buy);
}

void DPW_ServicePackage::buy()
{
    OrderData data;
    data.package_id = my_data.id;
    data.group_id = ((DPW_ServicePackageGroup*)parent())->my_data.id;
    data.spec_id = ((DPW_Specialization*)((DPW_ServicePackageGroup*)parent())->parent())->my_data.id;
    data.email = ((DoctorProfileSubscriptions*)((DPW_Specialization*)((DPW_ServicePackageGroup*)parent())->parent())->parent())->my_data.base.email;
    data.name = ((DoctorProfileSubscriptions*)((DPW_Specialization*)((DPW_ServicePackageGroup*)parent())->parent())->parent())->my_data.base.name;
    data.surname = ((DoctorProfileSubscriptions*)((DPW_Specialization*)((DPW_ServicePackageGroup*)parent())->parent())->parent())->my_data.base.surname;
    data.patronimic = ((DoctorProfileSubscriptions*)((DPW_Specialization*)((DPW_ServicePackageGroup*)parent())->parent())->parent())->my_data.base.patronymic;
    data.specialization = ((DPW_Specialization*)((DPW_ServicePackageGroup*)parent())->parent())->my_data.name;
    data.duration = GlobalData::strings::subscriptionTypeDurations.find(((DPW_ServicePackageGroup*)parent())->my_data.subscriptionType).value();
    data.time = my_data.consultationTime;
    data.cost = my_data.cost;
    data.valuta = my_data.valuta;
    Order *order = new Order(data);
}


DPW_ServicePackageGroup::DPW_ServicePackageGroup(DPW_Specialization* parent, ServicePackageGroup data, GlobalData::OutputType _outputType) : Widget(parent)
{
    //ИНИЦИАЛИЗАЦИЯ ПЕРЕМЕННЫХ
        using namespace GlobalData;
        using namespace GlobalData::interface;
        my_data = data;
        my_interval = new QLabel(this);
        QGridLayout* layout = new QGridLayout();
    //------------------------
    //ЗАПОЛНЕНИЕ ДАННЫМИ
        my_interval->setText(GlobalData::strings::subscriptionTypeNames.find(data.subscriptionType).value());
    //------------------------
    //НАСТРОЙКИ ФОРМАТИРОВАНИЯ
        my_interval->setFixedSize(screen::geometry.width() / 4, interface::row_size * 2);
        my_interval->setAlignment(Qt::AlignLeft);
        setTextSize(my_interval, interface::text_size);
    //------------------------
    //ФОРМИРОВАНИЕ LAYOUT
        int i = 0;
        for(; i < data.packages.size(); i++)
        {
            DPW_ServicePackage* _new_package = new DPW_ServicePackage(this, data.packages[i], _outputType);
            my_packages << _new_package;
            layout->addWidget(_new_package, i, 1, 1, 1);
        }
        layout->addWidget(my_interval, 0, 0, i + 1, 1);
        layout->setMargin(0);
        layout->setSpacing(indent);
        layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    //------------------------

    setLayout(layout);
    setColor(QPalette::Window, GlobalData::interface::color::lightBlue);
    setFixedWidth(screen::geometry.width() - indent * 4);
}


DPW_Specialization::DPW_Specialization(DoctorProfileSubscriptions* parent, Specialization data, GlobalData::OutputType _outputType) : Widget(parent)
{
    //ИНИЦИАЛИЗАЦИЯ ПЕРЕМЕННЫХ
        using namespace GlobalData;
        using namespace GlobalData::interface;
        my_data = data;
        my_name = new QLabel();
        QVBoxLayout* layout = new QVBoxLayout();
    //------------------------
    //ЗАПОЛНЕНИЕ ДАННЫМИ
        my_name->setText(data.name);
    //------------------------
    //НАСТРОЙКИ ФОРМАТИРОВАНИЯ
        my_name->setFixedWidth(screen::geometry.width() - interface::indent * 2);
        my_name->setAlignment(Qt::AlignCenter);
        setTextSize(my_name, interface::text_size);
    //------------------------
    //ФОРМИРОВАНИЕ LAYOUT
        layout->addWidget(my_name);
        for(int i = 0; i < data.groups.size(); i++)
        {
            DPW_ServicePackageGroup* _new_group = new DPW_ServicePackageGroup(this, data.groups[i], _outputType);
            my_groups << _new_group;
            layout->addWidget(_new_group);
        }
        layout->setMargin(indent);
        layout->setSpacing(indent * 2);
        layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    //------------------------

    setLayout(layout);
    setColor(QPalette::Window, GlobalData::interface::color::lightBlue);
    setFrame(true, Frame_Rounded, 4, GlobalData::interface::color::blue);
    setFixedWidth(screen::geometry.width() - indent * 2);
}


DoctorProfileSubscriptions::DoctorProfileSubscriptions(DoctorProfile* _object, DoctorProfileData _data, QWidget* parent, GlobalData::OutputType _outputType) : Widget(parent)
{
    using namespace GlobalData;
    using namespace GlobalData::interface;
    my_data = _data;
    my_object = _object;
    my_outputType = _outputType;
    if(_outputType == GlobalData::Output_Owner)
        wgt_edit = _object->widget_subscriptions_edit(_object);
    layout = new QVBoxLayout();
    layout_specs = new QVBoxLayout();

    setFixedWidth(screen::geometry.width() - indent * 2);

    layout_specs->setMargin(0);
    layout_specs->setSpacing(spacing);
    if(_outputType == GlobalData::Output_Owner)
        layout->addWidget(wgt_edit);
    layout->addLayout(layout_specs);
    layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    layout->setMargin(0);
    layout->setSpacing(spacing);

    setLayout(layout);
    setData(_data);
}

void DoctorProfileSubscriptions::setData(DoctorProfileData _data)
{
    using namespace GlobalData::interface;

    my_data = _data;
    while(QLayoutItem *item = layout_specs->itemAt(0))
    {
        layout_specs->removeItem(item);
        layout_specs->removeWidget(item->widget());
        item->widget()->deleteLater();
        delete (item);
    }

    int size = 0;
    for(int i = 0; i < _data.specializations.size(); i++)
    {
        DPW_Specialization* _new_spec = new DPW_Specialization(this, _data.specializations[i], my_outputType);
        my_specializations << _new_spec;
        layout_specs->addWidget(_new_spec);

        size += _new_spec->height();
        if(i > 0)
            size += spacing;
    }
    layout_specs->update();
    layout->update();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DPC_Comment::DPC_Comment(DoctorProfileComments* _parent, Comment _data, GlobalData::OutputType _outputType)
{
    using namespace GlobalData;
    using namespace GlobalData::interface;
    using namespace GlobalData::directory;
    int message_width = screen::geometry.width() - indent * 4,
        message_height = 0,
        message_shortHeight = 0;
    Widget* scroll_box = new Widget(this);
    Widget* wgt = new Widget(scroll_box);
    header = new QLabel();
    message = new QLabel(wgt);
    QHBoxLayout* layout_stars = new QHBoxLayout();
    QVBoxLayout* layout = new QVBoxLayout();

    header->setText(_data.name);
    message->setText(_data.message);

    QFontMetrics fm(message->font());
    message_height = (fm.horizontalAdvance(_data.message) / message_width) * row_size;
    if(message_height == 0)
        message_height = row_size;
    if(message_height >= row_size * 3)
        message_shortHeight = row_size * 3;
    else
        message_shortHeight = message_height;

    setTextSize(header, text_size);
    setTextSize(message, text_size * 0.8);
    setFixedWidth(screen::geometry.width() - indent * 2);
    scroll_box->setFixedSize(message_width, message_shortHeight);
    message->setWordWrap(true);
    message->setFixedWidth(message_width);
    message->move(0, 0);
    wgt->move(0, 0);
    if(message_height != message_shortHeight)
        wgt->setMovable_vertical(true);
    wgt->setFixedSize(message_width, message_height);
    wgt->setMoveableBorder(0, 0, scroll_box->width(), scroll_box->height());
    setFrame(true, Frame_Rectangle, 2, color::blue);

    layout->addWidget(header);
    for(int i = 0; i < 5; i++)
    {
        star[i] = new QLabel();
        star[i]->setFixedSize(text_size, text_size);
        if(_data.mark >= i + 1)
            star[i]->setPixmap(QPixmap(icon + icons::gold_star).scaled(text_size, text_size));
        else
            star[i]->setPixmap(QPixmap(icon + icons::star).scaled(text_size, text_size));
        layout_stars->addWidget(star[i]);
    }
    layout_stars->addStretch(0);
    layout_stars->setMargin(0);
    layout_stars->setSpacing(10);
    layout->addLayout(layout_stars);
    layout->addWidget(scroll_box);
    layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    layout->setMargin(indent);
    layout->setSpacing(indent);
    setLayout(layout);
}

DoctorProfileComments::DoctorProfileComments(DoctorProfile* _object, DoctorProfileData _data, QWidget* parent, GlobalData::OutputType _outputType)
{
    using namespace GlobalData;
    using namespace GlobalData::interface;
    using namespace GlobalData::directory;
    my_object = _object;
    my_outputType = _outputType;

    int resMark = 0;
    averageMark = new QLabel();
    QLabel* star_icon = new QLabel();
    QVBoxLayout* layout = new QVBoxLayout();
    QHBoxLayout* layout_header = new QHBoxLayout();
    layout_comments = new QVBoxLayout();

    for(int i = 0; i < _data.comments.size(); i++)
        resMark += _data.comments[i].mark;
    averageMark->setText("Средний ретинг: " + QString::number(((double)resMark / _data.comments.size() * 10) / 10));
    star_icon->setPixmap(QPixmap(icon + icons::gold_star).scaled(text_size, text_size));

    setTextSize(averageMark, text_size);
    setFixedWidth(screen::geometry.width() - indent * 2);

    layout_header->setAlignment(Qt::AlignHCenter);
    layout_header->addWidget(averageMark);
    layout_header->addWidget(star_icon);
    layout_header->setSpacing(10);
    layout_header->setMargin(0);
    layout->setAlignment(Qt::AlignLeft);
    layout->addLayout(layout_header);
    layout_comments->setMargin(0);
    layout_comments->setSpacing(spacing);
    layout->addLayout(layout_comments);
    layout->addStretch(0);
    layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    layout->setMargin(0);
    layout->setSpacing(spacing);
    setLayout(layout);
    setData(_data);
}

void DoctorProfileComments::setData(DoctorProfileData _data)
{
    using namespace GlobalData::interface;

    while(QLayoutItem *item = layout_comments->itemAt(0))
    {
        layout_comments->removeItem(item);
        layout_comments->removeWidget(item->widget());
        item->widget()->deleteLater();
        delete (item);
    }

    if(!_data.comments.isEmpty())
    {
        int resMark = 0;
        for(int i = 0; i < _data.comments.size(); i++)
            resMark += _data.comments[i].mark;
        averageMark->setText("Средний ретинг: " + QString::number(((resMark / _data.comments.size() * 10) / 10)));
    }
    else
    {
        averageMark->setText("Нет отзывов - нет рейтинга");
    }

    for(int i = 0; i < _data.comments.size(); i++)
    {
        DPC_Comment* new_achieve = new DPC_Comment(this, _data.comments[i], my_outputType);
        comments << new_achieve;
        layout_comments->addWidget(new_achieve);
    }
    layout_comments->update();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DPA_Achievement::DPA_Achievement(DoctorProfileAchievements* _parent, Achievement _data, GlobalData::OutputType _outputType)
{
    using namespace GlobalData;
    using namespace GlobalData::interface;
    int lenth = screen::geometry.width() / 5;
    header = new QLabel();
    message = new QLabel();
    QVBoxLayout* layout = new QVBoxLayout();

    setTextSize(header, text_size * 0.8);
    header->setAlignment(Qt::AlignCenter);
    header->setFixedHeight(lenth / 2 - spacing / 4);
    setTextSize(message, text_size * 0.6);
    setColor(message, QPalette::WindowText, Qt::gray);
    message->setWordWrap(true);
    message->setAlignment(Qt::AlignCenter);
    message->setFixedHeight(lenth / 2 - spacing / 4);
    setFixedSize(lenth, lenth);

    if(_data.header != "")
        header->setText(_data.header);
    else
        header->setPixmap(_data.header_icon.scaled(lenth / 3, lenth / 3));
    message->setText(_data.comment);

    layout->setAlignment(Qt::AlignHCenter);
    layout->addWidget(header);
    layout->addWidget(message);
    layout->setContentsMargins(0, spacing / 2, 0, spacing / 2);
    layout->setSpacing(0);
    setLayout(layout);
}


DoctorProfileAchievements::DoctorProfileAchievements(DoctorProfile* _object, DoctorProfileData _data, QWidget* parent, GlobalData::OutputType _outputType) : Widget()
{
    using namespace GlobalData;
    using namespace GlobalData::interface;
    my_object = _object;
    my_outputType = _outputType;

    int lenth = screen::geometry.width() / 5;
    Widget* wgt = new Widget(this);
    layout = new QHBoxLayout();

    setFixedSize(screen::geometry.width() - indent * 2, lenth);
    wgt->setMinimumSize(screen::geometry.width() - indent * 4, lenth);
    wgt->setMoveableBorder(0, 0, screen::geometry.width() - indent * 4, lenth);
    wgt->setMovable_horizontal(true);

    layout->addStretch(spacing);
    layout->setContentsMargins(spacing, 0, spacing, 0);
    layout->setSpacing(spacing);
    wgt->setLayout(layout);
    wgt->move(0, 0);
    setData(_data);
}

void DoctorProfileAchievements::setData(DoctorProfileData _data)
{
    using namespace GlobalData::interface;

    while(QLayoutItem *item = layout->itemAt(0))
    {
        layout->removeItem(item);
        layout->removeWidget(item->widget());
        item->widget()->deleteLater();
        delete (item);
    }

    for(int i = 0; i < _data.achievements.size(); i++)
    {
        DPA_Achievement* new_achieve = new DPA_Achievement(this, _data.achievements[i], my_outputType);
        achievements << new_achieve;
        layout->addWidget(new_achieve);
        layout->addStretch(spacing);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DoctorProfileInfo::DoctorProfileInfo(DoctorProfile* _object, DoctorProfileData _data, QWidget* parent, GlobalData::OutputType _outputType) : Widget()
{
    using namespace GlobalData;
    QLabel* lbl1 = new QLabel("Время работы:");
    QLabel* lbl2 = new QLabel("Время ответа:");
    QLabel* lbl3 = new QLabel("Образование:");
    QLabel* lbl4 = new QLabel("Место работы:");
    my_workTime = new QLabel(this);
    my_replyInterval = new QLabel(this);
    my_education = new QLabel(this);
    my_job = new QLabel(this);
    QGridLayout* layout = new QGridLayout(this);

    setTextSize(lbl1, interface::text_size);
    setTextSize(lbl2, interface::text_size);
    setTextSize(lbl3, interface::text_size);
    setTextSize(lbl4, interface::text_size);
    setTextSize(my_workTime, interface::text_size);
    setTextSize(my_replyInterval, interface::text_size);
    setTextSize(my_education, interface::text_size);
    setTextSize(my_job, interface::text_size);
    my_workTime->setFixedHeight(interface::row_size);
    my_replyInterval->setFixedHeight(interface::row_size);
    my_education->setFixedHeight(interface::row_size * 2);
    my_job->setFixedHeight(interface::row_size);
    lbl1->setFixedHeight(interface::row_size);
    lbl2->setFixedHeight(interface::row_size);
    lbl3->setFixedHeight(interface::row_size * 2);
    lbl4->setFixedHeight(interface::row_size);
    setFixedWidth(screen::geometry.width() - interface::indent * 2);
    setMinimumHeight(interface::row_size * 4 + interface::spacing * 3);

    layout->addWidget(lbl1, 0, 0);
    layout->addWidget(my_workTime, 0, 1, 1, 2);
    layout->addWidget(lbl2, 1, 0);
    layout->addWidget(my_replyInterval, 1, 1, 1, 2);
    layout->addWidget(lbl3, 2, 0);
    layout->addWidget(my_education, 2, 1, 1, 2);
    layout->addWidget(lbl4, 3, 0);
    layout->addWidget(my_job, 3, 1, 1, 2);
    layout->setMargin(0);
    layout->setSpacing(interface::spacing);
    setLayout(layout);
    setData(_data);
}

void DoctorProfileInfo::setData(DoctorProfileData _data)
{
    my_workTime->setText("с " + _data.workTime_begin.toString().mid(0, 5) +
                         " до " +  _data.workTime_end.toString().mid(0, 5));
    my_replyInterval->setText((_data.replyInterval / 60 > 0) ? (QString::number(_data.replyInterval / 60) + " часов") : (QString("")) + QString::number(_data.replyInterval % 60) + " минут");
    my_education->setText(_data.education);
    my_job->setText(_data.job);
}
