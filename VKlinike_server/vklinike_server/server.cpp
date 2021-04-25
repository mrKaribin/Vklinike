#include "server.h"
#include "client.h"
#include <QBuffer>
#include <QJsonDocument>
#include <QNetworkDatagram>
#include <QUdpSocket>

Server::Server()
{
    //QThread* my_thread = new QThread();
    //moveToThread(my_thread);
    //my_thread->start();

    connector = new QTcpSocket();
    connector->connectToHost("192.168.1.10", 10200);
    //write_to_socket("1.1.1.1", "header", "path");

    connect(this, &Server::newConnection, this, &Server::connection_create);
    QTimer::singleShot(GLOBAL::testing ? 15000 : 10, this, &Server::initialize);
}

void Server::initialize()
{
    using namespace GLOBAL;
    if(listen(QHostAddress(server_host), server_port))
        console_write("Сервер прослушивает адрес '" + server_host + ":" + QString::number(server_port) + "'\n");
    else
    {
        console_write("Не удалось начать прослушивание адреса '" + server_host + ":" + QString::number(server_port) + "'. Ошибка: " + errorString());
    }
}

void Server::connection_create()
{
    Client* client = new Client(nextPendingConnection(), this);
    GLOBAL::console_write("Новое соединение: " + client->socket()->peerAddress().toString() + ":" + QString::number(client->socket()->peerPort()));
}

void Server::connection_destroy()
{
    Client* client = (Client*)sender();
    GLOBAL::console_write("Разорвано соединение: " + client->adress_full());
    client->deleteLater();
}

void Server::write_to_socket(QTcpSocket *socket, QJsonObject object)
{
    QDataStream stream(socket);
    QByteArray block = QJsonDocument(object).toJson();
    QByteArray array;

    union {
        char bytes[4];
        int32_t value;
    } integer;

    integer.value = block.size();
    array.append(0x012);
    array.append(0x023);
    array.append(0x034);
    array.append(0x045);
    array.append(&integer.bytes[3], 1);
    array.append(&integer.bytes[2], 1);
    array.append(&integer.bytes[1], 1);
    array.append(&integer.bytes[0], 1);
    array.append(0x001);
    array.append(block);
    int block_size = block.size();
    int size = array.size();
    int maxSize = 8 * 100;
    int delay = 10;
    socket->write(array);
}

void Server::write_to_socket(QTcpSocket *socket, QByteArray enclosure)
{
    QByteArray array;

    union {
        char bytes[4];
        int32_t value;
    } integer;

    integer.value = enclosure.size();
    array.append(0x012);
    array.append(0x023);
    array.append(0x034);
    array.append(0x045);
    array.append(&integer.bytes[3], 1);
    array.append(&integer.bytes[2], 1);
    array.append(&integer.bytes[1], 1);
    array.append(&integer.bytes[0], 1);
    array.append(0x002);
    array.append(enclosure);
    int enclosure_size = enclosure.size();
    int size = array.size();
    int maxSize = 8 * 100;
    int delay = 5;
    DEBUG_LOG(QString("SEND ENCLOSURE: ") + QString::number(size) + " bytes");

    socket->write(array);
}

void Server::write_to_socket(QString ip, QString header, QString path)
{
    QJsonObject json
    {
        {"command", "SendFile"},
        {"ip", ip},
        {"header", header},
        {"path", path}
    };
    QByteArray block = QJsonDocument(json).toJson();

    QByteArray size = QString::number(block.size()).toUtf8();
    for(int i = 0; i < 5 - size.size(); i++)
        size.insert(0, '0');
    connector->write(size);
    connector->write(block);
    DEBUG_LOG(QString("SEND ENCLOSURE: ") + header);
}
