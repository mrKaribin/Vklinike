#include "updater.h"
#include "packer.h"


Updater::Updater()
{
    //QThread *new_thread = new QThread();
    //new_thread->start();
    //moveToThread(new_thread);
}

bool Updater::checkFile(QString type, QString name, bool loading)
{
    using namespace GlobalData;
    using namespace GlobalData::query;
    QString adress;
    if(type == data_icon)
        adress += directory::icon;
    if(type == data_image)
        adress += directory::image;
    adress += name;
    if(!QFile::exists(adress))
    {
        if(loading)
        {
            Packer packer;
            packer << type;
            packer << name;
            server_request(prefix_get + datas, packer.result());
            server_waitForReply(prefix_reply + prefix_get + datas);
        }
        return false;
    }
    return true;
}

void Updater::checkContent()
{
    using namespace GlobalData::query;
    using namespace GlobalData::directory;
    bool loading = true, ready = true;

    if(!QDir(path).exists())
    {
        QDir().mkdir(path);
        if(!QDir(path).exists())
            GlobalData::error_Critical("Уведомление", "Пожалуйста, предоставьте приложению разрешение на чтение и редактирование данных.");
    }
    if(!QDir(icon).exists())
        QDir().mkdir(icon);
    if(!QDir(image).exists())
        QDir().mkdir(image);
    if(!QDir(attachment).exists())
        QDir().mkdir(attachment);

    do
    {
        ready = true;
        ready *= checkFile(data_icon, icons::profile, loading);
        ready *= checkFile(data_icon, icons::profile_active, loading);
        ready *= checkFile(data_icon, icons::messages, loading);
        ready *= checkFile(data_icon, icons::messages_active, loading);
        ready *= checkFile(data_icon, icons::search, loading);
        ready *= checkFile(data_icon, icons::search_active, loading);
        ready *= checkFile(data_icon, icons::preferences, loading);
        ready *= checkFile(data_icon, icons::clock, loading);
        ready *= checkFile(data_icon, icons::money, loading);
        ready *= checkFile(data_icon, icons::star, loading);
        ready *= checkFile(data_icon, icons::gold_star, loading);
        ready *= checkFile(data_icon, icons::expand, loading);
        ready *= checkFile(data_icon, icons::turn, loading);
        ready *= checkFile(data_icon, icons::affix, loading);
        ready *= checkFile(data_icon, icons::back, loading);
        ready *= checkFile(data_icon, icons::call_audio, loading);
        ready *= checkFile(data_icon, icons::call_video, loading);
        ready *= checkFile(data_icon, icons::check, loading);
        ready *= checkFile(data_icon, icons::check_double, loading);
        ready *= checkFile(data_icon, icons::loading, loading);
        ready *= checkFile(data_icon, icons::unread, loading);
        ready *= checkFile(data_icon, icons::send, loading);
        ready *= checkFile(data_icon, icons::photo, loading);
        ready *= checkFile(data_icon, icons::video, loading);
        ready *= checkFile(data_icon, icons::document, loading);
        ready *= checkFile(data_icon, icons::settings, loading);
        ready *= checkFile(data_icon, icons::cross, loading);
        ready *= checkFile(data_icon, icons::search_patient, loading);

        ready *= checkFile(data_image, images::doctor, loading);
        ready *= checkFile(data_image, images::patient, loading);
        loading = false;
        QApplication::processEvents();
    }
    while(!ready);
}

void Updater::server_reply(QString header, QByteArray body)
{
    using namespace GlobalData::query;
    if(header == prefix_reply + prefix_get + datas)
        loadData_File(body);
}

void Updater::loadData_File(QByteArray array)
{
    using namespace GlobalData;
    using namespace GlobalData::query;
    QString type, name, adress;
    QByteArray data;
    Unpacker unpacker(array);
    unpacker >> type;
    unpacker >> name;
    unpacker >> data;

    if(type == data_icon)
        adress += directory::icon;
    if(type == data_image)
        adress += directory::image;
    adress += name;
    QFile file(adress);
    if(!file.open(QIODevice::WriteOnly))
        GlobalData::error_Show("Загрузка данных", "Не удалось сохранить необходимые данные!");
    file.write(data);
    file.close();
}
