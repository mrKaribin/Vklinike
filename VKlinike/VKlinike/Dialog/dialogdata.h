#ifndef DIALOGDATA_H
#define DIALOGDATA_H

#include "globaldata.h"

#include <QObject>
#include <QVector>
#include <QDateTime>
#include <QFile>


struct Attachment
{
    enum DataType {Null = 0, Image, Video, Document};

    Attachment() {};
    Attachment(QString _adress, QByteArray _data = QByteArray(), bool save = true)
    {
        name.clear();
        data.clear();
        group = Attachment::Null;
        if(_adress == ""){
            return;
        }

        _adress = _adress.split("/").last();
        name = _adress;
        int x = _adress.indexOf('.');

        type = _adress.mid(x + 1);
        if(type == "jpg" || type == "png" || type == "xpm")
            group = Image;
        if(type == "mp4")
            group = Video;
        if(type == "docx")
            group = Document;

        if(_data.isEmpty()){
            if(QFile::exists(GlobalData::directory::attachment + name))
            {
                QFile file(GlobalData::directory::attachment + name);
                if(!file.open(QIODevice::ReadOnly))
                    GlobalData::error_Show("Чтение вложенного файла", "Не удалось открыть файл для чтения");
                data = file.readAll();
            }
        }
        else
        {
            data = _data;
            if(save && !QFile::exists(GlobalData::directory::attachment + name))
            {
                QFile file(GlobalData::directory::attachment + name);
                if(!file.open(QIODevice::WriteOnly))
                    GlobalData::error_Show("Сохранение вложенного файла", "Не удалось открыть файл для сохранения");
                file.write(data);
            }
        }
    }

    void operator=(Attachment _attachment)
    {
        name = _attachment.name;
        type = _attachment.type;
        group = _attachment.group;
        data = _attachment.data;
    }

    QString name;
    QString type;
    DataType group = Attachment::Null;
    QByteArray data;
};


struct MessageData
{
    MessageData() {}
    MessageData(int _id, QString _sender_name, QString _sender_email, QString _message)
    {
        id = _id;
        sender_name = _sender_name;
        sender_email = _sender_email;
        message = _message;
        recd = false;
        readed = false;
        send_time = QDateTime::currentDateTime();
    }

    int id = -1;
    QString sender_name;
    QString sender_email;
    QString message;
    Attachment attachment;
    QDateTime send_time;
    bool recd;
    bool readed;
};


struct DialogData
{
    DialogData() {};
    DialogData(QString u_email, QString c_email);

    void operator <<(MessageData _message)
    {
        messages << _message;
    }

    int id;
    QString copanion_name;
    QString copanion_email;
    QString status;
    QVector <MessageData> messages;
};

Q_DECLARE_METATYPE(DialogData);

#endif // DIALOGDATA_H
