#include "Messages/messages.h"
#include "packer.h"

#include <QThread>


Messages::Messages(DialogsData _data, Widget* _widget_parent, GlobalData::OutputType _outputType, QThread* _object_thread) : Object()
{
    my_data = _data;
    my_widget_parent = _widget_parent;
    my_outputType = _outputType;
    Messages_initialize();
    if(_object_thread == nullptr)
    {
        _object_thread = new QThread();
        _object_thread->start();
    }
    my_ready = true;
}

Messages::Messages(Widget* _widget_parent, GlobalData::OutputType _outputType, QThread* _object_thread) : Object()
{
    my_data = DialogsData(GlobalData::currentLogin);
    my_widget_parent = _widget_parent;
    my_outputType = _outputType;
    my_login = GlobalData::currentLogin;
    Messages_initialize();
    if(_object_thread == nullptr)
    {
        _object_thread = new QThread();
        _object_thread->start();
    }
    QTimer::singleShot(10, this, &Messages::load);
}

void Messages::Messages_initialize()
{
    qRegisterMetaType(&my_data);

    my_widget = new MessagesWidget(this, my_data, my_widget_parent);

    connect(this, &Messages::update_all_widgets, my_widget, &MessagesWidget::setData);
}

void Messages::load()
{
    using namespace GlobalData::query;
    QString query;
    Packer packer;
    bool isDoctor = (GlobalData::currentMode == GlobalData::Mode_Doctor ? true : false);
    packer << GlobalData::currentLogin;
    packer << GlobalData::currentPassword;
    packer << isDoctor;
    query = prefix_get + dialogs;

    server_request(query, packer.result());
    server_waitForReady();
    emit update_all_widgets(my_data);
    my_ready = true;
}

void Messages::readFromBytes(QByteArray array, GlobalData::OutputType mode)
{
    Unpacker unpacker(array);
    if(mode == GlobalData::Output_Owner)
    {
        int size = 0;
        unpacker >> size;
        for(int i = 0; i < size; i++)
        {
            QByteArray photo_array;
            DialogPreviewData new_data;
            unpacker >> new_data.id;
            unpacker >> new_data.name;
            unpacker >> new_data.surname;
            unpacker >> new_data.patronimic;
            unpacker >> new_data.email;
            unpacker >> photo_array;
            new_data.photo.loadFromData(photo_array);
            unpacker >> new_data.specialization;
            unpacker >> new_data.specialization_info;
            //unpacker >> new_data.lastMessage.sender_name;
            //unpacker >> new_data.lastMessage.sender_email;
            //unpacker >> new_data.lastMessage.send_time;
            //unpacker >> new_data.lastMessage.message;
            //unpacker >> new_data.lastMessage.recd;
            //unpacker >> new_data.lastMessage.readed;
            my_data << new_data;
        }
    }
    ready();
    update_all_widgets(my_data);
}

void Messages::server_reply(QString header, QByteArray body)
{
    using namespace GlobalData::query;
    QString _header = header;
    if(header == prefix_reply + prefix_get + dialogs)
        readFromBytes(body);
}

void Messages::waitForReady()
{
    while(!my_ready)
    {
        QApplication::processEvents();
    }
}

MessagesWidget* Messages::widget()
{
    return my_widget;
}
