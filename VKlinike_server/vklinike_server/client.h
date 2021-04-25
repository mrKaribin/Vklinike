#ifndef CLIENT_H
#define CLIENT_H

#include "global.h"
#include "packer.h"
#include "Datas/tariffs.h"
#include "Datas/dialogs.h"

#include <QObject>
#include <QFile>
#include <QDataStream>
#include <QJsonObject>


struct Payout_PayPal
{
    Payout_PayPal(QString _login, QString _password, tariffs tariff, int _patient_id, int _doctor_id)
    {
        login = _login;
        password = _password;
        valuta = "RUB";
        cost = tariff.cost();
        tariff_id = tariff.id();
        iser_patient_id = _patient_id;
        user_doctor_id = _doctor_id;
        file_name = "paypal_link_" + QString::number(iser_patient_id) + ".txt";
    }

    QString login;
    QString password;
    QString valuta;
    QString file_name;
    int tariff_id;
    int cost;
    int iser_patient_id;
    int user_doctor_id;

    QString token;
    QString payment_id;
    QString link_approve;
};


struct Enclosure
{
    Enclosure(QString _header, QString _path){
        header = _header;
        path = _path;
    }

    QString header;
    QString path;
};


class Client : public QObject
{
    Q_OBJECT
public:
    Client(QTcpSocket* _socket, Server* _server);
    void                    initialize();
    void                    waitForReady();

    QTcpSocket             *socket();

    QString                 adress_full();
    QString                 email();
    bool                    autorizated();
    bool                    autorization(QString login, QString password);

    QByteArray              getEnclosure(QString header);

private:
    bool                    checkPassword(Unpacker *unpacker);

    int                     new_profile_base(QJsonObject profile);
    void                    get_profile_base(QString login, QJsonObject& object);
    void                    get_profile_base_limited(QString login, QJsonObject& object);

    int                     new_profile_doctor(QJsonObject profile);
    void                    get_profile_doctor(QString login, QJsonObject& object);
    void                    get_profile_doctor_limited(QString login, QJsonObject& object);
    void                    get_subscribtions_doctor(QString login, QJsonObject& object);
    void                    get_comments_doctor(QString login, QJsonObject& object);

    int                     new_profile_patient(QJsonObject profile);
    void                    get_profile_patient(QString login, QJsonObject& object);
    void                    get_profile_patient_limited(QString login, QJsonObject& object);
    void                    get_subscribtions_patient(QString login, QJsonObject& object);

    void                    get_dialogList(int user_id, int mode, QJsonObject &object);
    void                    get_dialogMessages(int dialog_id, QJsonObject &object);
    dialogs&                new_dialog(int user1_id, int user2_id, int mode1, int mode2);

    void                    get_available_specializations(QJsonObject& object);
    void                    get_available_valutas(QJsonObject& object);

    void                    searchDoctors(QString key, int specialization_id, QJsonObject &object);

    void                    new_payment_PayPal(int doctor_id, int patient_id, int tariff_id);
    void                    runScript_payout_paypal_create(Payout_PayPal& payout);
    bool                    runScript_payout_paypal_update(Payout_PayPal& payout);
    bool                    runScript_payout_paypal_capture(Payout_PayPal& payout);

    void                    clearBlock();

    QTcpSocket                 *my_socket;

    QMap<QString, QByteArray>   array_enclosures;
    QList <QByteArray>          array_output_enclosures;
    QList <Enclosure>           array_output_enclosure_paths;

    QString                     my_email                    = GLOBAL::null_str;
    int32_t                     nextBlockSize               = 0;
    QByteArray                  nextBlock;
    char                        nextBlockType               = 0;
    bool                        my_ready                    = false;
    QString                     my_adress_full;
    bool                        payout_paypal_waiting              = false;

public slots:
    void socket_read();
    void socket_write(QString header, QJsonObject body);
    void socket_write(QString header, QByteArray enclosure);
    void socket_write(QString header, QString path);
    void socket_write(QString email, QString header, QJsonObject body);
    void socket_disconnected();

    void query(QJsonObject _request);

signals:
    void write_to_socket(QTcpSocket*, QJsonObject);
    void write_to_socket(QTcpSocket*, QByteArray);
    void write_to_socket(QString, QString ,QString);
    void write_to_socket_by_email(QString, QString, QByteArray);
    void disconnect_from_socket();
};

#endif // CLIENT_H
