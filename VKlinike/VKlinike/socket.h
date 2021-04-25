#ifndef SOCKET_H
#define SOCKET_H

#include "globaldata.h"


class Socket : public QObject
{
    Q_OBJECT
public:
    Socket();

    QTcpSocket             *socket();

private:
    QTcpSocket             *my_socket;

    uint                    nextBlockSize = 0;
public slots:
    void connected();
    void socket_Error(QAbstractSocket::SocketError err);
    void disconnection();

    void socket_read();
    void socket_write(QString header, QByteArray body);

signals:
    void package_received(QString header, QByteArray array);

};

#endif // SOCKET_H
