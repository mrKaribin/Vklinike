#include "search.h"
#include "packer.h"

#include <QThread>


Search::Search(QThread *_thread) : Object()
{
    qRegisterMetaType(&my_data);
    if(_thread == nullptr){
        _thread = new QThread();
        _thread->start();
    }
    moveToThread(_thread);
    QTimer::singleShot(10, this, &Search::load);
}

Widget* Search::create_widget_search(Search *object)
{
    PatientSearchWidget *search_patient = new PatientSearchWidget(object);
    return search_patient;
}

void Search::load()
{
    using namespace GlobalData::query;
    server_request(prefix_get + specializations, QByteArray());
}

void Search::search(QString text, int spec_id)
{
    using namespace GlobalData::query;
    Packer packer;
    packer << GlobalData::currentLogin;
    packer << GlobalData::currentPassword;
    packer << text;
    packer << spec_id;
    server_request(prefix_get + list_doctor, packer.result());
}

void Search::update()
{
    emit update_all_widgets(my_data);
}

void Search::server_reply(QString header, QByteArray body)
{
    using namespace GlobalData::query;
    if(header == prefix_reply + prefix_get + specializations)
        readFromBytes_Specializations(body);
    if(header == prefix_reply + prefix_get + list_doctor)
        readFromBytes_SearchResult(body);
}

void Search::readFromBytes_Specializations(QByteArray array)
{
    my_data.specializations.clear();
    int size;
    Unpacker unpacker(array);
    unpacker >> size;
    for(int i = 0; i < size; i++)
    {
        SpecializationData spec;
        unpacker >> spec.id;
        unpacker >> spec.name;
        unpacker >> spec.info;
        my_data.specializations << spec;
    }

    emit update_all_widgets(my_data);
}

void Search::readFromBytes_SearchResult(QByteArray array)
{
    my_data.search_result.clear();
    int size;
    Unpacker unpacker(array);
    unpacker >> size;
    for(int i = 0; i < size; i++)
    {
        SearchDoctorData new_doctor;
        unpacker >> new_doctor.name;
        unpacker >> new_doctor.surname;
        unpacker >> new_doctor.patronimic;
        QByteArray photo_array;
        unpacker >> photo_array;
        new_doctor.photo.loadFromData(photo_array);
        unpacker >> new_doctor.email;
        unpacker >> new_doctor.raiting;
        int specs_size;
        unpacker >> specs_size;
        for(int j = 0; j < specs_size; j++)
        {
            QString spec;
            unpacker >> spec;
            new_doctor << spec;
        }
        my_data.search_result << new_doctor;
    }
    emit update_all_widgets(my_data);
}
