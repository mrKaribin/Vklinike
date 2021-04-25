#ifndef SEARCHDATA_H
#define SEARCHDATA_H

#include <QObject>
#include <QPixmap>


struct SearchDoctorData
{
    SearchDoctorData() {}
    SearchDoctorData(QPixmap _photo, QString _name, QString _surname, QString _patronimic, float _raiting);

    SearchDoctorData operator <<(QString spec){
        specializations << spec;
        return *this;
    }

    QPixmap photo;
    QString name;
    QString surname;
    QString patronimic;
    QString email;
    QList <QString> specializations;
    float raiting;
};

struct SpecializationData
{
    int id;
    QString name;
    QString info;
};

struct SearchData
{
    SearchData operator <<(SpecializationData spec){
        specializations << spec;
        return *this;
    }
    SearchData operator <<(SearchDoctorData result){
        search_result << result;
        return *this;
    }

    QList <SpecializationData> specializations;
    QList <SearchDoctorData> search_result;
};

Q_DECLARE_METATYPE(SearchData);

#endif // SEARCHDATA_H
