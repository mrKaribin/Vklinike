#include "object.h"
#include "socket.h"


Object::Object(QObject *parent) : QObject(parent)
{
    connect(this, &Object::my_srvr_rqst, GlobalData::socket, &Socket::socket_write);
    connect(GlobalData::socket, &Socket::package_received, this, &Object::my_srv_rpl);
}

void Object::server_request(QString header, QByteArray body, bool waitReply)
{
    if(waitReply)
        my_replies << GlobalData::query::prefix_reply + header;
    emit my_srvr_rqst(header, body);
}

void Object::server_expextedReply(QString header)
{
    my_replies << header;
}

void Object::server_expextedReusableReply(QString header)
{
    my_reusable_replies << header;
}

void Object::server_waitingReply(QString reply)
{
    my_replies << reply;
}

void Object::my_srv_rpl(QString header, QByteArray body)
{
    if(header == my_replyRequest)
        my_replyReceived = true;

    foreach(auto reply, my_replies)
    {
        if(header == reply)
        {
            my_replies.removeOne(reply);
            server_reply(header, body);
        }
    }
    foreach(auto reply, my_reusable_replies)
    {
        if(header == reply)
            server_reply(header, body);
    }
}

void Object::server_waitForReply(QString request)
{
    my_replyRequest = request;
    my_replyReceived = false;
    while(!my_replyReceived)
    {
        QApplication::processEvents();
    }
}

void Object::ready()
{
    my_ready = true;
}

void Object::server_waitForReady()
{
    my_ready = false;
    while(!my_ready)
    {
        QApplication::processEvents();
    }
}


