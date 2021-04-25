#include "baseprofileeditor.h"
#include "baseprofile.h"
#include "QFileDialog"
#include "viewer.h"

#include <QLayout>


BaseProfileEditor::BaseProfileEditor(BaseProfile *_object, BaseProfileData _data, GlobalData::Mode _mode, bool _creating, QWidget *parent) : Widget(parent)
{
    my_object = _object;
    my_data = _data;
    my_mode = _mode;
    creating = _creating;
    if(parent == nullptr)
    {
        Viewer* viewer = new Viewer(this);
        connect(this, &BaseProfileEditor::returning, viewer, &Viewer::back);
    }
    initializing();
    formating();
    filling();
    linking();
}

void BaseProfileEditor::initializing()
{
    using namespace GlobalData;

    layout = new QVBoxLayout();
    layout_photo = new QGridLayout();
    layout_sex = new QHBoxLayout();
    wgt_photo = new QLabel();
    wgt_photo_edit = new Button();
    wgt_photo_remove = new Button();
    wgt_photo_status = new QLabel();
    wgt_name = new QLineEdit();
    wgt_name_status = new QLabel();
    wgt_surname = new QLineEdit();
    wgt_surname_status = new QLabel();
    wgt_patronimic = new QLineEdit();
    wgt_patronimic_status = new QLabel();
    wgt_sex_male = new QCheckBox();
    wgt_sex_female = new QCheckBox();
    wgt_sex_status = new QLabel;
    wgt_birthday = new QLineEdit();
    wgt_birthday_status = new QLabel();
    wgt_email = new QLineEdit();
    wgt_email_status = new QLabel();
    wgt_phone = new QLineEdit();
    wgt_phone_status = new QLabel();
    if(creating){
        wgt_password = new QLineEdit();
        wgt_password_status = new QLabel();
        connect(wgt_password, &QLineEdit::textEdited, this, &BaseProfileEditor::passwordChanged);
    }
    wgt_save = new Button();

    margin = interface::indent;
    spacing = interface::spacing;
    text_main_size = interface::text_size;
    text_status_size = interface::text_size * 0.6;
    size_photo = QSize(interface::photo_size * 2, interface::photo_size * 2);
    size_line = QSize(screen::geometry.width() - margin * 2, interface::row_size * 1.2);
    size_status = QSize(screen::geometry.width() - margin * 2, interface::row_size * 0.6);

    connect(wgt_photo_edit, &Button::clicked, this, &BaseProfileEditor::photoEdit);
    connect(wgt_photo_remove, &Button::clicked, this, &BaseProfileEditor::photoRemove);
    connect(wgt_save, &Button::clicked, this, &BaseProfileEditor::save);
    connect(wgt_name, &QLineEdit::textEdited, this, &BaseProfileEditor::nameChanged);
    connect(wgt_surname, &QLineEdit::textEdited, this, &BaseProfileEditor::surnameChanged);
    connect(wgt_patronimic, &QLineEdit::textEdited, this, &BaseProfileEditor::patronimicChanged);
    connect(wgt_sex_male, &QCheckBox::stateChanged, this, &BaseProfileEditor::maleChecked);
    connect(wgt_sex_female, &QCheckBox::stateChanged, this, &BaseProfileEditor::femaleChecked);
    connect(wgt_birthday, &QLineEdit::textEdited, this, &BaseProfileEditor::birthdayChanged);
    connect(wgt_email, &QLineEdit::textEdited, this, &BaseProfileEditor::emailChanged);
    connect(wgt_phone, &QLineEdit::textEdited, this, &BaseProfileEditor::phoneChanged);

    if(my_object != nullptr)
    {
        connect(this, &BaseProfileEditor::saved, my_object, &BaseProfile::edited);
        connect(this, &BaseProfileEditor::created, my_object, &BaseProfile::created);
    }
}

void BaseProfileEditor::formating()
{
    using namespace GlobalData;

    wgt_photo->setFixedSize(size_photo);
    wgt_photo_edit->setFixedSize(size_line.width() / 3, interface::row_size * 1.5);
    wgt_photo_edit->setFrame(true, GlobalData::Frame_Rectangle, 2, interface::color::blue);
    wgt_photo_remove->setFixedSize(size_line.width() / 3, interface::row_size * 1.5);
    wgt_photo_remove->setFrame(true, GlobalData::Frame_Rectangle, 2, interface::color::blue);

    formating_line(wgt_name);
    formating_status(wgt_name_status);

    formating_line(wgt_surname);
    formating_status(wgt_surname_status);

    formating_line(wgt_patronimic);
    formating_status(wgt_patronimic_status);

    formating_line(wgt_birthday);
    formating_status(wgt_birthday_status);

    formating_line(wgt_email);
    formating_status(wgt_email_status);

    formating_line(wgt_phone);
    formating_status(wgt_phone_status);

    Widget::setTextSize(wgt_sex_male, text_main_size);
    Widget::setTextSize(wgt_sex_female, text_main_size);
    formating_status(wgt_sex_status);

    if(creating)
    {
        formating_line(wgt_password);
        formating_status(wgt_password_status);
    }

    wgt_save->setText("Сохранить");
    wgt_save->setFixedSize(size_line.width(), interface::row_size * 2);
    wgt_save->setFrame(true, GlobalData::Frame_Rounded, 3, interface::color::blue);
}

void BaseProfileEditor::formating_line(QLineEdit *line)
{
    line->setFixedSize(size_line);
    Widget::setTextSize(line, text_main_size);
    line->setAlignment(Qt::AlignLeft);
}

void BaseProfileEditor::formating_status(QLabel *label)
{
    label->setFixedSize(size_status);
    Widget::setTextSize(label, text_status_size);
    label->setAlignment(Qt::AlignCenter);
}

void BaseProfileEditor::filling()
{
    using namespace GlobalData;
    QString status_prefix = (my_mode == GlobalData::Mode_Doctor) ? ("* ") : ("");

    wgt_photo_edit->setText("Изменить");
    wgt_photo_remove->setText("Удалить");
    wgt_sex_male->setText("Мужской");
    wgt_sex_female->setText("Женский");

    if(my_data.photo.isNull())
        my_data.photo.load(directory::image + ((currentMode == Mode_Doctor) ? directory::images::doctor : directory::images::patient));
    my_photo = my_data.photo;
    wgt_photo->setPixmap(my_data.photo.scaled(wgt_photo->size(), Qt::KeepAspectRatioByExpanding));
    wgt_name->setText(my_data.name);
    wgt_surname->setText(my_data.surname);
    if(my_data.birthday == QDate(0, 0, 0))
        wgt_birthday->setText("");
    else
        wgt_birthday->setText(((my_data.birthday.day() < 10) ? ("0" + QString::number(my_data.birthday.day())) : (QString::number(my_data.birthday.day()))) + "." +
                              ((my_data.birthday.month() < 10) ? ("0" + QString::number(my_data.birthday.month())) : (QString::number(my_data.birthday.month()))) + "." +
                              QString::number(my_data.birthday.year()));
    (my_data.sex == 1) ? (wgt_sex_female->setCheckState(Qt::Checked)) : (wgt_sex_male->setCheckState(Qt::Checked));
    wgt_patronimic->setText(my_data.patronymic);
    wgt_email->setText(my_data.email);
    wgt_phone->setText(my_data.phone);

    wgt_photo_status->setText("загрузите вашу фотографию");
    wgt_name_status->setText("* введите ваше полное имя");
    wgt_surname_status->setText(status_prefix + "введите вашу фамилию");
    wgt_patronimic_status->setText(status_prefix + "введите ваше отчество");
    wgt_birthday_status->setText("* введите вашу дату рождения (дд.мм.гггг)");
    wgt_sex_status->setText("* выберите ваш пол");
    wgt_email_status->setText("* введите уникальную электронную почту");
    wgt_phone_status->setText(status_prefix + "введите ваш номер телефона");
    if(creating)
        wgt_password_status->setText(status_prefix + "введите пароль");
}

void BaseProfileEditor::linking()
{
    using namespace GlobalData;
    layout_photo->addWidget(wgt_photo, 0, 0, 2, 2);
    layout_photo->addWidget(wgt_photo_edit, 0, 1, 1, 1);
    layout_photo->addWidget(wgt_photo_remove, 1, 1, 1, 1);
    layout_sex->addWidget(wgt_sex_male);
    layout_sex->addStretch(1);
    layout_sex->addWidget(wgt_sex_female);


    layout->addLayout(layout_photo);
    layout->addSpacing(spacing);
    layout->addWidget(wgt_name);
    layout->addWidget(wgt_name_status);
    layout->addSpacing(spacing);
    layout->addWidget(wgt_surname);
    layout->addWidget(wgt_surname_status);
    layout->addSpacing(spacing);
    layout->addWidget(wgt_patronimic);
    layout->addWidget(wgt_patronimic_status);
    layout->addSpacing(spacing);
    layout->addLayout(layout_sex);
    layout->addWidget(wgt_sex_status);
    layout->addSpacing(spacing);
    layout->addWidget(wgt_birthday);
    layout->addWidget(wgt_birthday_status);
    layout->addSpacing(spacing);
    layout->addWidget(wgt_email);
    layout->addWidget(wgt_email_status);
    layout->addSpacing(spacing);
    layout->addWidget(wgt_phone);
    layout->addWidget(wgt_phone_status);
    layout->addSpacing(spacing);
    if(creating)
    {
        layout->addWidget(wgt_password);
        layout->addWidget(wgt_password_status);
        layout->addSpacing(spacing);
    }
    layout->addWidget(wgt_save);
    layout->setMargin(margin);
    layout->setSizeConstraint(QLayout::SetMinAndMaxSize);

    setLayout(layout);
}

void BaseProfileEditor::photoChanged()
{

}

void BaseProfileEditor::photoEdit()
{
    QString file = QFileDialog::getOpenFileName(nullptr, tr("Open File"), "/storage/emulated/0/DCIM/Camera", tr("Images (*.png *.xpm *.jpg)"));
    my_photo = QPixmap(file).scaled(wgt_photo->size(), Qt::KeepAspectRatioByExpanding);
    wgt_photo->setPixmap(my_photo);
}

void BaseProfileEditor::photoRemove()
{
    my_photo = QPixmap();
    wgt_photo->setPixmap(my_photo);
}

void BaseProfileEditor::nameChanged(QString _name)
{

}

void BaseProfileEditor::surnameChanged(QString _surname)
{

}

void BaseProfileEditor::patronimicChanged(QString _patronimic)
{

}

void BaseProfileEditor::maleChecked(int check)
{
    switch(check)
    case Qt::Checked :
    {
        wgt_sex_female->setCheckState(Qt::Unchecked);
        break;
    }
}

void BaseProfileEditor::femaleChecked(int check)
{
    switch(check)
    case Qt::Checked :
    {
        wgt_sex_male->setCheckState(Qt::Unchecked);
        break;
    }
}

void BaseProfileEditor::birthdayChanged(QString _birthday)
{

}

void BaseProfileEditor::emailChanged(QString _email)
{

}

void BaseProfileEditor::phoneChanged(QString _phone)
{

}

void BaseProfileEditor::passwordChanged(QString _password)
{

}

void BaseProfileEditor::save()
{
    my_data.photo = my_photo;
    my_data.name = wgt_name->text();
    my_data.surname = wgt_surname->text();
    my_data.patronymic = wgt_patronimic->text();
    if(wgt_sex_male->isChecked())
        my_data.sex = 0;
    else if(wgt_sex_female->isChecked())
        my_data.sex = 1;

    QStringList list = wgt_birthday->text().split(".");
    if(list.size() == 3)
        my_data.birthday.setDate(list[2].toInt(), list[1].toInt(), list[0].toInt());

    my_data.email = wgt_email->text();
    my_data.phone = wgt_phone->text();
    if(creating)
    {
        my_data.password = wgt_password->text();
        emit created(my_data);
    }
    else
        emit saved(my_data);
    emit returning();
}
