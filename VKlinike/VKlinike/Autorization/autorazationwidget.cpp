#include "autorazationwidget.h"
#include "BaseProfile/baseprofile.h"
#include "BaseProfile/baseprofileeditor.h"

#include <QLayout>


AutorazationWidget::AutorazationWidget(Widget *_parent) : Widget(_parent)
{
    using namespace GlobalData::interface;
    QVBoxLayout* layout = new QVBoxLayout();
    QHBoxLayout* layout_buttons = new QHBoxLayout();
    QLabel* my_login_label = new QLabel();
    QLabel* my_password_label = new QLabel();
    status = new QLabel();
    my_login = new QLineEdit();
    my_password = new QLineEdit();
    my_autorization = new Button();
    my_registration = new Button();

    status->setText("Введите свои учетные данные");
    my_login_label->setText("Логин:");
    my_password_label->setText("Пароль:");
    my_autorization->setText("Войти");
    my_registration->setText("Регистрация");

    status->setWordWrap(true);
    status->setFixedWidth(GlobalData::screen::geometry.width() - indent * 2);
    status->setAlignment(Qt::AlignCenter);
    setFixedSize(GlobalData::screen::geometry.size());
    my_login->setFixedHeight(row_size * 1.5);
    my_password->setFixedHeight(row_size * 1.5);
    my_autorization->setFrame(true, GlobalData::Frame_Rounded, 3, color::blue);
    my_autorization->setFixedHeight(row_size * 2);
    my_registration->setFrame(true, GlobalData::Frame_Rounded, 3, color::blue);
    my_registration->setFixedHeight(row_size * 2);

    layout_buttons->addWidget(my_autorization);
    layout_buttons->addWidget(my_registration);
    layout_buttons->setSpacing(spacing);
    layout_buttons->setMargin(indent);
    layout->addStretch(0);
    layout->addWidget(status);
    layout->setAlignment(status, Qt::AlignCenter);
    layout->addWidget(my_login_label);
    layout->setAlignment(my_login_label, Qt::AlignLeft);
    layout->addWidget(my_login);
    layout->addWidget(my_password_label);
    layout->setAlignment(my_password_label, Qt::AlignLeft);
    layout->addWidget(my_password);
    layout->addLayout(layout_buttons);
    layout->addStretch(0);
    layout->setSpacing(spacing);
    layout->setMargin(indent);
    setLayout(layout);
    show();

    connect(my_autorization, &Button::clicked, this, &AutorazationWidget::autorization);
    connect(my_registration, &Button::clicked, this, &AutorazationWidget::regisatration);
}

void AutorazationWidget::regisatration()
{
    BaseProfile* base_profile = new BaseProfile(BaseProfileData(), nullptr, GlobalData::Output_Owner);
    BaseProfileEditor *editor = new BaseProfileEditor(base_profile, BaseProfileData(), GlobalData::Mode_Doctor, true);
    connect(editor, &BaseProfileEditor::created, this, &AutorazationWidget::registrated);
    connect(editor, &BaseProfileEditor::destroyed, base_profile, &BaseProfile::deleteLater);
}

void AutorazationWidget::registrated(BaseProfileData _data)
{
    my_login->setText(_data.email);
    my_password->setText(_data.password);
    QTimer::singleShot(100, this, &AutorazationWidget::autorization);
}

void AutorazationWidget::autorization()
{
    emit autorization_request(my_login->text(), my_password->text());
    //my_login->setText("");
    my_password->setText("");
}

void AutorazationWidget::denied()
{
    status->setText("Не удалось войти. Проверьте учетные данные!");
}
