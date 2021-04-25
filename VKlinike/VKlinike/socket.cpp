#include "socket.h"

#include <QHostAddress>


Socket::Socket() : QObject()
{
    my_socket = new QTcpSocket(this);

    connect(my_socket, &QTcpSocket::connected, this, &Socket::connected);
    connect(my_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socket_Error(QAbstractSocket::SocketError)));
    connect(my_socket, &QTcpSocket::readyRead, this, &Socket::socket_read);

    my_socket->connectToHost(QHostAddress(GlobalData::server_host), GlobalData::server_port);
}

QTcpSocket* Socket::socket()
{
    return my_socket;
}

void Socket::connected()
{

}

void Socket::disconnection()
{
    my_socket->disconnectFromHost();
}

void Socket::socket_read()
{
    QDataStream socket(my_socket);
    socket.setVersion(QDataStream::Qt_5_12);
    QByteArray header;
    QByteArray body;
    QByteArray array;
    char* buffer;
    uint lenth;

    if(!nextBlockSize){
        if(my_socket->bytesAvailable() > sizeof(quint32))
            socket >> nextBlockSize;
        else
            return;
    }
    if(my_socket->bytesAvailable() < nextBlockSize)
        return;

    buffer = new char[nextBlockSize];
    my_socket->read(buffer, nextBlockSize);
    array = QByteArray(buffer, nextBlockSize);

    QDataStream in(array);
    in.setVersion(QDataStream::Qt_5_12);

    in.readBytes(buffer, lenth);
    header = QByteArray(buffer, lenth);
    delete(buffer);

    in.readBytes(buffer, lenth);
    body = QByteArray(buffer, lenth);
    delete(buffer);
    nextBlockSize = 0;

    emit package_received(QString::fromUtf8(header), body);
    socket_read();
}

void Socket::socket_write(QString header, QByteArray body)
{
    uint block_size = 0;
    QByteArray arrBlock;
    QByteArray header_array = header.toUtf8();
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    out << quint32(0);
    out.writeBytes(header_array.data(), (uint) header_array.length());
    out.writeBytes(body.data(), (uint) body.length());

    block_size = arrBlock.length() - sizeof(quint32);
    out.device()->seek(0);
    out << block_size;

    my_socket->write(arrBlock);
}

void Socket::socket_Error(QAbstractSocket::SocketError err)
{
    QString mess;

    if(err == QAbstractSocket::ConnectionRefusedError)
        mess = "Соединение было разорвано другим узлом (или по тайм-ауту)";
    else if(err == QAbstractSocket::RemoteHostClosedError)
        mess = "Соединение было разорвано сервером";
    else if(err == QAbstractSocket::HostNotFoundError)
        mess = "Адрес сервера не найден";
    else if(err == QAbstractSocket::SocketAccessError)
        mess = "Приложение не получило необходимых прав";
    else if(err == QAbstractSocket::SocketResourceError)
        mess = "Системе не хватает ресурсов";
    else if(err == QAbstractSocket::SocketTimeoutError)
        mess = "Время для соединения с сервером истекло";
    else if(err == QAbstractSocket::DatagramTooLargeError)
        mess = "Объём передаваемых данных выше установленного в операционной системе ограничения";
    else if(err == QAbstractSocket::NetworkError)
        mess = "Непредвиденные проблемы с сетью";
    else if(err == QAbstractSocket::AddressInUseError)
        mess = "Адрес сервера уже используется в режиме эксклюзивного использования";
    else if(err == QAbstractSocket::SocketAddressNotAvailableError)
        mess = "Адрес не найден на узле";
    else if(err == QAbstractSocket::UnsupportedSocketOperationError)
        mess = "Операция не поддерживается операционной системой";
    else if(err == QAbstractSocket::ProxyAuthenticationRequiredError)
        mess = "Ошибка прокси сервера";
    else if(err == QAbstractSocket::SslHandshakeFailedError)
        mess = "Подтверждение связи SSL/TLS завершилось неудачей";
    else if(err == QAbstractSocket::UnfinishedSocketOperationError)
        mess = "Последняя неудачная операция еще не завершена ";
    else if(err == QAbstractSocket::ProxyConnectionRefusedError)
        mess = "Невозможно связаться с прокси-сервером, поскольку соединение к этому серверу было запрещено";
    else if(err == QAbstractSocket::ProxyConnectionClosedError)
        mess = "Соединение с прокси-сервером было неожиданно закрыто";
    else if(err == QAbstractSocket::ProxyConnectionTimeoutError)
        mess = "Время соединения с прокси-сервером истекло";
    else if(err == QAbstractSocket::ProxyNotFoundError)
        mess = "Адрес прокси не был найден";
    else if(err == QAbstractSocket::ProxyProtocolError)
        mess = "Ответ прокси-сервера не интерпритируется";
    else if(err == QAbstractSocket::UnknownSocketError)
        mess = "Произошла неопределённая ошибка";

    GlobalData::error_Critical("Ошибка сети", mess);
}
