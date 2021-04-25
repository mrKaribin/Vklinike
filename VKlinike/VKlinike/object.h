#ifndef OBJECT_H
#define OBJECT_H

#include "globaldata.h"

#include <QObject>


class Object : public QObject
{
    Q_OBJECT
public:
    Object(QObject *parent = nullptr);

private:
    QStringList                 my_replies;
    QStringList                 my_reusable_replies;
    QString                     my_replyRequest                 = "";
    bool                        my_replyReceived                = false;
    bool                        my_ready                        = false;

public slots:
    void                        my_srv_rpl(QString header, QByteArray body);
    virtual void                server_reply(QString header, QByteArray body) = 0;
    void                        server_expextedReply(QString header);
    void                        server_expextedReusableReply(QString header);
    void                        server_waitForReply(QString request);
    void                        server_waitingReply(QString request);
    void                        server_request(QString header, QByteArray body, bool waitReply = true);

    void                        ready();
    void                        server_waitForReady();

signals:
    void my_srvr_rqst(QString header, QByteArray body);

};

#endif // OBJECT_H
