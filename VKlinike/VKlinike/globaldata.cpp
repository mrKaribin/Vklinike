#include "globaldata.h"
#include "mainwidget.h"
#include "socket.h"

#include <QtGlobal>
#include <QStandardPaths>


namespace GlobalData
{
    namespace strings
    {
        namespace database
        {
            QString             DATABASE_CREATE                 = "CREATE DATABASE %1;";
            QString             DATABASE_SELECT                 = "SELECT %1 FROM %2;";
            QString             DATABASE_INSERT                 = "INSERT INTO %1 VALUES (%2);";
            QString             DATABASE_UPDATE                 = "UPDATE %1 FROM %2 WHERE %3;";
            QString             DATABASE_DELETE                 = "DELETE FROM %2;";
        }
        namespace error
        {
            QString             database_header                 = "Ошибка базы данных";
            QString             database_cantOpen               = "Не удалось открыть базу данных";
            QString             database_cantRead               = "Не удалось чтение базы данных";
            QString             database_cantWrite              = "Не удалась запись базы данных";
        }

        QMap <SubscriptionType, QString>                        subscriptionTypeNames;
        QMap <SubscriptionType, QString>                        subscriptionTypeDurations;
        QMap <SubscriptionType, int>                            subscriptionTypeValue;
    }
    namespace directory
    {
        namespace icons
        {
            QString             profile                         = "profile.png",
                                profile_active                  = "profile_active.png",
                                messages                        = "messages.png",
                                messages_active                 = "messages_active.png",
                                search                          = "search.png",
                                search_active                   = "search_active.png",
                                preferences                     = "prefs.png";

            QString             clock                           = "clock.png";
            QString             money                           = "money.png";

            QString             star                            = "star.png",
                                gold_star                       = "gold_star.png";

            QString             expand                          = "expand.png";
            QString             turn                            = "turn.png";
            QString             affix                           = "affix.png";
            QString             back                            = "back.png";
            QString             call_audio                      = "call_audio.png";
            QString             call_video                      = "call_video.png";
            QString             check                           = "check.png";
            QString             check_double                    = "check_double.png";
            QString             loading                         = "loading.png";
            QString             unread                          = "unread.png";
            QString             send                            = "send.png";
            QString             photo                           = "photo.png";
            QString             video                           = "video.png";
            QString             document                        = "document.png";
            QString             settings                        = "settings.png";
            QString             cross                           = "cross.png";

            QString             search_patient                  = "search_patient.png";
        }
        namespace images
        {
            QString             patient                         = "null_patient.png";
            QString             doctor                          = "null_doctor.png";
        }

        QString                 path                            = "";
        QString                 syspath                         = QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0];
        QString                 image                           = "";
        QString                 icon                            = "";
        QString                 attachment                      = "";
    }
    namespace query
    {
        QString                 prefix_reply                    = "Reply:";
        QString                 prefix_get                      = "Get_";
        QString                 prefix_set                      = "Set_";
        QString                 prefix_new                      = "New_";
        QString                 prefix_update                   = "Update_";
        QString                 prefix_find                     = "Find_";
        QString                 prefix_remove                   = "Remove_";

        QString                 postfix_guest                    = "_Guest";

        QString                 autorization                    = "Autorization";
        QString                 profile_base                    = "BaseProfile";
        QString                 profile_doctor                  = "DoctorProfile";
        QString                 profile_doctor_tariff           = "DoctorProfileTariff";
        QString                 profile_patient                 = "PatientProfile";
        QString                 dialogs                         = "DialogsPreview";
        QString                 dialog                          = "Dialog";
        QString                 message                         = "Message";
        QString                 message_attachment              = "MessageAttachment";
        QString                 card                            = "Card";
        QString                 specializations                 = "Specializations";
        QString                 list_doctor                     = "ListDoctor";
        QString                 datas                           = "Datas";
        QString                 data_icon                       = "DataIcon";
        QString                 data_image                      = "DataImage";
        QString                 payment_paypal                  = "PaymentPayPal";
        QString                 payment_complete                = "PaymentComplete";
        QString                 redirection_web                 = "RedirectionWeb";

        QString                 confirmation                    = "CONFIRMATION";
        QString                 negation                        = "NEGATION";
    }
    namespace interface
    {
        namespace color
        {
            QColor              lightBlue                       (224, 255, 255);
            QColor              blue                            (66, 170, 255);
            QColor              lightRed                        (255, 100, 115);
            QColor              red                             (255, 0, 0);
            QColor              gray                            (200, 200, 200);
            QColor              black                           (0, 0, 0);
        }
        QEasingCurve            animation_curve                 = QEasingCurve::OutExpo;
        int                     animation_duration              = 1000,

                                indent,
                                indent_medium,
                                indent_small,
                                spacing,


                                row_size,
                                text_size,
                                photo_size,

                                menuBar_height;
    }
    namespace screen
    {
        QScreen*                screen;
        QRect                   geometry;
        int                     geometry_statusBar_height;
        int                     geometry_shortSide;
        int                     geometry_longSide;

    }


    Mode                        currentMode                             = Mode_Patient;
    Valuta                      currentValuta("Рубль", "руб", "rub");
    QString                     currentName;
    QString                     currentLogin                            = "";
    QString                     currentPassword                         = "";

    MainWidget*                 widget_main                             = nullptr;
    Widget*                     widget_mainArea                         = nullptr;

    QSqlDatabase               *database;
    QString                     database_password                       = "database_pass";
    QList <Valuta>              valutes;

    Socket                     *socket;
    QString                     server_host                             = "93.81.248.7"; // "192.168.1.34" "vklinike.ddnsking.com"
    quint16                     server_port                             = 10228;
    wchar_t                     separator                               = L'֎';


    void initialize()
    {
        QString test = directory::syspath;
        screen::screen = QApplication::screens().at(0);
#ifdef Q_OS_WIN
        screen::geometry = QRect(0, 0, 720/2, 1280/2);

        directory::path = "C:\\Projects\\Qt_Projects\\VKlinike\\VKlinike\\Files";
        directory::image = directory::path + "\\Picture\\";
        directory::icon = directory::path + "\\Icon\\";
#endif
#ifdef Q_OS_ANDROID
        screen::geometry = screen::screen->virtualGeometry();

        directory::path = "/storage/emulated/0/Android/obb/vklinike.v1-0";
        directory::image = directory::path + "/Picture/";
        directory::icon = directory::path + "/Icon/";
        directory::attachment = directory::path + "/Attachment/";
#endif
        screen::geometry_shortSide = (screen::geometry.width() > screen::geometry.height()) ? (screen::geometry.height()) : (screen::geometry.width());
        screen::geometry_longSide = (screen::geometry.width() > screen::geometry.height()) ? (screen::geometry.width()) : (screen::geometry.height());
        screen::geometry_statusBar_height = 70;
        screen::geometry.setHeight(screen::geometry.height() - screen::geometry_statusBar_height);
        interface::indent = screen::geometry_shortSide * 0.02;
        interface::indent_medium = interface::indent * 3;
        interface::indent_small = interface::indent / 2;
        interface::spacing = screen::geometry_shortSide * 0.05;
        interface::row_size = screen::geometry.height() * 0.03;
        interface::text_size = screen::geometry.height() * 0.025;
        interface::photo_size = screen::geometry_shortSide / 3 - interface::indent_medium * 2;
        interface::menuBar_height = screen::geometry.height() * 0.07;

        strings::subscriptionTypeNames.insert(Subscription_Day, "Дневная");
        strings::subscriptionTypeNames.insert(Subscription_Week, "Недельная");
        strings::subscriptionTypeNames.insert(Subscription_Month, "Месячная");

        strings::subscriptionTypeDurations.insert(Subscription_Day, "день");
        strings::subscriptionTypeDurations.insert(Subscription_Week, "неделя");
        strings::subscriptionTypeDurations.insert(Subscription_Month, "месяц");

        strings::subscriptionTypeValue.insert(Subscription_Day, 24);
        strings::subscriptionTypeValue.insert(Subscription_Week, 24 * 7);
        strings::subscriptionTypeValue.insert(Subscription_Month, 24 * 30);

        valutes << Valuta("Рубль", "руб", "rub");

    }

    void connectToServer()
    {
        socket = new Socket();
    }

    inline void checkFile(QString type, QString name)
    {
        using namespace GlobalData;
        QString adress;
        if(type == "icon")
            adress += directory::icon;
        if(type == "image")
            adress += directory::image;
        adress += name;
        if(!QFile::exists(adress))
        {

        }
    }

    void checkContent()
    {

    }

    void error_Critical(QString _header, QString _message)
    {
        QMessageBox::critical(widget_main, _header, _message);
        QApplication::instance()->quit();
    }

    void error_Show(QString _header, QString _message)
    {
        QMessageBox::critical(widget_main, _header, _message);
    }

    void database_Open()
    {
        database = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
        database->setDatabaseName("VKLINIKE_DB");
        database->setUserName("user");
        database->setHostName("local");
        database->setPassword(database_password);
        database->setPort(3300);
        if(!database->open())
            error_Critical(strings::error::database_header, strings::error::database_cantOpen);
        database_Check();
    }

    void database_Check()
    {
        using namespace strings::database;
        using namespace strings::error;

        bool table_main = false;
        QStringList list = database->tables();

        foreach(auto l, list)
        {
            if(l == "service") table_main = true;
        }

        if(!table_main)
        {
            QSqlQuery query;
            if(!query.exec("CREATE TABLE service (name TEXT UNIQUE NOT NULL, data TEXT NOT NULL);"))
                error_Show(database_header, "Не удалось создать таблицу service");
        }
    }

    void database_Read()
    {
        using namespace strings::database;
        using namespace strings::error;
        QSqlQuery query; QSqlRecord record;

        QString str = DATABASE_SELECT.arg("*")
                                     .arg("service");
        if(!query.exec(str)) error_Show(database_header, database_cantRead);

        record = query.record();
        while(query.next())
        {
            QString name = query.value(record.indexOf("name")).toString();
            if(name == "mode")
                currentMode = (Mode) query.value(record.indexOf("data")).toString().toInt();
            if(name == "login")
                currentLogin = query.value(record.indexOf("data")).toString();
            if(name == "password")
                currentPassword = query.value(record.indexOf("data")).toString();
        }
    }

    void database_write_service(QString name, QString data)
    {
        using namespace strings::database;
        using namespace strings::error;
        QSqlQuery query;
        QString str = "INSERT INTO service (name, data) VALUES ('" + name + "', '" + data + "');";
        if(!query.exec(str))
            error_Show(database_header, database_cantWrite);
    }

    void database_Write()
    {
        using namespace strings::database;
        using namespace strings::error;
        QSqlQuery query;

        QString str = DATABASE_DELETE.arg("service");
        if(!query.exec(str))
            error_Show(database_header, database_cantWrite);

        database_write_service("mode", QString::number((int) currentMode));
        if(currentLogin != "")
            database_write_service("login", currentLogin);
        if(currentPassword != "")
            database_write_service("password", currentPassword);
    }


    void customization_BottomLayer()
    {

    }
};
