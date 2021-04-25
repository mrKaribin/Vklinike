#include "dialog.h"
#include "packer.h"
#include "mainwidget.h"

Dialog::Dialog(DialogData data) : Object()
{
    my_data = data;
    Dialog_initialization();
    my_ready = true;
}

Dialog::Dialog(int dialog_id) : Object()
{
    my_dialog_id = dialog_id;
    my_data.id = dialog_id;
    Dialog_initialization();
    QTimer::singleShot(10, this, &Dialog::load);
}

Dialog::Dialog(QString user_email, QString companion_email) : Object()
{
    Dialog_initialization();
}

void Dialog::Dialog_initialization()
{
    using namespace GlobalData::query;
    server_expextedReusableReply(prefix_reply + prefix_get + dialog + QString::number(my_data.id));
    server_expextedReusableReply(prefix_new + message + QString::number(my_data.id));
    qRegisterMetaType(&my_data);

    my_widget = new DialogWidget(this, my_data);
    GlobalData::widget_main->widgets_Swift(my_widget, MainWidget::Swift_toFullScreen);

    connect(this, &Dialog::update_all_widgets, my_widget, &DialogWidget::setData);
    connect(my_widget, &DialogWidget::message_send, this, &Dialog::message_send);
}

DialogWidget* Dialog::widget()
{
    return my_widget;
}

void Dialog::load()
{
    using namespace GlobalData::query;
    Packer packer;
    packer << GlobalData::currentLogin;
    packer << GlobalData::currentPassword;
    packer << my_dialog_id;

    server_request(prefix_get + dialog, packer.result());
    my_ready = true;
}

void Dialog::message_send(MessageData _message)
{
    using namespace GlobalData::query;
    Packer packer;
    packer << my_dialog_id;
    packer << _message.sender_email;
    packer << _message.send_time;
    packer << _message.message;
    packer << _message.attachment.type;
    packer << _message.attachment.data;
    server_request(prefix_new + message, packer.result());
}

void Dialog::message_attachment_load(QString adress)
{
    using namespace GlobalData::query;
    Packer packer;
    packer << GlobalData::currentLogin;
    packer << GlobalData::currentPassword;
    packer << adress;
    server_expextedReply(prefix_reply + prefix_get + message_attachment + QString::number(my_dialog_id));
    server_request(prefix_get + message_attachment, packer.result(), false);
}

void Dialog::message_receive(QByteArray array)
{
    using namespace GlobalData::query;
    QString attachment_name;
    Unpacker unpacker(array);
    MessageData new_data;
    unpacker >> new_data.id;
    unpacker >> new_data.sender_name;
    unpacker >> new_data.sender_email;
    unpacker >> new_data.send_time;
    unpacker >> new_data.message;
    unpacker >> new_data.recd;
    unpacker >> new_data.readed;
    unpacker >> attachment_name;
    new_data.attachment = Attachment(attachment_name);

    for(int i = 0; i < my_data.messages.size(); i++)
        if(my_data.messages[i].id == -1)
        {
            new_data.attachment = Attachment(attachment_name, my_data.messages[i].attachment.data);
            my_data.messages.remove(i);
        }
    my_data.messages << new_data;

    server_expextedReply(prefix_new + message + QString::number(my_data.id));
    emit update_all_widgets(my_data);
}

void Dialog::message_attachment_receive(QByteArray array)
{
    using namespace GlobalData::query;
    QString adress;
    QByteArray data;
    int message_id;
    Unpacker unpacker(array);
    unpacker >> message_id;
    unpacker >> adress;
    unpacker >> data;
    for(int i = 0; i < my_data.messages.size(); i++)
        if(my_data.messages[i].id == message_id)
            my_data.messages[i].attachment = Attachment(adress, data);
    emit update_all_widgets(my_data);
}

void Dialog::readFromBytes(QByteArray array, GlobalData::OutputType mode)
{
    using namespace GlobalData::query;
    my_data.messages.clear();
    Unpacker unpacker(array);
    if(mode == GlobalData::Output_Owner)
    {
        int size = 0;
        unpacker >> my_data.copanion_name;
        unpacker >> my_data.copanion_email;
        unpacker >> size;
        for(int i = 0; i < size; i++)
        {
            MessageData new_data;
            QString attachment_name;
            unpacker >> new_data.id;
            unpacker >> new_data.sender_name;
            unpacker >> new_data.sender_email;
            unpacker >> new_data.send_time;
            unpacker >> new_data.message;
            unpacker >> new_data.recd;
            unpacker >> new_data.readed;
            unpacker >> attachment_name;
            new_data.attachment = Attachment(attachment_name);
            my_data << new_data;
        }
    }
    emit update_all_widgets(my_data);
    server_expextedReply(prefix_reply + prefix_get + dialog + QString::number(my_data.id));
    ready();
}

void Dialog::server_reply(QString header, QByteArray body)
{
    using namespace GlobalData::query;
    QString _header = header;
    if(header == prefix_reply + prefix_get + dialog + QString::number(my_data.id))
        readFromBytes(body);
    if(header == prefix_new + message + QString::number(my_data.id))
        message_receive(body);
    if(header == prefix_reply + prefix_get + message_attachment + QString::number(my_dialog_id))
        message_attachment_receive(body);
}

void Dialog::waitForReady()
{
    while(!my_ready)
    {
        QApplication::processEvents();
    }
}
