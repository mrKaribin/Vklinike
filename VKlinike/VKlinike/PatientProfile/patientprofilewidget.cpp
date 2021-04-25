#include "patientprofilewidget.h"
#include "PatientProfile/patientprofile.h"


PPW_FullServicePackage::PPW_FullServicePackage(PatientProfileSubscriptions* parent, FinalServicePackage data, GlobalData::OutputType _outputType) : Widget(parent)
{
    //ИНИЦИАЛИЗАЦИЯ ПЕРЕМЕННЫХ
        int minutes_total = data.consultationTime / 60,
            spacing = GlobalData::interface::spacing * 0.7;
        my_cost                  = new QLabel();
        my_consultationBalance   = new QLabel();
        my_specialization        = new QLabel();
        my_timeBalance           = new QLabel();
        QLabel* icon1            = new QLabel();
        QLabel* icon2            = new QLabel();
        QHBoxLayout* layout_body = new QHBoxLayout();
        QVBoxLayout* layout      = new QVBoxLayout();
    //------------------------
    //ЗАПОЛНЕНИЕ ДАННЫМИ
        using namespace GlobalData;
        my_consultationBalance->setText(QString::number(minutes_total) + " мин");
        my_specialization->setText(data.specialization);
        timeBalance_Change(data.finishTimepoint.date(), data.finishTimepoint.time());
        my_cost->setText(QString::number(data.cost) + " " + data.valuta.abbreviation + " / " + strings::subscriptionTypeDurations.find(data.subscriptionType).value());
        icon1->setPixmap(QPixmap(GlobalData::directory::icon + "clock.png").scaled(interface::text_size, interface::text_size));
        icon2->setPixmap(QPixmap(GlobalData::directory::icon + "money.png").scaled(interface::text_size, interface::text_size));
    //------------------------
    //НАСТРОЙКИ ФОРМАТИРОВАНИЯ
        my_specialization->setAlignment(Qt::AlignCenter);
        my_specialization->setFixedHeight(interface::row_size);
        setTextSize(my_specialization, interface::text_size);
        my_timeBalance->setAlignment(Qt::AlignCenter);
        my_timeBalance->setFixedHeight(interface::row_size);
        setTextSize(my_timeBalance, interface::text_size);
        my_consultationBalance->setAlignment(Qt::AlignLeft);
        my_consultationBalance->setFixedHeight(interface::row_size);
        setTextSize(my_consultationBalance, interface::text_size);
        my_cost->setAlignment(Qt::AlignRight);
        my_cost->setFixedHeight(interface::row_size);
        setTextSize(my_cost, interface::text_size);
        icon1->setFixedSize(interface::text_size, interface::text_size);
        icon2->setFixedSize(interface::text_size, interface::text_size);
    //------------------------
    //ФОРМИРОВАНИЕ LAYOUT
        layout_body->addWidget(icon1);
        layout_body->addWidget(my_consultationBalance);
        layout_body->addStretch(0);
        layout_body->addWidget(icon2);
        layout_body->addWidget(my_cost);
        layout_body->setMargin(0);
        layout_body->setSpacing(10);
        layout->addWidget(my_specialization);
        layout->addWidget(my_timeBalance);
        layout->addLayout(layout_body);
        layout->setMargin(interface::indent);
        layout->setSpacing(spacing);
    //------------------------

    setLayout(layout);
    setColor(QPalette::Window, GlobalData::interface::color::lightBlue);
    setFrame(true, Frame_Rounded, 4, GlobalData::interface::color::blue);
    //setFixedSize(screen::geometry.width() - interface::indent * 4, interface::row_size * 3 + interface::indent * 2 + interface::spacing * 2);
    setFixedWidth(screen::geometry.width() - interface::indent * 4);
}

void PPW_FullServicePackage::timeBalance_Change(QDate finishData, QTime finishTime)
{
    QString res = "";
    int i = 2;

    //finishData = QDate(finishData.year() - QDate::currentDate().year(), finishData.month() - QDate::currentDate().month(), finishData.day() - QDate::currentDate().day());
    //finishTime = QTime(finishTime.hour() - QTime::currentTime().hour(), finishTime.minute() - QTime::currentTime().minute(), finishTime.second() - QTime::currentTime().second());

    if(finishData.year() != 0 && finishData.year() != 2000)
    {
        int num = finishData.year();
        res += QString::number(num) + ((num == 1) ? (" год ") : ((num < 5) ? (" года ") : (" лет ")));
        i--;
    }
    if(i > 0 && finishData.month() != 0 && finishData.month() != 1)
    {
        int num = finishData.month();
        res += QString::number(num) + ((num == 1) ? (" месяц ") : ((num < 5) ? (" месяца ") : (" месяцев ")));
        i--;
    }
    if(i > 0 && finishData.day() != 0)
    {
        int num = finishData.day();
        res += QString::number(num) + ((num == 1) ? (" день ") : ((num < 5) ? (" дня ") : (" дней ")));
        i--;
    }
    if(i > 0 && finishTime.hour() != 0)
    {
        int num = finishTime.hour();
        res += QString::number(num) + ((num == 1) ? (" час ") : ((num < 5) ? (" часа ") : (" часов ")));
        i--;
    }
    if(i > 0 && finishTime.minute() != 0)
    {
        int num = finishTime.minute();
        res += QString::number(num) + ((num == 1) ? (" минута ") : ((num < 5) ? (" минуты ") : (" минут ")));
        i--;
    }
    if(i > 0 && finishTime.second() != 0)
    {
        int num = finishTime.second();
        res += QString::number(num) + ((num == 1) ? (" секунда ") : ((num < 5) ? (" секунды ") : (" секунд ")));
        i--;
    }

    my_timeBalance->setText("Осталось: " + res);
}


PatientProfileSubscriptions::PatientProfileSubscriptions(PatientProfile* _object, PatientProfileData _data, QWidget* parent, GlobalData::OutputType _outputType) : Widget(parent)
{
    using namespace GlobalData;
    my_outputType = _outputType;
    layout = new QVBoxLayout(this);

    if(_outputType == Output_Owner)
    layout->setMargin(0);
    layout->setSpacing(interface::spacing);

    setLayout(layout);
    setFixedWidth(screen::geometry.width() - interface::indent * 2);
    setData(_data);
}

void PatientProfileSubscriptions::setData(PatientProfileData _data)
{
    my_data = _data;
    while(QLayoutItem *item = layout->itemAt(0))
    {
        layout->removeItem(item);
        layout->removeWidget(item->widget());
        item->widget()->deleteLater();
        delete (item);
    }

    for(int i = 0; i < _data.packages.size(); i++)
    {
        PPW_FullServicePackage* _new_package = new PPW_FullServicePackage(this, _data.packages[i], my_outputType);
        my_packages << _new_package;
        layout->addWidget(_new_package);
    }
}
