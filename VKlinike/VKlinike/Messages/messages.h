#ifndef MESSAGES_H
#define MESSAGES_H

#include "object.h"
#include "Messages/messageswidget.h"
#include "messagesdata.h"


class Messages : public Object
{
    Q_OBJECT
public:
    Messages(DialogsData _data, Widget *_widget_parent = nullptr, GlobalData::OutputType _outputType = GlobalData::Output_Guest, QThread* _object_thread = nullptr);
    Messages(Widget *_widget_parent = nullptr, GlobalData::OutputType _outputType = GlobalData::Output_Guest, QThread* _object_thread = nullptr);
    void Messages_initialize();

    void load();
    void readFromBytes(QByteArray array, GlobalData::OutputType mode = GlobalData::Output_Owner);
    void waitForReady();

    MessagesWidget* widget();

private:
    DialogsData                         my_data;
    Widget                             *my_widget_parent;
    GlobalData::OutputType              my_outputType;
    QString                             my_login                        = "";
    bool                                my_ready                        = false;

    MessagesWidget                     *my_widget;

public slots:
    void server_reply(QString header, QByteArray body) override;

signals:
    void update_all_widgets(DialogsData);
};

#endif // MESSAGES_H
