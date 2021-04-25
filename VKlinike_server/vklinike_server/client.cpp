#include <windows.h>
#include <QJsonDocument>
#include <QJsonArray>
#include <QCoreApplication>

#include "client.h"
#include "server.h"
#include "tester.h"

#define CHECK_SATISFACTORY(condition, header) if(!condition) socket_write(prefix_reply + header, negation.toUtf8());


Client::Client(QTcpSocket *_socket, Server *_server) : QObject()
{
    my_socket = _socket;
    QThread* my_thread = new QThread;
    my_thread->start();
    moveToThread(my_thread);
    my_adress_full = my_socket->peerAddress().toString() + ":" + QString::number(my_socket->peerPort());

    connect(my_socket, &QTcpSocket::disconnected, this, &Client::socket_disconnected);
    connect(this, &Client::disconnect_from_socket, _server, &Server::connection_destroy);
    connect(my_socket, &QTcpSocket::readyRead, this, &Client::socket_read);
    connect(this, SIGNAL(write_to_socket(QTcpSocket*, QJsonObject)), _server, SLOT(write_to_socket(QTcpSocket*, QJsonObject)));
    connect(this, SIGNAL(write_to_socket(QTcpSocket*, QByteArray)), _server, SLOT(write_to_socket(QTcpSocket*, QByteArray)));
    connect(this, SIGNAL(write_to_socket(QString, QString, QString)), _server, SLOT(write_to_socket(QString, QString, QString)));
    QTimer::singleShot(10, this, &Client::initialize);
}

void Client::initialize()
{
    QSqlDatabase *database = new QSqlDatabase();
    GLOBAL::database_connect(*database);
    GLOBAL::database_check(*database);
    my_ready = true;
}

void Client::waitForReady()
{
    while(!my_ready)
    {
        QCoreApplication::processEvents();
    }
}

QTcpSocket* Client::socket()
{
    return my_socket;
}

bool Client::autorizated()
{
    if(my_email != GLOBAL::null_str)
        return true;
    else return false;
}

QString Client::adress_full()
{
    return my_adress_full;
}

bool Client::autorization(QString login, QString password)
{
    users user(login);
    if(user.id() > 0 && user.password() == password)
    {
        my_email = login;
        return true;
    }
    else
        return false;
}

void Client::query(QJsonObject request)
{
    using namespace GLOBAL::query;
    QString header = request.find("header").value().toString();
    QJsonObject body = request.find("body").value().toObject();
    waitForReady();
    DEBUG_LOG(my_adress_full + ":INPUT: " + header);
    if(header == "Autorization")
    {
        QString login, password;
        if(body.find("login") != body.end() && body.find("password") != body.end())
        {
            login = body.find("login").value().toString();
            password = body.find("password").value().toString();
        }

        if(autorization(login, password))
        {
            socket_write("Reply Autorization", QJsonObject {{"status", "successful"}});
        }
        else
        {
            socket_write("Reply Autorization", QJsonObject {{"status", "denied"}});
        }
    }
    if(header == "Registration")
    {
        if(body.find("ProfileBase") != body.end())
        {
            users user = users::createFromJson(body.find("ProfileBase").value().toObject(), this, true);
            doctors dpctor(user.id(), 0, QTime(), QTime(), GLOBAL::null_str, GLOBAL::null_str);
            patients patient(user.id());
            socket_write("Reply Registration", QJsonObject {{"status", "successful"}});
        }
        else
        {
            socket_write("Reply Registration", QJsonObject {{"status", "denied"}});
        }
    }
    //-------------------------------------------------------------------------------------------------------------------------------
    else if(header == "Get BasicUserData")
    {
        QString login, password;
        if(body.find("login") != body.end() && body.find("password") != body.end())
        {
            login = body.find("login").value().toString();
            password = body.find("password").value().toString();
        }

        if(autorizated() || autorization(login, password))
        {
            users user(my_email);
            QJsonObject reply;
            reply.insert("status", "successful");
            reply.insert("ProfileBase", user.toJson(this));

            int mode = body.find("mode").value().toInt();
            switch (mode) {
            case 0:{
                get_profile_doctor(login, reply);
                get_subscribtions_doctor(login, reply);
                get_comments_doctor(login, reply);
                break;
            }
            case 1:{
                get_profile_patient(login, reply);
                get_subscribtions_patient(login, reply);
                break;
            }
            }
            get_dialogList(user.id(), mode, reply);
            get_available_specializations(reply);
            get_available_valutas(reply);

            socket_write("Reply Get BasicUserData", reply);
        }
        else
            socket_write("Reply Get BasicUserData", QJsonObject {{"status", "denied"}});
    }
    else if(header == "Get ProfileBase")
    {
        QString login, password;
        int mode = 0;
        if(body.find("login") != body.end() && body.find("password") != body.end())
        {
            login = body.find("login").value().toString();
            password = body.find("password").value().toString();
        }
        if(body.find("mode") != body.end())
        {
            mode = body.find("mode").value().toInt();
        }


        if(mode == 0 && (autorizated() || autorization(login, password)))
        {
            QJsonObject reply;
            reply.insert("status", "successful");
            get_profile_base(login, reply);
            socket_write("Reply Get ProfileBase", reply);
        }
        else if(mode != 0)
        {
            QJsonObject reply;
            reply.insert("status", "successful");
            get_profile_base_limited(login, reply);
            socket_write("Reply Get ProfileDoctor", reply);
        }
        else
            socket_write("Reply Get ProfileBase", QJsonObject {{"status", "denied"}});
    }
    else if(header == "Get ProfileDoctor")
    {
        QString login, password;
        int mode = 0;
        if(body.find("login") != body.end())
            login = body.find("login").value().toString();
        if(body.find("password") != body.end())
            password = body.find("password").value().toString();
        if(body.find("mode") != body.end())
            mode = body.find("mode").value().toInt();

        if(mode == 0 && (autorizated() || autorization(login, password)))
        {
            QJsonObject reply;
            reply.insert("status", "successful");
            get_profile_doctor(login, reply);
            get_subscribtions_doctor(login, reply);
            get_comments_doctor(login, reply);
            socket_write("Reply Get ProfileDoctor", reply);
        }
        else if(mode != 0)
        {
            QJsonObject reply;
            reply.insert("status", "successful");
            get_profile_doctor_limited(login, reply);
            get_subscribtions_doctor(login, reply);
            get_comments_doctor(login, reply);
            socket_write("Reply Get ProfileDoctor", reply);
        }
        else
            socket_write("Reply Get ProfileDoctor", QJsonObject {{"status", "denied"}});
    }
    else if(header == "Get ProfilePatient")
    {
        QString login, password;
        int mode = 0;
        if(body.find("login") != body.end() && body.find("password") != body.end())
        {
            login = body.find("login").value().toString();
            password = body.find("password").value().toString();
        }
        if(body.find("mode") != body.end())
        {
            mode = body.find("mode").value().toInt();
        }

        if(mode == 0 && (autorizated() || autorization(login, password)))
        {
            QJsonObject reply;
            reply.insert("status", "successful");
            get_profile_patient(login, reply);
            socket_write("Reply Get ProfilePatient", reply);
        }
        else if(mode != 0)
        {
            QJsonObject reply;
            reply.insert("status", "successful");
            get_profile_patient_limited(login, reply);
            get_subscribtions_patient(login, reply);
            socket_write("Reply Get ProfileDoctor", reply);
        }
        else
            socket_write("Reply Get ProfilePatient", QJsonObject {{"status", "denied"}});
    }
    //-------------------------------------------------------------------------------------------------------------------------------
    else if(header == "New ProfileBase")
    {
        if(autorizated() && body.find("ProfileBase") != body.end())
        {
            QJsonObject reply;
            reply.insert("status", "successful");
            reply.insert("id", new_profile_base(body));
            socket_write("Reply New ProfileBase", reply);
        }
        else
            socket_write("Reply New ProfileBase", QJsonObject {{"status", "denied"}});
    }
    else if(header == "New ProfileDoctor")
    {
        if(autorizated() && body.find("ProfileDoctor") != body.end())
        {
            QJsonObject reply;
            reply.insert("status", "successful");
            reply.insert("id", new_profile_doctor(body));
            socket_write("Reply New ProfileDoctor", reply);
        }
        else
            socket_write("Reply New ProfileDoctor", QJsonObject {{"status", "denied"}});
    }
    else if(header == "New ProfilePatient")
    {
        if(autorizated() && body.find("ProfilePatient") != body.end())
        {
            QJsonObject reply;
            reply.insert("status", "successful");
            reply.insert("id", new_profile_patient(body));
            socket_write("Reply New ProfilePatient", reply);
        }
        else
            socket_write("Reply New ProfilePatient", QJsonObject {{"status", "denied"}});
    }
    //-------------------------------------------------------------------------------------------------------------------------------
    else if(header == "Update ProfileBase")
    {
        QJsonObject::iterator itr_profile = body.find("ProfileBase");

        if(autorizated() && itr_profile != body.end())
        {
            QJsonObject reply;
            users user = users::createFromJson(itr_profile.value().toObject(), this);

            if(user.email() != my_email)
            {
                socket_write("Reply Update ProfileDoctor", QJsonObject {{"status", "denied"}});
                return;
            }

            user.update();
            reply.insert("status", "successful");
            reply.insert("id", user.id());
            socket_write("Reply Update ProfileBase", reply);

            QJsonObject request
            {
                {"ProfileBase", user.toJson(this)}
            };
            socket_write("Updated ProfileBase " + QString::number(user.id()), request);
        }
        else
            socket_write("Reply Update ProfileBase", QJsonObject {{"status", "denied"}});
    }
    else if(header == "Update ProfileDoctor")
    {
        QJsonObject::iterator itr_profile = body.find("ProfileDoctor");

        if(autorizated() && itr_profile != body.end())
        {
            QJsonObject reply;
            doctors doctor = doctors::createFromJson(itr_profile.value().toObject());

            if(doctor.id() != doctors(my_email).id())
            {
                socket_write("Reply Update ProfileDoctor", QJsonObject {{"status", "denied"}});
                return;
            }

            doctor.update();
            reply.insert("status", "successful");
            reply.insert("id", doctor.id());
            socket_write("Reply Update ProfileDoctor", reply);

            QJsonObject request
            {
                {"ProfileDoctor", doctor.toJson()}
            };
            socket_write("Updated ProfileDoctor " + QString::number(doctor.id()), request);
        }
        else
            socket_write("Reply Update ProfileDoctor", QJsonObject {{"status", "denied"}});
    }
    else if(header == "Update ProfilePatient")
    {
        QJsonObject::iterator itr_profile = body.find("ProfilePatient");

        if(autorizated() && itr_profile != body.end())
        {
            QJsonObject reply;
            patients patient = patients::createFromJson(itr_profile.value().toObject());

            if(patient.user_id() != users(my_email).id())
            {
                socket_write("Reply Update ProfileDoctor", QJsonObject {{"status", "denied"}});
                return;
            }

            patient.update();
            reply.insert("status", "successful");
            reply.insert("id", patient.id());
            socket_write("Reply Update ProfilePatient", reply);

            QJsonObject request
            {
                {"ProfilePatient", patient.toJson()}
            };
            socket_write("Updated ProfilePatient "   + QString::number(patient.id()), request);
        }
        else
            socket_write("Reply Update ProfilePatient", QJsonObject {{"status", "denied"}});
    }
    //-------------------------------------------------------------------------------------------------------------------------------
    else if(header == "Get DialogList")
    {
        QString login, password;
        if(body.find("login") != body.end() && body.find("password") != body.end())
        {
            login = body.find("login").value().toString();
            password = body.find("password").value().toString();
        }

        if((autorizated() || autorization(login, password)) && body.find("mode") != body.end())
        {
            QJsonObject reply;
            reply.insert("status", "successful");
            get_dialogList(users(my_email, false).id(), body.find("mode").value().toInt(), reply);
            socket_write("Reply Get DialogList", reply);
        }
        else
            socket_write("Reply Get DialogList", QJsonObject {{"status", "denied"}});
    }
    else if(header == "Get Dialog")
    {
        QJsonObject::iterator itr_id = body.find("id");

        if(autorizated() && itr_id != body.end())
        {
            QJsonObject reply;
            reply.insert("status", "successful");
            users user(my_email, false);
            QList <messages*> dialog_messages = messages::findMessages(itr_id.value().toInt());
            QJsonArray array;
            for(auto message : dialog_messages)
                array.append(message->toJson(this));
            reply.insert("Messages", array);
            socket_write("Reply Get Dialog", reply);
        }
        else
            socket_write("Reply Get Dialog", QJsonObject {{"status", "denied"}});
    }
    else if(header == "New Dialog")
    {
        QJsonObject::iterator itr_user_1_id = body.find("user_1_id");
        QJsonObject::iterator itr_user_2_id = body.find("user_2_id");
        QJsonObject::iterator itr_user_1_mode = body.find("user_1_mode");
        QJsonObject::iterator itr_user_2_mode = body.find("user_2_mode");

        if(autorizated() && itr_user_1_id != body.end() && itr_user_2_id != body.end()
                && itr_user_1_mode != body.end() && itr_user_2_mode != body.end())
        {
            dialogs dialog = new_dialog(
                        itr_user_1_id.value().toInt(),
                        itr_user_2_id.value().toInt(),
                        itr_user_1_mode.value().toInt(),
                        itr_user_2_mode.value().toInt()
            );

            QJsonObject reply{{"status", "successful"}};
            reply.insert("Dialog", dialog.toJson(this, itr_user_1_id.value().toInt()));
            socket_write("Reply New Dialog", reply);
        }
        else
            socket_write("Reply New Dialog", QJsonObject {{"status", "denied"}});
    }
    //-------------------------------------------------------------------------------------------------------------------------------
    else if(header == "New Message")
    {
        QJsonObject::iterator itr_message = body.find("Message");

        if(autorizated() && itr_message != body.end())
        {
            messages message = messages::createFromJson(this, itr_message.value().toObject(), true);
            QJsonObject object
            {
                {"status", "successful"},
                {"lastId", itr_message.value().toObject().find("id").value().toInt()},
                {"newId", message.id()}
            };
            socket_write("Reply New Message", object);
        }
        else
            socket_write("Reply New Message", QJsonObject {{"status", "denied"}});
    }
    //-------------------------------------------------------------------------------------------------------------------------------
    else if(header == "New Tariff")
    {
        QJsonObject::iterator itr_tariff = body.find("Tariff");
        QJsonObject::iterator itr_specialization_id = body.find("specialization_id");
        QJsonObject::iterator itr_duration = body.find("duration");
        QJsonObject::iterator itr_doctor_id = body.find("doctor_id");

        if(autorizated() &&
                itr_tariff != body.end() &&
                itr_specialization_id != body.end() &&
                itr_duration != body.end() &&
                itr_doctor_id != body.end())
        {
            QMultiMap <int, packages*> packs_all = packages::findPackages(itr_doctor_id.value().toInt());
            QList <packages*> packs = packs_all.values(itr_specialization_id.value().toInt());
            packages *currentPack = nullptr;
            int duration = itr_duration.value().toInt();

            for(auto pack : packs)
                if(pack->interval() == duration)
                    currentPack = pack;
            if(currentPack == nullptr)
                currentPack = new packages(itr_doctor_id.value().toInt(), itr_specialization_id.value().toInt(), duration);

            QJsonObject object = itr_tariff->toObject();
            QJsonObject::iterator itr_cost = object.find("cost");
            QJsonObject::iterator itr_valuta = object.find("valuta");
            QJsonObject::iterator itr_time = object.find("time");

            tariffs tariff = tariffs(
                        currentPack->id(),
                        itr_cost.value().toInt(),
                        itr_valuta.value().toString(),
                        itr_time.value().toInt()
            );
            socket_write("Reply New Tariff", QJsonObject {
                             {"status", "successful"},
                             {"id", tariff.id()}
                         });

            QJsonObject request;
            get_subscribtions_doctor(my_email, request);
            socket_write("Updated Subscriptions", request);
        }
        else
            socket_write("Reply New Tariff", QJsonObject {{"status", "denied"}});
    }
    else if(header == "Update Tariff")
    {
        QJsonObject::iterator itr_tariff = body.find("Tariff");

        if(autorizated() && itr_tariff != body.end())
        {
            tariffs tariff = tariffs::createFromJson(itr_tariff.value().toObject());
            tariff.update();
            socket_write("Reply Update Tariff", QJsonObject {{"status", "successful"}});

            QJsonObject request;
            get_subscribtions_doctor(my_email, request);
            socket_write("Updated Subscriptions", request);
        }
        else
            socket_write("Reply Update Tariff", QJsonObject {{"status", "denied"}});
    }
    //-------------------------------------------------------------------------------------------------------------------------------
    else if(header == "Search Doctor")
    {
        QJsonObject::iterator itr_key = body.find("key");
        QJsonObject::iterator itr_specialization_id = body.find("specialization_id");

        if(autorizated() &&
                itr_key != body.end() &&
                itr_specialization_id != body.end())
        {
            QJsonObject reply;
            reply.insert("status", "successful");
            searchDoctors(itr_key.value().toString(), itr_specialization_id.value().toInt(), reply);
            socket_write("Reply Search Doctor", reply);
        }
        else
            socket_write("Reply Search Doctor", QJsonObject {{"status", "denied"}});
    }
    //-------------------------------------------------------------------------------------------------------------------------------
    else if(header == "New Payment PayPal")
    {
        QJsonObject::iterator itr_doctor_id = body.find("doctor_id");
        QJsonObject::iterator itr_patient_id = body.find("patient_id");
        QJsonObject::iterator itr_tariff_id = body.find("tariff_id");

        if(autorizated() &&
                itr_doctor_id != body.end() &&
                itr_patient_id != body.end() &&
                itr_tariff_id != body.end())
        {
            new_payment_PayPal(
                        itr_doctor_id.value().toInt(),
                        itr_patient_id.value().toInt(),
                        itr_tariff_id.value().toInt());
        }
        else
            socket_write("Reply Search Doctor", QJsonObject {{"status", "denied"}});
    }
    else if(header == "Cancel Payment PayPal")
    {
        QJsonObject::iterator itr_reason = body.find("reason");

        if(autorizated() && itr_reason != body.end())
        {
            payout_paypal_waiting = false;
            socket_write("Reply Cancel Payment PayPal", QJsonObject {{"status", "successful"}});
        }
        else
            socket_write("Reply Cancel Payment PayPal", QJsonObject {{"status", "denied"}});
    }
}

bool Client::checkPassword(Unpacker *unpacker)
{
    QString login, password;
    *unpacker >> login;
    *unpacker >> password;
    users user(login, false);
    if(user.password() != password)
        return false;
    else
        return true;
}

int Client::new_profile_base(QJsonObject profile)
{
    users user = users::createFromJson(profile.find("ProfileBase").value().toObject(), this, true);
    return user.id();
}

void Client::get_profile_base(QString login, QJsonObject& object)
{
    users user(login);
    object.insert("ProfileBase", user.toJson(this));
}

void Client::get_profile_base_limited(QString login, QJsonObject& object)
{
    users user(login);
    object.insert("ProfileBase", user.toJsonLimited(this));
}

int Client::new_profile_doctor(QJsonObject profile)
{
    doctors doctor = doctors::createFromJson(profile.find("ProfileDoctor").value().toObject(), true);
    return doctor.id();
}

void Client::get_profile_doctor(QString login, QJsonObject& object)
{
    doctors doctor(login);
    object.insert("ProfileDoctor", doctor.toJson());
}

void Client::get_profile_doctor_limited(QString login, QJsonObject& object)
{
    doctors doctor(login);
    object.insert("ProfileDoctor", doctor.toJsonLimited());
}

void Client::get_subscribtions_doctor(QString login, QJsonObject &object)
{
    QJsonArray array;
    doctors doctor(login);
    QMultiMap <int, packages*> packs = packages::findPackages(doctor.id());
    for(int specialization_id : packs.uniqueKeys())
    {
        specializations specialization(specialization_id);
        QJsonObject object_specialization
        {
            {"specialization", specialization.toJson()}
        };
        QJsonArray array_packages;
        QList <packages*> list_packs = packs.values(specialization_id);
        for(auto current_package : list_packs)
        {
            QJsonObject object_package
            {
                {"id", current_package->id()},
                {"duration", current_package->interval()}
            };
            QJsonArray array_tariffs;
            QList <tariffs*> list_tariffs = tariffs::findTariffs(current_package->id());
            for(auto current_tariff : list_tariffs)
            {
                array_tariffs.append(current_tariff->toJson());
            }
            object_package.insert("tariffs", array_tariffs);
            array_packages.append(object_package);
        }
        object_specialization.insert("packages", array_packages);
        array.append(object_specialization);
    }
    object.insert("Subscriptions", array);
}

void Client::get_comments_doctor(QString login, QJsonObject &object)
{
    QJsonArray array;
    doctors doctor(login);
    QList <comments*> doctor_comments = comments::findCommentsByDoctor(doctor.id());
    for(auto comment : doctor_comments)
        array.append(comment->toJsonForDoctor(this));
    object.insert("Comments", array);
}

void Client::get_profile_patient(QString login, QJsonObject& object)
{
    patients patient(login, true);
    object.insert("ProfilePatient", patient.toJson());
}

void Client::get_profile_patient_limited(QString login, QJsonObject &object)
{
    patients patient(login, true);
    object.insert("ProfilePatient", patient.toJsonLimited());
}

void Client::get_subscribtions_patient(QString login, QJsonObject &object)
{
    QJsonArray array;
    patients patient(login, true);
    QList <subscriptions*> subs = subscriptions::findSubscriptionsToPatient(patient.id());
    for(auto subscription : subs)
        array.append(subscription->toJson());
    object.insert("Subscriptions", array);
}

int Client::new_profile_patient(QJsonObject profile)
{
    patients patient = patients::createFromJson(profile.find("ProfilePatient").value().toObject(), true);
    return patient.id();
}

void Client::get_dialogList(int user_id, int mode, QJsonObject& object)
{
    QJsonArray arr_dialogs;
    QVector <dialogs*> dialogList = dialogs::findDialogs(user_id, mode == 1);
    for(auto dialog : dialogList)
        arr_dialogs.append(dialog->toJson(this, user_id));
    object.insert("DialogList", arr_dialogs);
}

void Client::get_dialogMessages(int dialog_id, QJsonObject& object)
{
    QJsonArray arr_dialogs;
    QList <messages*> messagesList = messages::findMessages(dialog_id);
    for(auto message : messagesList)
        arr_dialogs.append(message->toJson(this));
    object.insert("Messages", arr_dialogs);
}

dialogs &Client::new_dialog(int user1_id, int user2_id, int user1_mode, int user2_mode)
{
    dialogs *dialog = new dialogs(-1,
                       user1_id,
                       user2_id,
                       user1_mode,
                       user2_mode,
                       false,
                       false
    );

    QJsonObject request;
    get_dialogList(user1_id, user1_mode, request);
    socket_write("Updated Dialogs", request);
    return *dialog;
}

void Client::get_available_specializations(QJsonObject &object)
{
    QJsonArray array;
    QList <specializations*> specializationList = specializations::loadAll();
    for(auto specialization : specializationList)
        array.append(specialization->toJson());
    object.insert("Specializations", array);
}

void Client::get_available_valutas(QJsonObject &object)
{
    QJsonArray array
    {
        QJsonObject
        {
            {"name", "Рубли"},
            {"abbreviation", "руб"},
            {"symbol", "Р"}
        },
        QJsonObject
        {
            {"name", "Доллары"},
            {"abbreviation", "долл"},
            {"symbol", "$"}
        }
    };
    object.insert("Valutes", array);
}

void Client::searchDoctors(QString key, int specialization_id, QJsonObject &object)
{
    QJsonArray array;
    QList <doctors*> docs = doctors::findDoctors(key, specialization_id);
    for(auto doctor : docs)
    {
        QJsonObject result;
        QList <int> specializations_id = packages::findPackages(doctor->id()).uniqueKeys();
        QJsonArray specs;
        for(auto spec_id: specializations_id)
            specs.append(specializations(spec_id).toJson());

        result.insert("Profile", users(doctor->user_id()).toJson(this));
        result.insert("Specializations", specs);
        result.insert("Rating", doctor->rating());
        array.append(result);
    }
    object.insert("Doctors", array);
}

void Client::runScript_payout_paypal_create(Payout_PayPal& payout)
{
    QString command = "php script_payout_paypal_1.php %1 %2 %3 %4 %5";
    command =  command.arg(payout.login)
                      .arg(payout.password)
                      .arg(payout.valuta)
                      .arg(QString::number(payout.cost))
                      .arg(QString::number(payout.iser_patient_id));
    system(command.toStdString().c_str());


    if(QFile::exists(payout.file_name))
    {
        QFile file(payout.file_name);
        if(file.open(QIODevice::ReadOnly))
        {
            payout.token = file.readLine();
            payout.token.remove(payout.token.size() - 1, 1);
            payout.payment_id = file.readLine();
            payout.payment_id.remove(payout.payment_id.size() - 1, 1);
            payout.link_approve = file.readLine();
            payout.link_approve.remove(payout.link_approve.size() - 1, 1);
        }
        file.close();
    }
}

bool Client::runScript_payout_paypal_update(Payout_PayPal& payout)
{
    QString command = "php script_payout_paypal_2.php %1 %2 %3";
    command =  command.arg(payout.token)
                      .arg(payout.payment_id)
                      .arg(QString::number(payout.iser_patient_id));
    system(command.toStdString().c_str());

    QString result;
    if(QFile::exists(payout.file_name))
    {
        QFile file(payout.file_name);
        if(file.open(QIODevice::ReadOnly))
            result = file.readAll();
        file.close();
    }
    if(result == "APPROVED")
        return true;
    else {
        return false;
    }
}

bool Client::runScript_payout_paypal_capture(Payout_PayPal &payout)
{
    QString command = "php script_payout_paypal_3.php %1 %2 %3";
    command =  command.arg(payout.token)
                      .arg(payout.payment_id)
                      .arg(QString::number(payout.iser_patient_id));
    system(command.toStdString().c_str());

    QString result;
    if(QFile::exists(payout.file_name))
    {
        QFile file(payout.file_name);
        if(file.open(QIODevice::ReadOnly))
            result = file.readAll();
        file.close();
        file.remove();
    }

    if(result == "COMPLETED")
        return true;
    else
        return false;
}

void Client::new_payment_PayPal(int user_doctor_id, int user_patient_id, int tariff_id)
{
    tariffs tariff(tariff_id);
    Payout_PayPal payout(
                "Aa76WqBVOPtSu21aVR1UKkvZJJkTThZCe06XsBu_W8iQr6ypM3b4Acshh6nRx_LOUYjOijnn2fwHxh8A",
                "EFAkayHZip25tGrabslsXss-3asQ2MDxMJJryaseXBVO00ILPhGosXkRnDPYcK8-RvI4YprxlunG5FmK",
                tariff,
                user_doctor_id,
                user_patient_id
                );

    runScript_payout_paypal_create(payout);

    QJsonObject reply
    {
        {"status", "successful"},
        {"link", payout.link_approve}
    };
    socket_write("Reply New Payment PayPal", reply);

    payout_paypal_waiting = true;
    int count = 60;
    while(payout_paypal_waiting)
    {
        if(runScript_payout_paypal_update(payout))
        {
            if(runScript_payout_paypal_capture(payout))
            {
                patients patient(users(user_patient_id).id());
                doctors doctor(users(user_doctor_id).id());
                tariffs tariff(payout.tariff_id);
                packages package(tariff.package_id(), false);
                specializations specialization(package.specialization_id(), false);
                QDateTime timenow = QDateTime::currentDateTime();
                subscriptions new_sub(patient.id(), doctor.id(), specialization.id(), package.interval(), tariff.cost(), tariff.valuta(), tariff.time(), timenow, timenow.addSecs(60 * 60 * package.interval()));
                dialogs new_dialog(specialization.id(), user_doctor_id, user_patient_id, true, false, false, false);

                socket_write("Payment PayPal Complete", QJsonObject {{"status", "successful"}});
            }
            else
                socket_write("Payment PayPal Complete", QJsonObject {{"status", "denied"}});
        }
        else
        {
            count--;
            if(count < 1)
                payout_paypal_waiting = false;
            QCoreApplication::processEvents();
            QThread::msleep(1000);
        }
    }
}


QByteArray Client::getEnclosure(QString header)
{
    QMap<QString, QByteArray>::iterator iterator = array_enclosures.find(header);
    if(iterator != array_enclosures.end())
    {
        QByteArray result = iterator.value();
        array_enclosures.remove(header);
        return result;
    }
    else
        return nullptr;
}

void Client::clearBlock()
{
    nextBlock.clear();
    nextBlockSize = 0;
    nextBlockType = 0;
}

void Client::socket_read()
{
    QDataStream stream(my_socket);
    stream.setVersion(QDataStream::Qt_5_12);

    while(my_socket->bytesAvailable() != 0)
    {
        if(nextBlockSize == 0)
        {
            if(my_socket->bytesAvailable() >= 9)
            {
                char prefix[4];
                char key[4] = {0x012, 0x023, 0x034, 0x045};
                do
                {
                    my_socket->read(prefix, 1);
                    if(prefix[0] == key[0])
                    {
                        my_socket->read(&prefix[1], 3);
                        if(prefix[1] == key[1] && prefix[2] == key[2] && prefix[3] == key[3])
                        {
                            char* buffer = new char[5];
                            my_socket->read(buffer, 5);

                            union {
                                char bytes[4];
                                int32_t value;
                            } integer;

                            memcpy(&integer.bytes[3], buffer, 1);
                            memcpy(&integer.bytes[2], buffer + 1, 1);
                            memcpy(&integer.bytes[1], buffer + 2, 1);
                            memcpy(&integer.bytes[0], buffer + 3, 1);
                            memcpy(&nextBlockType, buffer + 4, 1);
                            nextBlockSize = integer.value;
                            delete [] buffer;
                            break;
                        }
                    }
                } while(my_socket->bytesAvailable() >= 9);
            }
            else
                return;
        }

        int count = 0;
        while(nextBlock.size() < nextBlockSize)
        {
            if(my_socket->bytesAvailable() == 0)
            {
                count++;
                if(count >= 10)
                {
                    clearBlock();
                    return;
                }
                else
                    continue;
            }
            else
                count = 0;

            int length = my_socket->bytesAvailable();
            if(length + nextBlock.size() > nextBlockSize)
                length = nextBlockSize - nextBlock.size();
            char* newBlock = new char[length];
            my_socket->read(newBlock, length);
            nextBlock.append(newBlock, length);

            delete [] newBlock;
            if(nextBlock.size() != nextBlockSize)
            {
                QCoreApplication::processEvents();
                QThread::msleep(200);
            }
        }

        if(nextBlockType == 0x001)
        {
            QJsonObject request = QJsonDocument::fromJson(nextBlock).object();
            query(request);
        }
        else if(nextBlockType == 0x002)
        {
            nextBlock += '\0';
            QByteArray header;
            QByteArray body(nextBlock);
            int blockSize = nextBlock.size();
            QDataStream stream(&nextBlock, QIODevice::ReadOnly);
            stream >> header;
            stream >> body;
            array_enclosures.insert(QString::fromUtf8(header), body);
        }
        clearBlock();
    }
}

void Client::socket_write(QString header, QJsonObject body)
{
    DEBUG_LOG(my_adress_full + ":OUTPUT: "  + header)
    QJsonObject object
    {
        {"header", header},
        {"body", body}
    };

    //QThread::sleep(1);
    emit write_to_socket(my_socket, object);

    for(auto enclosure : array_output_enclosures)
    {
        //QThread::msleep(1000);
        emit write_to_socket(my_socket, enclosure);
    }
    array_output_enclosures.clear();

    for(auto enclosure : array_output_enclosure_paths)
    {
        //QThread::msleep(1000);
        emit write_to_socket(socket()->peerAddress().toString(), enclosure.header, enclosure.path);
    }
    array_output_enclosure_paths.clear();
}

void Client::socket_write(QString header, QString path)
{
    Enclosure enclosure(header, path);
    array_output_enclosure_paths.append(enclosure);
}

void Client::socket_write(QString header, QByteArray enclosure)
{
    QByteArray output;
    QDataStream stream(&output, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_5_12);

    if(enclosure.isEmpty())
        enclosure = "n";

    stream << header.toUtf8();
    stream << enclosure;

    array_output_enclosures.append(output);
    //emit write_to_socket(my_socket, output);
}

void Client::socket_write(QString _email, QString header, QJsonObject body)
{
    if(_email == my_email)
        socket_write(header, body);
}

void Client::socket_disconnected()
{
    emit disconnect_from_socket();
}
