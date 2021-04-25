#include "tester.h"
#include "packer.h"

#include <QCoreApplication>


int main(int argc, char *argv[])
{
    using namespace GLOBAL;
    setlocale(LC_ALL,"Russian");
    QCoreApplication a(argc, argv);

    debug = true;
    testing = false;
    initialize();

    if(testing)
    {
        Tester tester;
        tester.users_full();
        tester.patients_full();
        tester.doctors_full();
        tester.specializations_full();
        tester.packages_full();
        tester.tariffs_full();
        tester.comments_full();
        tester.subscriptions_full();
        tester.dialogs_full();
        tester.messages_full();
    }

    if(false)
    {
        users* user_1 = new users(QByteArray(), QByteArray(), "Анна", "Кощина", "Петровна", true, QDate(2000, 5, 20), "email1@gmail.com", "+79312699523", "password");
        patients* patient_1 = new patients(user_1->id());
        users* user_2 = new users(QByteArray(), QByteArray(), "Павел", "Селюков", "Евгеньевич", true, QDate(1995, 5, 20), "email2@gmail.com", "+79312699523", "password");
        patients* patient_2 = new patients(user_2->id());
        users* user_3 = new users(QByteArray(), QByteArray(), "Олег", "Ахрипов", "Валентинович", true, QDate(1982, 5, 20), "email3@gmail.com", "+79312699523", "password");
        patients* patient_3 = new patients(user_3->id());

        users* user_4 = new users(QByteArray(), QByteArray(), "Ольга", "Будко", "Антоновна", true, QDate(1992, 5, 20), "email4@gmail.com", "+79312699523", "password");
        doctors* doctor_1 = new doctors(user_4->id(), 300, QTime(15, 0, 0), QTime(21, 0, 0), "Образование", "Место работы");
        users* user_5 = new users(QByteArray(), QByteArray(), "Сергей", "Стародубцев", "Альфредович", true, QDate(1994, 5, 20), "email5@gmail.com", "+79312699523", "password");
        doctors* doctor_2 = new doctors(user_5->id(), 300, QTime(15, 0, 0), QTime(21, 0, 0), "Образование", "Место работы");
        users* user_6 = new users(QByteArray(), QByteArray(), "Иван", "Кастров", "Денисович", true, QDate(1988, 5, 20), "email6@gmail.com", "+79312699523", "password");
        doctors* doctor_3 = new doctors(user_6->id(), 300, QTime(15, 0, 0), QTime(21, 0, 0), "Образование", "Место работы");

        users* user = new users(QByteArray(), QByteArray(), "Демьян", "Карибин", "Александрович", true, QDate(2000, 5, 20), "dema.marfida@gmail.com", "+79312699523", "dema2000");
        doctors* doctor = new doctors(user->id(), 300, QTime(13, 0, 0), QTime(19, 0, 0), "Образование", "Место работы");
        specializations* spec_1 = new specializations("Педиатрия", (QString)"Основной задачей педиатрии является сохранение или возвращение состояния здоровья ребёнку, позволяющее ему максимально полно реализовать свой врождённый потенциал жизни.");
        specializations* spec_2 = new specializations("Хирургия", (QString)"Область медицины, изучающая острые и хронические заболевания, которые лечатся при помощи хирургического метода.");

        packages* package_1_1 = new packages(doctor->id(), spec_1->id(), 24 * 30);
        tariffs* tariff_1_1_1 = new tariffs(package_1_1->id(), 4000, "rub", 60 * 60 * 1);
        tariffs* tariff_1_1_2 = new tariffs(package_1_1->id(), 8000, "rub", 60 * 60 * 2);
        tariffs* tariff_1_1_3 = new tariffs(package_1_1->id(), 12000, "rub", 60 * 60 * 3);
        packages* package_1_2 = new packages(doctor->id(), spec_1->id(), 24 * 7);
        tariffs* tariff_1_2_1 = new tariffs(package_1_2->id(), 2000, "rub", 60 * 40);
        tariffs* tariff_1_2_2 = new tariffs(package_1_2->id(), 5000, "rub", 60 * 60 * 1.5);
        packages* package_1_3 = new packages(doctor->id(), spec_1->id(), 24 * 1);
        tariffs* tariff_1_3_1 = new tariffs(package_1_3->id(), 800, "rub", 60 * 10);
        tariffs* tariff_1_3_2 = new tariffs(package_1_3->id(), 1500, "rub", 60 * 30);

        packages* package_2_1 = new packages(doctor->id(), spec_2->id(), 24 * 30);
        tariffs* tariff_2_1_1 = new tariffs(package_2_1->id(), 5000, "rub", 60 * 60 * 1.5);
        tariffs* tariff_2_1_2 = new tariffs(package_2_1->id(), 8000, "rub", 60 * 60 * 3);
        packages* package_2_2 = new packages(doctor->id(), spec_2->id(), 24 * 7);
        tariffs* tariff_2_2_1 = new tariffs(package_2_2->id(), 3000, "rub", 60 * 30);
        tariffs* tariff_2_2_2 = new tariffs(package_2_2->id(), 4500, "rub", 60 * 60);

        packages* package_doc_1 = new packages(doctor->id(), spec_2->id(), 24 * 30);
        tariffs* tariff_doc_1 = new tariffs(package_doc_1->id(), 8000, "rub", 60 * 60 * 2);

        packages* package_doc_2 = new packages(doctor->id(), spec_1->id(), 24 * 30);
        tariffs* tariff_doc_2 = new tariffs(package_doc_2->id(), 4000, "rub", 60 * 60 * 1);

        packages* package_doc_3 = new packages(doctor->id(), spec_1->id(), 24 * 30);
        tariffs* tariff_doc_3 = new tariffs(package_doc_3->id(), 4500, "rub", 60 * 60 * 1.5);

        comments* comment_1 = new comments(patient_1->id(), doctor->id(), 5, "Замечательный врач! Чуткий, отзывчивый, понимающий человек! На приеме полностью информирует пациента о его состоянии, прогнозе, вариантах лечения. Никаких избыточных анализов и обследований не навязывает, только то, что необходимо для оценки состояния и постановки диагноза. Вежливость, корректность, участие! Высокий профессионализм!", QDateTime::currentDateTime());
        comments* comment_2 = new comments(patient_2->id(), doctor->id(), 4, "Все понравилось.", QDateTime::currentDateTime());
        comments* comment_3 = new comments(patient_3->id(), doctor->id(), 2, "Ужасное обращение, никакого уважения. Хотябы услуги соответсвуют заявленному качеству.", QDateTime::currentDateTime());

        dialogs dialog_1(spec_1->id(), patient_1->user_id(), doctor->user_id(), false, true, false, false);
        dialogs dialog_2(spec_1->id(), patient_2->user_id(), doctor->user_id(), false, true, false, false);
        dialogs dialog_3(spec_1->id(), doctor->user_id(), patient_3->user_id(), true, false, false, false);

    }

    return a.exec();
}
