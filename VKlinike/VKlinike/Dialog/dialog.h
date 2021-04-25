#ifndef DIALOG_H
#define DIALOG_H

#include "Dialog/dialogdata.h"
#include "Dialog/dialogwidget.h"
#include "object.h"
#include "button.h"


class Dialog : public Object
{
    Q_OBJECT
public:
    Dialog(DialogData data);
    Dialog(int dialog_id);
    Dialog(QString user_email, QString companion_email);
    void Dialog_initialization();

    void                                waitForReady();

    DialogWidget*                       widget();

private:
    DialogData                          my_data;
    DialogWidget                       *my_widget;
    GlobalData::OutputType              my_outputType;
    int                                 my_dialog_id            = 0;
    bool                                my_ready                = false;

public slots:
    void                                server_reply(QString header, QByteArray body) override;

    void                                load();
    void                                message_send(MessageData message);
    void                                message_attachment_load(QString adress);

    void                                readFromBytes(QByteArray array, GlobalData::OutputType mode = GlobalData::Output_Owner);
    void                                message_receive(QByteArray array);
    void                                message_attachment_receive(QByteArray array);

signals:
    void update_all_widgets(DialogData);

};

#endif // DIALOG_H
