#ifndef PATIENTSEARCHWIDGET_H
#define PATIENTSEARCHWIDGET_H

#include "widget.h"
#include "Search/search.h"
#include "Search/searchdata.h"
#include "button.h"

#include <QLineEdit>
#include <QComboBox>
#include <QLayout>

class Search;


class PSW_Doctor : public Button
{
    Q_OBJECT
public:
    PSW_Doctor(SearchDoctorData _data);

private:
    SearchDoctorData                my_data;

    QLabel                         *photo;
    QLabel                         *header;
    QLabel                         *raiting;
    QLabel                         *raiting_icon;

    QSize                           my_size;
    int                             photo_size;
    int                             text_size;
    int                             info_spacing;
    int                             margin;
    int                             spacing;

public slots:
    void clicked();

};


class PatientSearchWidget : public Widget
{
    Q_OBJECT
public:
    PatientSearchWidget(Search* _object, QWidget* parent = nullptr);

private:
    SearchData                  my_data;
    int                         my_filter_id            = -1;
    Search                     *my_object;

    QComboBox                  *filter;
    Widget                     *search;
    QLineEdit                  *search_text;
    Button                     *search_start;
    Widget                     *results_area;
    Widget                     *results;
    QVBoxLayout                *layout;
    QHBoxLayout                *layout_search;
    QVBoxLayout                *layout_results;

    QSize                       size_search;
    QSize                       size_filter;
    QSize                       size_results;
    int                         margin;
    int                         spacing;
    int                         search_margin;
    int                         search_spacing;
    int                         results_margin;
    int                         results_spacing;
    int                         icon_size;

    QString                     allDoctors              = "Все врачи";

public slots:
    void                        setDatas(SearchData _data);
    void                        updateResults(QList<SearchDoctorData> _doctors);
    void                        updateFiltes(QList <SpecializationData> _specs);

    void                        searchStart();
    void                        filterChanged(QString text);

signals:
    void request_search(QString text, int spec_id);
    void update();

};

#endif // PATIENTSEARCHWIDGET_H
