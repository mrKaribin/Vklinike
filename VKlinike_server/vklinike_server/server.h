#ifndef SERVER_H
#define SERVER_H

#include <global.h>
#include <QObject>
#include <QJsonObject>


class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();

private:
    QTcpSocket*                     connector;

public slots:
    void initialize();
    void connection_create();
    void connection_destroy();
    void write_to_socket(QTcpSocket *socket, QJsonObject object);
    void write_to_socket(QTcpSocket *socket, QByteArray enclosure);
    void write_to_socket(QString ip, QString header, QString path);

signals:
    void write_to_socket_by_email(QString email, QJsonObject object);
};

#endif // SERVER_H
