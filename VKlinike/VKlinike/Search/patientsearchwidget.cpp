#include "patientsearchwidget.h"
#include "Search/search.h"
#include "mainwidget.h"
#include "viewer.h"


PSW_Doctor::PSW_Doctor(SearchDoctorData _data) : Button()
{
    using namespace GlobalData;
    using namespace GlobalData::directory;
    //ИНИЦИАЛИЗАЦИЯ ПЕРЕМЕННЫХ
        my_data = _data;
        my_size = QSize(screen::geometry.width() - interface::indent * 2, screen::geometry.height() / 8);
        margin = interface::indent;
        spacing = interface::spacing;
        info_spacing = interface::indent;
        text_size = interface::text_size;
        photo_size = my_size.height() - PSW_Doctor::margin * 2;

        photo = new QLabel();
        header = new QLabel();
        raiting = new QLabel();
        raiting_icon = new QLabel();
        QHBoxLayout *layout = new QHBoxLayout();
        QVBoxLayout *layout_info = new QVBoxLayout();
        QHBoxLayout *layout_raiting = new QHBoxLayout();
    //------------------------
    //ЗАПОЛНЕНИЕ ДАННЫМИ
        if(!_data.photo.isNull())
            photo->setPixmap(_data.photo.scaled(photo_size, photo_size, Qt::KeepAspectRatioByExpanding));
        else
            photo->setPixmap(QPixmap(image + images::doctor).scaled(photo_size, photo_size, Qt::KeepAspectRatioByExpanding));
        header->setText(_data.name + " " + _data.patronimic);
        raiting->setText("Рейтинг: " + QString::number(_data.raiting));
        raiting_icon->setPixmap(QPixmap(icon + icons::gold_star).scaled(text_size, text_size));
    //------------------------
    //НАСТРОЙКИ ФОРМАТИРОВАНИЯ
        setTextSize(header, text_size);
        setTextSize(raiting, text_size);
        photo->setFixedSize(photo_size, photo_size);
        setFixedSize(my_size);
    //------------------------
    //ФОРМИРОВАНИЕ LAYOUT
        layout_raiting->addWidget(raiting);
        layout_raiting->addWidget(raiting_icon);
        layout_raiting->addStretch(0);
        layout_raiting->setMargin(0);
        layout_raiting->setSpacing(10);
        layout_info->addWidget(header);
        layout_info->addLayout(layout_raiting);
        layout_info->setMargin(0);
        layout_info->setSpacing(info_spacing);
        layout->addWidget(photo);
        layout->addLayout(layout_info);
        layout->setMargin(PSW_Doctor::margin);
        layout->setSpacing(PSW_Doctor::spacing);
        setLayout(layout);
        show();
    //------------------------
    connect(this, &Button::clicked, this, &PSW_Doctor::clicked);
}

void PSW_Doctor::clicked()
{
    using namespace GlobalData;
    Widget *widget = new Widget();
    MainWidget::create_profile_doctor(widget, my_data.email, GlobalData::Output_Guest);
    Viewer *viewer = new Viewer(widget);
}


PatientSearchWidget::PatientSearchWidget(Search *_object, QWidget *_parent) : Widget(_parent)
{
    using namespace GlobalData;
    my_object = _object;
    //ИНИЦИАЛИЗАЦИЯ ПЕРЕМЕННЫХ
        margin = 0;
        spacing = interface::spacing;
        search_margin = 0;
        search_spacing = interface::indent;
        size_filter = QSize(screen::geometry.width() - interface::indent * 2, interface::row_size);
        size_search = QSize(screen::geometry.width() - interface::indent * 2, interface::row_size * 1.5);
        size_results = QSize(screen::geometry.width() - interface::indent * 2, screen::geometry.height() - size_search.height() - size_filter.height() - spacing * 2);
        icon_size = size_search.height() - margin * 2;

        filter = new QComboBox();
        search = new Widget();
        search_text = new QLineEdit();
        search_start = new Button();
        results_area = new Widget();
        results = new Widget(results_area);
        layout = new QVBoxLayout();
        layout_search = new QHBoxLayout();
        layout_results = new QVBoxLayout();
    //------------------------
    //ЗАПОЛНЕНИЕ ДАННЫМИ
        filter->addItem(allDoctors);
        filter->setCurrentText(allDoctors);
        search_start->setPixmap(QPixmap(directory::icon + directory::icons::search_patient).scaled(icon_size, icon_size));
    //------------------------
    //НАСТРОЙКИ ФОРМАТИРОВАНИЯ
        search->setFixedSize(size_search);
        search_start->setFixedSize(icon_size, icon_size);
        filter->setFixedSize(size_filter);
        results_area->setFixedSize(size_results);
        results->setFixedWidth(size_results.width());
        results->setMinimumHeight(size_results.height());
        results->setMoveableBorder(QRect(QPoint(0, 0), size_results));
        results->setMovable_vertical(true);
        results->move(0, 0);
    //------------------------
    //ФОРМИРОВАНИЕ LAYOUT
        layout_search->addWidget(search_text);
        layout_search->addWidget(search_start);
        layout_search->setMargin(search_margin);
        layout_search->setSpacing(search_spacing);
        search->setLayout(layout_search);
        layout_results->setMargin(results_margin);
        layout_results->setSpacing(results_spacing);
        results->setLayout(layout_results);
        layout->addWidget(search);
        layout->addWidget(filter);
        layout->addWidget(results_area);
        layout->setMargin(margin);
        layout->setSpacing(spacing);
        setLayout(layout);
    //------------------------
        connect(filter, &QComboBox::currentTextChanged, this, &PatientSearchWidget::filterChanged);
        connect(search_start, &Button::clicked, this, &PatientSearchWidget::searchStart);

        connect(my_object, &Search::update_all_widgets, this, &PatientSearchWidget::setDatas);
        connect(this, &PatientSearchWidget::request_search, my_object, &Search::search);
        connect(this, &PatientSearchWidget::update, my_object, &Search::update);
        emit update();
}

void PatientSearchWidget::setDatas(SearchData _data)
{
    my_data = _data;
    updateResults(my_data.search_result);
    updateFiltes(my_data.specializations);
}

void PatientSearchWidget::updateResults(QList <SearchDoctorData> _doctors)
{
    while(QLayoutItem *item = layout_results->itemAt(0))
    {
        layout_results->removeItem(item);
        layout_results->removeWidget(item->widget());
        item->widget()->deleteLater();
        delete (item);
    }

    for(int i = 0; i < _doctors.size(); i++)
    {
        PSW_Doctor *new_result = new PSW_Doctor(_doctors[i]);
        layout_results->addWidget(new_result);
    }
    if(_doctors.size() > 0)
        layout_results->addStretch(0);
    layout_results->update();
}

void PatientSearchWidget::updateFiltes(QList <SpecializationData> _specs)
{
    disconnect(filter, &QComboBox::currentTextChanged, this, &PatientSearchWidget::filterChanged);
    QString last = filter->currentText();
    filter->clear();
    filter->addItem(allDoctors);
    foreach(auto spec, _specs)
    {
        filter->addItem(spec.name);
    }
    filter->setCurrentText(last);
    connect(filter, &QComboBox::currentTextChanged, this, &PatientSearchWidget::filterChanged);
}

void PatientSearchWidget::searchStart()
{
    emit request_search(search_text->text(), my_filter_id);
}

void PatientSearchWidget::filterChanged(QString text)
{
    if(text == allDoctors)
    {
        emit request_search(search_text->text(), -1);
        my_filter_id = -1;
        return;
    }
    foreach(auto spec, my_data.specializations)
        if(spec.name == text)
        {
            emit request_search(search_text->text(), spec.id);
            my_filter_id = spec.id;
            return;
        }
}
