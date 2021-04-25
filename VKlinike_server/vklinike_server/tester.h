#ifndef TESTER_H
#define TESTER_H

#include "global.h"
#include "Datas/users.h"
#include "Datas/doctors.h"
#include "Datas/patients.h"
#include "Datas/specializations.h"
#include "Datas/packages.h"
#include "Datas/tariffs.h"
#include "Datas/comments.h"
#include "Datas/subscriptions.h"
#include "Datas/dialogs.h"
#include "Datas/messages.h"
#include "Datas/cards.h"

#include <QObject>


class Tester
{
public:
    Tester();

    void users_full();
    void doctors_full();
    void patients_full();
    void specializations_full();
    void packages_full();
    void tariffs_full();
    void comments_full();
    void subscriptions_full();
    void dialogs_full();
    void messages_full();
};

#endif // TESTER_H
