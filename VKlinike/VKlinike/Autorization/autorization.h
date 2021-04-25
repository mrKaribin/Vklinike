#ifndef AUTORIZATION_H
#define AUTORIZATION_H

#include "object.h"
#include "autorazationwidget.h"


class Autorization : public Object
{
    Q_OBJECT
public:
    Autorization(Widget *_widget_parent = nullptr);
    void Autorization_initialize();

    AutorazationWidget*         widget();

private:
    Widget                     *my_widget_parent;
    AutorazationWidget         *my_widget               = nullptr;
    QString                     my_login;
    QString                     my_password;

public slots:
    void                        server_reply(QString header, QByteArray body) override;
    void                        readFromBytes(QByteArray array);

    void                        autorization(QString login, QString password);

signals:
    void confirmed();
    void denied();
};

#endif // AUTORIZATION_H
