#ifndef AUTORAZATIONWIDGET_H
#define AUTORAZATIONWIDGET_H

#include "widget.h"
#include "button.h"
#include "BaseProfile/baseprofiledata.h"

#include <QLineEdit>

class AutorazationWidget : public Widget
{
    Q_OBJECT
public:
    AutorazationWidget(Widget* _parent);

private:
    QLabel                     *status;
    QLineEdit                  *my_login;
    QLineEdit                  *my_password;
    Button                     *my_autorization;
    Button                     *my_registration;

public slots:
    void                        regisatration();
    void                        registrated(BaseProfileData);
    void                        autorization();
    void                        denied();

signals:
    void autorization_request(QString login, QString password);
};

#endif // AUTORAZATIONWIDGET_H
