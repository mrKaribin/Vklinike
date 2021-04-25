#ifndef MESSAGESDATA_H
#define MESSAGESDATA_H

#include "globaldata.h"
#include "Dialog/dialogdata.h"


struct DialogPreviewData
{
    int id;
    QPixmap photo;
    QString email;
    QString name;
    QString surname;
    QString patronimic;
    QString specialization;
    QString specialization_info;
    MessageData lastMessage;
    bool forChild = false;
};


struct DialogsData
{
    DialogsData() {};
    DialogsData(QString _email)
    {
        email = _email;
    }

    void operator << (DialogPreviewData message)
    {
        messages << message;
    }

    QString email;
    QVector <DialogPreviewData> messages;
};

Q_DECLARE_METATYPE(DialogsData);

#endif // MESSAGESDATA_H
