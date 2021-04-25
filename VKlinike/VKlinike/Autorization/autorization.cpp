#include "autorization.h"
#include "packer.h"
#include "mainwidget.h"

#include <QThread>


Autorization::Autorization(Widget *_widget_parent)
{
    using namespace GlobalData;
    my_widget_parent = _widget_parent;
    if(currentLogin == "" || currentPassword == "")
        Autorization_initialize();
    else
        autorization(currentLogin, currentPassword);
    QThread*_object_thread = new QThread();
    _object_thread->start();
    moveToThread(_object_thread);
}

void Autorization::Autorization_initialize()
{
    my_widget = new AutorazationWidget(my_widget_parent);
    GlobalData::widget_main->widgets_Swift(widget(), MainWidget::Swift_toTop);

    connect(my_widget, &AutorazationWidget::autorization_request, this, &Autorization::autorization);
    connect(this, &Autorization::denied, my_widget, &AutorazationWidget::denied);
}

AutorazationWidget* Autorization::widget()
{
    return my_widget;
}

void Autorization::autorization(QString login, QString password)
{
    my_login = login;
    my_password = password;
    Packer packer;
    packer << login;
    packer << password;
    server_request(GlobalData::query::autorization, packer.result());
}

void Autorization::server_reply(QString header, QByteArray body)
{
    if(header == GlobalData::query::prefix_reply + GlobalData::query::autorization)
        readFromBytes(body);
}

void Autorization::readFromBytes(QByteArray array)
{
    using namespace GlobalData::query;
    QString reply = QString::fromUtf8(array);
    if(reply == confirmation)
    {
        GlobalData::currentLogin = my_login;
        GlobalData::currentPassword = my_password;
        QTimer::singleShot(1000, this, &Autorization::deleteLater);
        QTimer::singleShot(1000, my_widget, &AutorazationWidget::deleteLater);
        emit confirmed();
    }
    else if(reply == negation)
    {
        if(my_widget == nullptr)
        {
            GlobalData::currentLogin = "";
            GlobalData::currentPassword = "";
            Autorization_initialize();
        }
        emit denied();
    }
}
