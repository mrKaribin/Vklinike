#include "tester.h"

#include <QFile>


Tester::Tester()
{

}

void Tester::users_full()
{
    using namespace GLOBAL;
    QString photo_adress = "C:\\Projects\\Qt_Projects\\VKlinike_server\\build-vklinike_server-Desktop_Qt_5_12_3_MinGW_32_bit-Debug\\null_doctor.png";
    QByteArray array;
    QFile file;
    console_write("Тестирование таблицы 'users'.");
    console_indent++;

    console_write("Сохраняю данные:", true);
    file.setFileName(photo_adress);
    if(file.open(QIODevice::ReadOnly)) array = file.readAll();
    file.close();
    users* user = new users(array, QByteArray(), "Демьян", "Карибин", "Александрович", true, QDate(2000, 5, 20), "dema.marfida@gmail.com", "+79312699523", "dema2000");
    int id = user->id();
    console_write(QString::number(user->id()) + " " + user->photo_adress() + " " + user->surname() + " " + user->name() + " " + user->patronimic() + " " + bool_to_QString(user->sex()) + " " + user->birthday().toString() + " " + user->email() + " " + user->phone() + " " + user->password());
    delete (user);

    console_write("Считываю данные по полю 'email' (full_initialize = true):", true);
    user = new users("dema.marfida@gmail.com");
    console_write(QString::number(user->id()) + " " + user->photo_adress() + " " + user->surname() + " " + user->name() + " " + user->patronimic() + " " + bool_to_QString(user->sex()) + " " + user->birthday().toString() + " " + user->email() + " " + user->phone() + " " + user->password());
    delete (user);

    console_write("Считываю данные по полю 'id' (full_initialize = false):", true);
    user = new users(id, false);
    console_write(QString::number(user->id()) + " " + user->photo_adress() + " " + user->surname() + " " + user->name() + " " + user->patronimic() + " " + bool_to_QString(user->sex()) + " " + user->birthday().toString() + " " + user->email() + " " + user->phone() + " " + user->password());

    console_write("Частично изменяю и сохраняю данные:", true);
    user->setDatas(user->photo(), user->miniature(), user->name(), "Марфида", user->patronimic(), user->sex(), user->birthday(), "dema.marfida@yandex.ru", user->phone(), "dema2010");
    user->update();
    console_write(QString::number(user->id()) + " " + user->photo_adress() + " " + user->surname() + " " + user->name() + " " + user->patronimic() + " " + bool_to_QString(user->sex()) + " " + user->birthday().toString() + " " + user->email() + " " + user->phone() + " " + user->password());
    delete (user);

    console_write("Считываю обновленные данные:", true);
    user = new users(id, false);
    console_write(QString::number(user->id()) + " " + user->photo_adress() + " " + user->surname() + " " + user->name() + " " + user->patronimic() + " " + bool_to_QString(user->sex()) + " " + user->birthday().toString() + " " + user->email() + " " + user->phone() + " " + user->password());

    console_write("Полностью изменяю и сохраняю данные:", true);
    photo_adress = "C:\\Projects\\Qt_Projects\\VKlinike_server\\build-vklinike_server-Desktop_Qt_5_12_3_MinGW_32_bit-Debug\\null_patient.png";
    file.setFileName(photo_adress);
    array.clear();
    if(file.open(QIODevice::ReadOnly)) array = file.readAll();
    file.close();
    user->setDatas(array, QByteArray(), "Татьяна", "Чубарева", "Дмитриевна", false, QDate(2001, 10, 12), "chubareva12@mail.ru", "+79817961923", "taty2001");
    user->update();
    console_write(QString::number(user->id()) + " " + user->photo_adress() + " " + user->surname() + " " + user->name() + " " + user->patronimic() + " " + bool_to_QString(user->sex()) + " " + user->birthday().toString() + " " + user->email() + " " + user->phone() + " " + user->password());
    delete (user);

    console_write("Считываю обновленные данные:", true);
    user = new users(id, false);
    console_write(QString::number(user->id()) + " " + user->photo_adress() + " " + user->surname() + " " + user->name() + " " + user->patronimic() + " " + bool_to_QString(user->sex()) + " " + user->birthday().toString() + " " + user->email() + " " + user->phone() + " " + user->password());

    console_write("Тестирование таблицы успешно завершено. Удаляю данные.\n", true);
    user->remove();
    delete (user);
    console_indent--;
    DEBUG_PAUSE();
}

void Tester::doctors_full()
{
    using namespace GLOBAL;
    console_write("Тестирование таблицы 'doctors'.");
    console_indent++;

    console_write("Сохраняю данные:", true);
    users* user = new users(QByteArray(), QByteArray(), "Демьян", "Карибин", "Александрович", true, QDate(2000, 5, 20), "dema.marfida@gmail.com", "+79312699523", "dema2000");
    int user_id = user->id();
    doctors* doctor = new doctors(user_id, 3000, QTime(13, 0, 0), QTime(19, 0, 0), "Образование", "Место работы");
    int id = doctor->id();
    console_write(QString::number(doctor->id()) + " " + QString::number(doctor->user_id()) + " " + QString::number(doctor->interval()) + " " + doctor->workday_begin().toString() + " " + doctor->workday_end().toString() + " " + doctor->education() + " " + doctor->job());
    delete (doctor);

    console_write("Считываю данные по полю 'email' (full_initialize = true):", true);
    doctor = new doctors("dema.marfida@gmail.com");
    console_write(QString::number(doctor->id()) + " " + QString::number(doctor->user_id()) + " " + QString::number(doctor->interval()) + " " + doctor->workday_begin().toString() + " " + doctor->workday_end().toString() + " " + doctor->education() + " " + doctor->job());

    console_write("Изменяю и сохраняю данные:", true);
    doctor->setDatas(user_id, 5000, QTime(11, 30, 0), QTime(15, 30, 0), "Другое образование", "Другое место работы");
    doctor->update();
    console_write(QString::number(doctor->id()) + " " + QString::number(doctor->user_id()) + " " + QString::number(doctor->interval()) + " " + doctor->workday_begin().toString() + " " + doctor->workday_end().toString() + " " + doctor->education() + " " + doctor->job());
    delete (doctor);

    console_write("Считываю обновленные данные по полю 'id' (full_initialize = false):", true);
    doctor = new doctors(id, false);
    console_write(QString::number(doctor->id()) + " " + QString::number(doctor->user_id()) + " " + QString::number(doctor->interval()) + " " + doctor->workday_begin().toString() + " " + doctor->workday_end().toString() + " " + doctor->education() + " " + doctor->job());

    console_write("Тестирование таблицы успешно завершено. Удаляю данные.\n", true);
    doctor->remove();
    user->remove();
    delete (doctor);
    delete (user);

    console_indent--;
    DEBUG_PAUSE();
}

void Tester::patients_full()
{
    using namespace GLOBAL;
    console_write("Тестирование таблицы 'patients'.");
    console_indent++;

    console_write("Сохраняю данные:", true);
    users* user = new users(QByteArray(), QByteArray(), "Демьян", "Карибин", "Александрович", true, QDate(2000, 5, 20), "dema.marfida@gmail.com", "+79312699523", "dema2000");
    int user_id = user->id();
    patients* patient = new patients(user_id);
    int id = patient->id();
    console_write(QString::number(patient->id()) + " " + QString::number(patient->user_id()));
    delete (patient);

    console_write("Считываю данные по полю 'email' (full_initialize = true):", true);
    patient = new patients("dema.marfida@gmail.com", true);
    console_write(QString::number(patient->id()) + " " + QString::number(patient->user_id()));

    console_write("Изменяю и сохраняю данные:", true);
    patient->setDatas(user_id);
    patient->update();
    console_write(QString::number(patient->id()) + " " + QString::number(patient->user_id()));
    delete (patient);

    console_write("Считываю обновленные данные по полю 'id' (full_initialize = false):", true);
    patient = new patients(id, false);
    console_write(QString::number(patient->id()) + " " + QString::number(patient->user_id()));

    console_write("Тестирование таблицы успешно завершено. Удаляю данные.\n", true);
    patient->remove();
    user->remove();
    delete (patient);
    delete (user);

    console_indent--;
    DEBUG_PAUSE();
}

void Tester::specializations_full()
{
    using namespace GLOBAL;
    console_write("Тестирование таблицы 'specializations'.");
    console_indent++;

    console_write("Сохраняю данные:", true);
    specializations* spec = new specializations("Педиатрия", (QString)"Основной задачей педиатрии является сохранение или возвращение состояния здоровья ребёнку, позволяющее ему максимально полно реализовать свой врождённый потенциал жизни.");
    int id = spec->id();
    console_write(QString::number(spec->id()) + " " + spec->name() + " " + spec->info());
    delete (spec);

    console_write("Считываю данные по полю 'name' (full_initialize = true):", true);
    spec = new specializations("Педиатрия", true);
    console_write(QString::number(spec->id()) + " " + spec->name() + " " + spec->info());

    console_write("Изменяю и сохраняю данные:", true);
    spec->setDatas("Хирургия", "Область медицины, изучающая острые и хронические заболевания, которые лечатся при помощи хирургического метода.");
    spec->update();
    console_write(QString::number(spec->id()) + " " + spec->name() + " " + spec->info());
    delete (spec);

    console_write("Считываю обновленные данные по полю 'id' (full_initialize = false):", true);
    spec = new specializations(id, false);
    console_write(QString::number(spec->id()) + " " + spec->name() + " " + spec->info());

    console_write("Тестирование таблицы успешно завершено. Удаляю данные.\n", true);
    spec->remove();
    delete (spec);

    console_indent--;
    DEBUG_PAUSE();
}

void Tester::packages_full()
{
    using namespace GLOBAL;
    console_write("Тестирование таблицы 'packages'.");
    console_indent++;

    console_write("Сохраняю данные:", true);
    users* user = new users(QByteArray(), QByteArray(), "Демьян", "Карибин", "Александрович", true, QDate(2000, 5, 20), "dema.marfida@gmail.com", "+79312699523", "dema2000");
    doctors* doctor = new doctors(user->id(), 3000, QTime(13, 0, 0), QTime(19, 0, 0), "Образование", "Место работы");
    specializations* spec = new specializations("Хирургия", (QString)"Область медицины, изучающая острые и хронические заболевания, которые лечатся при помощи хирургического метода.");
    packages* package = new packages(doctor->id(), spec->id(), 24 * 7);
    int id = package->id();
    console_write(QString::number(package->id()) + " " + QString::number(package->doctor_id()) + " " + QString::number(package->specialization_id()) + " " + QString::number(package->interval()));
    delete (package);

    console_write("Считываю данные по полю 'id' (full_initialize = true):", true);
    package = new packages(id, true);
    console_write(QString::number(package->id()) + " " + QString::number(package->doctor_id()) + " " + QString::number(package->specialization_id()) + " " + QString::number(package->interval()));

    console_write("Изменяю и сохраняю данные:", true);
    package->setDatas(package->doctor_id(), package->specialization_id(), 24 * 30);
    package->update();
    console_write(QString::number(package->id()) + " " + QString::number(package->doctor_id()) + " " + QString::number(package->specialization_id()) + " " + QString::number(package->interval()));
    delete (package);

    console_write("Считываю обновленные данные по полю 'id' (full_initialize = false):", true);
    package = new packages(id, false);
    console_write(QString::number(package->id()) + " " + QString::number(package->doctor_id()) + " " + QString::number(package->specialization_id()) + " " + QString::number(package->interval()));

    console_write("Создаю еще две строки в таблице:", true);
    packages* package2 = new packages(doctor->id(), spec->id(), 24);
    int id2 = package2->id();
    packages* package3 = new packages(doctor->id(), spec->id(), 24 * 7);
    int id3 = package3->id();
    console_write(QString::number(package2->id()) + " " + QString::number(package2->doctor_id()) + " " + QString::number(package2->specialization_id()) + " " + QString::number(package2->interval()));
    console_write(QString::number(package3->id()) + " " + QString::number(package3->doctor_id()) + " " + QString::number(package3->specialization_id()) + " " + QString::number(package3->interval()));

    console_write("Считываю все строки по полю 'doctor_id':", true);
    QMultiMap <int, packages*> tariffs = packages::findPackages(doctor->id());
    foreach(auto tariff, tariffs)
        console_write(QString::number(tariff->id()) + " " + QString::number(tariff->doctor_id()) + " " + QString::number(tariff->specialization_id()) + " " + QString::number(tariff->interval()));

    console_write("Тестирование таблицы успешно завершено. Удаляю данные.\n", true);
    package->remove();
    package2->remove();
    package3->remove();
    spec->remove();
    doctor->remove();
    user->remove();

    delete (package);
    delete (package2);
    delete (package3);
    delete (spec);
    delete (doctor);
    delete (user);
    console_indent--;
    DEBUG_PAUSE();
}

void Tester::tariffs_full()
{
    using namespace GLOBAL;
    console_write("Тестирование таблицы 'tariffs'.");
    console_indent++;

    console_write("Сохраняю данные:", true);
    users* user = new users(QByteArray(), QByteArray(), "Демьян", "Карибин", "Александрович", true, QDate(2000, 5, 20), "dema.marfida@gmail.com", "+79312699523", "dema2000");
    doctors* doctor = new doctors(user->id(), 3000, QTime(13, 0, 0), QTime(19, 0, 0), "Образование", "Место работы");
    specializations* spec = new specializations("Хирургия", (QString)"Область медицины, изучающая острые и хронические заболевания, которые лечатся при помощи хирургического метода.");
    packages* package = new packages(doctor->id(), spec->id(), 24 * 7);
    tariffs* tariff = new tariffs(package->id(), 7500, "rub", 60 * 60 * 1.5);
    int id = tariff->id();
    console_write(QString::number(tariff->id()) + " " + QString::number(tariff->package_id()) + " " + QString::number(tariff->cost()) + " " + tariff->valuta() + " " + QString::number(tariff->time()));
    delete (tariff);

    console_write("Считываю данные по полю 'id' (full_initialize = true):", true);
    tariff = new tariffs(id, true);
    console_write(QString::number(tariff->id()) + " " + QString::number(tariff->package_id()) + " " + QString::number(tariff->cost()) + " " + tariff->valuta() + " " + QString::number(tariff->time()));

    console_write("Изменяю и сохраняю данные:", true);
    tariff->setDatas(package->id(), 8000, "rub", 60 * 60 * 1.5);
    tariff->update();
    console_write(QString::number(tariff->id()) + " " + QString::number(tariff->package_id()) + " " + QString::number(tariff->cost()) + " " + tariff->valuta() + " " + QString::number(tariff->time()));
    delete (tariff);

    console_write("Считываю обновленные данные по полю 'id' (full_initialize = false):", true);
    tariff = new tariffs(id, false);
    console_write(QString::number(tariff->id()) + " " + QString::number(tariff->package_id()) + " " + QString::number(tariff->cost()) + " " + tariff->valuta() + " " + QString::number(tariff->time()));

    console_write("Создаю еще две строки в таблице:", true);
    tariffs* tariff2 = new tariffs(package->id(), 4000, "rub", 60 * 30);
    int id2 = tariff2->id();
    tariffs* tariff3 = new tariffs(package->id(), 10000, "rub", 60 * 60 * 2);
    int id3 = tariff3->id();
    console_write(QString::number(tariff2->id()) + " " + QString::number(tariff2->package_id()) + " " + QString::number(tariff2->cost()) + " " + tariff2->valuta() + " " + QString::number(tariff2->time()));
    console_write(QString::number(tariff3->id()) + " " + QString::number(tariff3->package_id()) + " " + QString::number(tariff3->cost()) + " " + tariff3->valuta() + " " + QString::number(tariff3->time()));

    console_write("Считываю все строки по полю 'doctor_id':", true);
    QList <tariffs*> packs = tariffs::findTariffs(package->id());
    for(int i = 0; i < packs.size(); i++)
        console_write(QString::number(packs[i]->id()) + " " + QString::number(packs[i]->package_id()) + " " + QString::number(packs[i]->cost()) + " " + packs[i]->valuta() + " " + QString::number(packs[i]->time()));

    console_write("Тестирование таблицы успешно завершено. Удаляю данные.\n", true);
    tariff->remove();
    tariff2->remove();
    tariff3->remove();
    package->remove();
    spec->remove();
    doctor->remove();
    user->remove();

    delete (tariff);
    delete (tariff2);
    delete (tariff3);
    delete (package);
    delete (spec);
    delete (doctor);
    delete (user);
    console_indent--;
    DEBUG_PAUSE();
}

void Tester::comments_full()
{
    using namespace GLOBAL;
    console_write("Тестирование таблицы 'comments'.");
    console_indent++;

    console_write("Сохраняю данные:", true);
    users *user1 = new users(QByteArray(), QByteArray(), "Демьян", "Карибин", "Александрович", true, QDate(2000, 5, 20), "dema.marfida@gmail.com", "+79312699523", "dema2000");
    users *user2 = new users(QByteArray(), QByteArray(), "Татьяна", "Чубарева", "Дмитриевна", false, QDate(2001, 10, 12), "chubareva12@mail.ru", "+79817961923", "taty2001");
    doctors *doctor = new doctors(user1->id(), 3000, QTime(13, 0, 0), QTime(19, 0, 0), "Образование", "Место работы");
    patients* patient = new patients(user2->id());
    comments* comment = new comments(patient->id(), doctor->id(), 5, "Отличный врач!", QDateTime::currentDateTime());
    int id = comment->id();
    console_write(QString::number(comment->id()) + " " + QString::number(comment->patient_id()) + " " + QString::number(comment->doctor_id()) + " " + QString::number(comment->rating()) + " " + comment->message() + " " + comment->timepoint().toString());
    delete (comment);

    console_write("Считываю данные по полю 'name' (full_initialize = true):", true);
    comment = new comments(id, true);
    console_write(QString::number(comment->id()) + " " + QString::number(comment->patient_id()) + " " + QString::number(comment->doctor_id()) + " " + QString::number(comment->rating()) + " " + comment->message() + " " + comment->timepoint().toString());

    console_write("Изменяю и сохраняю данные:", true);
    comment->setDatas(patient->id(), doctor->id(), 2, "Ужасный врач!", QDateTime(QDate(2020, 04, 12), QTime(14, 51, 27)));
    comment->update();
    console_write(QString::number(comment->id()) + " " + QString::number(comment->patient_id()) + " " + QString::number(comment->doctor_id()) + " " + QString::number(comment->rating()) + " " + comment->message() + " " + comment->timepoint().toString());
    delete (comment);

    console_write("Считываю обновленные данные по полю 'id' (full_initialize = false):", true);
    comment = new comments(id, false);
    console_write(QString::number(comment->id()) + " " + QString::number(comment->patient_id()) + " " + QString::number(comment->doctor_id()) + " " + QString::number(comment->rating()) + " " + comment->message() + " " + comment->timepoint().toString());

    console_write("Тестирование таблицы успешно завершено. Удаляю данные.\n", true);
    comment->remove();
    doctor->remove();
    patient->remove();
    user1->remove();
    user2->remove();

    delete (comment);
    delete (doctor);
    delete (patient);
    delete (user1);
    delete (user2);

    console_indent--;
    DEBUG_PAUSE();
}

void Tester::subscriptions_full()
{
    using namespace GLOBAL;
    console_write("Тестирование таблицы 'subscriptions'.");
    console_indent++;

    console_write("Сохраняю данные:", true);
    users *user1 = new users(QByteArray(), QByteArray(), "Демьян", "Карибин", "Александрович", true, QDate(2000, 5, 20), "dema.marfida@gmail.com", "+79312699523", "dema2000");
    users *user2 = new users(QByteArray(), QByteArray(), "Татьяна", "Чубарева", "Дмитриевна", false, QDate(2001, 10, 12), "chubareva12@mail.ru", "+79817961923", "taty2001");
    doctors *doctor = new doctors(user1->id(), 3000, QTime(13, 0, 0), QTime(19, 0, 0), "Образование", "Место работы");
    patients* patient = new patients(user2->id());
    subscriptions* subscription = new subscriptions(patient->id(), doctor->id(), 1, 24 * 7, 4000, "rub", 60 * 30, QDateTime(QDate(2020, 04, 12), QTime(14, 20, 27)), QDateTime(QDate(2020, 04, 19), QTime(14, 20, 27)));
    int id = subscription->id();
    console_write(QString::number(subscription->id()) + " " + QString::number(subscription->patient_id()) + " " + QString::number(subscription->doctor_id()) + " " + QString::number(subscription->interval()) + " " + QString::number(subscription->cost()) + " " + subscription->valuta() + " " + QString::number(subscription->time()) + " " + subscription->timepoint_begin().toString() + " " + subscription->timepoint_end().toString());
    delete (subscription);

    console_write("Считываю данные по полю 'name' (full_initialize = true):", true);
    subscription = new subscriptions(id, true);
    console_write(QString::number(subscription->id()) + " " + QString::number(subscription->patient_id()) + " " + QString::number(subscription->doctor_id()) + " " + QString::number(subscription->interval()) + " " + QString::number(subscription->cost()) + " " + subscription->valuta() + " " + QString::number(subscription->time()) + " " + subscription->timepoint_begin().toString() + " " + subscription->timepoint_end().toString());

    console_write("Изменяю и сохраняю данные:", true);
    subscription->setDatas(patient->id(), doctor->id(), 1, 24 * 30, 12000, "rub", 60 * 60 * 3, QDateTime(QDate(2020, 05, 15), QTime(12, 20, 51)), QDateTime(QDate(2020, 05, 22), QTime(12, 20, 51)));
    subscription->update();
    console_write(QString::number(subscription->id()) + " " + QString::number(subscription->patient_id()) + " " + QString::number(subscription->doctor_id()) + " " + QString::number(subscription->interval()) + " " + QString::number(subscription->cost()) + " " + subscription->valuta() + " " + QString::number(subscription->time()) + " " + subscription->timepoint_begin().toString() + " " + subscription->timepoint_end().toString());
    delete (subscription);

    console_write("Считываю обновленные данные по полю 'id' (full_initialize = false):", true);
    subscription = new subscriptions(id, false);
    console_write(QString::number(subscription->id()) + " " + QString::number(subscription->patient_id()) + " " + QString::number(subscription->doctor_id()) + " " + QString::number(subscription->interval()) + " " + QString::number(subscription->cost()) + " " + subscription->valuta() + " " + QString::number(subscription->time()) + " " + subscription->timepoint_begin().toString() + " " + subscription->timepoint_end().toString());

    console_write("Тестирование таблицы успешно завершено. Удаляю данные.\n", true);
    subscription->remove();
    doctor->remove();
    patient->remove();
    user1->remove();
    user2->remove();

    delete (subscription);
    delete (doctor);
    delete (patient);
    delete (user1);
    delete (user2);

    console_indent--;
    DEBUG_PAUSE();
}

void Tester::dialogs_full()
{

}

void Tester::messages_full()
{
    using namespace GLOBAL;
    console_write("Тестирование таблицы 'messages'.");
    console_indent++;

    console_write("Сохраняю данные:", true);
    users *user1 = new users(QByteArray(), QByteArray(), "Демьян", "Карибин", "Александрович", true, QDate(2000, 5, 20), "dema.marfida@gmail.com", "+79312699523", "dema2000");
    users *user2 = new users(QByteArray(), QByteArray(), "Татьяна", "Чубарева", "Дмитриевна", false, QDate(2001, 10, 12), "chubareva12@mail.ru", "+79817961923", "taty2001");
    doctors *doctor = new doctors(user1->id(), 3000, QTime(13, 0, 0), QTime(19, 0, 0), "Образование", "Место работы");
    patients* patient = new patients(user2->id());
    specializations spec("Хирургия", "Область медицины, изучающая острые и хронические заболевания, которые лечатся при помощи хирургического метода.");
    dialogs* dialog = new dialogs(spec.id(), patient->user_id(), doctor->user_id(), false, true, false, false);
    messages* message = new messages(dialog->id(), user1->id(), QDateTime::currentDateTime(), "Здравствуйте, это тестовое сообщение", false, false);
    int id = message->id();
    console_write(QString::number(message->id()) + " " + QString::number(message->sender_id()) + " " + message->timepoint().toString() + " " + message->message() + " " + bool_to_QString(message->recd()) + " " + bool_to_QString(message->readed()));
    delete (message);

    console_write("Считываю данные по полю 'name' (full_initialize = true):", true);
    message = new messages(id, true);
    console_write(QString::number(message->id()) + " " + QString::number(message->sender_id()) + " " + message->timepoint().toString() + " " + message->message() + " " + bool_to_QString(message->recd()) + " " + bool_to_QString(message->readed()));

    console_write("Изменяю и сохраняю данные:", true);
    message->setDatas(dialog->id(), user1->id(), QDateTime(QDate(2020, 04, 12), QTime(14, 20, 27)), "Новое измененное тестовое сообщение", true, false);
    message->update();
    console_write(QString::number(message->id()) + " " + QString::number(message->sender_id()) + " " + message->timepoint().toString() + " " + message->message() + " " + bool_to_QString(message->recd()) + " " + bool_to_QString(message->readed()));
    delete (message);

    console_write("Считываю обновленные данные по полю 'id' (full_initialize = false):", true);
    message = new messages(id, false);
    console_write(QString::number(message->id()) + " " + QString::number(message->sender_id()) + " " + message->timepoint().toString() + " " + message->message() + " " + bool_to_QString(message->recd()) + " " + bool_to_QString(message->readed()));

    console_write("Тестирование таблицы успешно завершено. Удаляю данные.\n", true);
    message->remove();
    dialog->remove();
    doctor->remove();
    patient->remove();
    user1->remove();
    user2->remove();

    delete (message);
    delete (dialog);
    delete (doctor);
    delete (patient);
    delete (user1);
    delete (user2);

    console_indent--;
    DEBUG_PAUSE();
}
