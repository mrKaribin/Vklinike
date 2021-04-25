#include "mainwidget.h"
#include "browser.h"

#include <QScreen>
#include <QFile>
#include <QTimer>
#include <QMenu>


MainWidget::MainWidget() : Widget()
{
    using namespace GlobalData;
    using namespace GlobalData::directory;
    screen = screen::geometry;
    int menuBar_height  = interface::menuBar_height,
        indent          = interface::indent;
    mainArea_geometry.setRect(0, menuBar_height, screen.width(), screen.height() - menuBar_height * 2);
    header_geometry_opened.setRect(0, 0, screen.width(), menuBar_height);
    header_geometry_closed.setRect(0, -menuBar_height, screen.width(), menuBar_height);
    menuBar_geometry_opened.setRect(0, screen.height() - menuBar_height, screen.width(), menuBar_height);
    menuBar_geometry_closed.setRect(0, screen.height() + 100, screen.width(), menuBar_height);
    widget_main = this;
    widget_mainArea = mainArea;

    using namespace GlobalData::directory;
    currentWidget = nullptr;
    profile_widget = nullptr;
    message_widget = nullptr;
    search_widget = nullptr;
    preferences = new Button(QPixmap(icon + icons::preferences).scaled(interface::text_size * 1.2, interface::text_size * 1.2));
    profile_button = new Button(QPixmap(icon + icons::profile).scaled(menuBar_height / 2, menuBar_height / 2));
    message_button = new Button(QPixmap(icon + icons::messages).scaled(menuBar_height / 2, menuBar_height / 2));
    search_button = new Button(QPixmap(icon + icons::search).scaled(menuBar_height / 2, menuBar_height / 2));
    header = new Widget(this);
    menuBar = new Widget(this);
    mainArea = new Widget(this);
    status = new QLabel();
    contextMenu = new QMenu(this);
    serviceThread = new QThread();
    serviceThread->start();

    profile_button->setFixedHeight(menuBar_height);
    message_button->setFixedHeight(menuBar_height);
    search_button->setFixedHeight(menuBar_height);
    mainArea->setFixedSize(mainArea_geometry.size());
    mainArea->move(mainArea_geometry.topLeft());
    header->setFixedSize(header_geometry_opened.size());
    header->move(header_geometry_closed.topLeft());
    header->setFrame(true, Frame_Rectangle, 3, interface::color::blue);
    status->setMinimumHeight(interface::row_size * 1.5);
    setTextSize(status, interface::text_size * 1.2);
    preferences->setFixedSize(interface::row_size * 1.5, interface::row_size * 1.5);
    //preferences->setFrame(true, Frame_Circular, 3, interface::color::blue);
    menuBar->setFixedSize(menuBar_geometry_opened.size());
    menuBar->setFrame(true, Frame_Rectangle, 3, interface::color::blue);

    QHBoxLayout* layout_header = new QHBoxLayout();
    layout_header->addWidget(status);
    layout_header->addStretch(0);
    layout_header->addWidget(preferences);
    layout_header->setContentsMargins(interface::indent * 2, 0, interface::indent * 2, 0);
    contextMenu->addAction("Сменить режим");
    contextMenu->addAction("Выйти");
    header->setLayout(layout_header);
    header->setGeometry(header_geometry_closed);

    QHBoxLayout *layout_bar = new QHBoxLayout();
    layout_bar->addWidget(profile_button);
    layout_bar->addWidget(message_button);
    layout_bar->addWidget(search_button);
    layout_bar->setSpacing(0);
    layout_bar->setMargin(0);
    menuBar->setLayout(layout_bar);
    menuBar->setGeometry(menuBar_geometry_closed);

    Autorization* autorization = new Autorization(this);

    connect(profile_button, &Button::clicked, this, &MainWidget::profile_button_Clicked);
    connect(message_button, &Button::clicked, this, &MainWidget::message_button_Clicked);
    connect(search_button, &Button::clicked, this, &MainWidget::search_button_Clicked);
    connect(preferences, &Button::clicked, this, &MainWidget::menu_Open);
    connect(contextMenu, &QMenu::triggered, this, &MainWidget::menu_Clicked);
    connect(autorization, &Autorization::confirmed, this, &MainWidget::prepareMainArea);
    connect(this, &MainWidget::destroyed, GlobalData::socket, &Socket::disconnection);
    connect(GlobalData::socket, &Socket::package_received, this, &MainWidget::server_reply);

    show();
    setFixedSize(screen.width(), screen.height());
    move(0, 0);
}

void MainWidget::create_profile_doctor(Widget *parent, QString login, GlobalData::OutputType type)
{
    using namespace GlobalData;
    DoctorProfile* _profile = new DoctorProfile(login, nullptr, type);
    Widget* profile_widget_info = new Widget();
    QVBoxLayout *profile_layout_info = new QVBoxLayout();
    profile_layout_info->addWidget(_profile->baseProfile()->widget_info());
    profile_layout_info->addWidget(_profile->widget_doctor_info());
    profile_layout_info->addStretch(0);
    profile_layout_info->setSizeConstraint(QLayout::SetMinAndMaxSize);
    profile_layout_info->setMargin(0);
    profile_layout_info->setSpacing(interface::spacing);
    profile_widget_info->setLayout(profile_layout_info);
    profile_widget_info->setFixedWidth(screen::geometry.width() - interface::indent * 2);
    TabWidget* profile_tab = new TabWidget();
    profile_tab->addTab("Информация", profile_widget_info);
    profile_tab->addTab("Подписки", _profile->widget_subscriptions());
    profile_tab->addTab("Отзывы", _profile->widget_comments());
    QVBoxLayout *profile_layout = new QVBoxLayout();
    profile_layout->addWidget(_profile->baseProfile()->widget_header());
    if(type == Output_Owner)
        profile_layout->addWidget(_profile->baseProfile()->widget_edit());
    profile_layout->addWidget(_profile->widget_achievements());
    profile_layout->addWidget(profile_tab);
    profile_layout->addStretch(0);
    profile_layout->setMargin(interface::indent);
    profile_layout->setSpacing(interface::spacing);
    profile_layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    parent->setLayout(profile_layout);
}

void MainWidget::create_profile_patient(Widget *parent, QString login, GlobalData::OutputType type)
{
    using namespace GlobalData;
    PatientProfile* profile = new PatientProfile(login, parent, type);
    QVBoxLayout *profile_layout = new QVBoxLayout();
    profile_layout->addWidget(profile->baseProfile()->widget_header());
    profile_layout->addWidget(profile->baseProfile()->widget_info());
    profile_layout->addWidget(profile->subscriptions());
    if(type == Output_Owner)
        profile_layout->addWidget(profile->baseProfile()->widget_edit());
    profile_layout->addStretch(0);
    profile_layout->setMargin(interface::indent);
    profile_layout->setSpacing(interface::spacing);
    profile_layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    parent->setLayout(profile_layout);
}

void MainWidget::create_search_patient(Widget *parent, GlobalData::OutputType)
{
    using namespace GlobalData;
    Search *_search = new Search();
    QVBoxLayout *search_layout = new QVBoxLayout();
    search_layout->addWidget(_search->create_widget_search(_search));
    search_layout->addStretch(0);
    parent->setLayout(search_layout);
}

void MainWidget::create_message(Widget *parent, GlobalData::OutputType)
{
    using namespace GlobalData;
    Messages* _messages = new Messages(parent);
    QVBoxLayout *messages_layout = new QVBoxLayout();
    messages_layout->addWidget(_messages->widget());
    messages_layout->addStretch(0);
    messages_layout->setMargin(interface::indent);
    messages_layout->setSpacing(interface::spacing);
    parent->setLayout(messages_layout);
}

void MainWidget::prepareMainArea()
{
    using namespace GlobalData;

    if(profile_widget != nullptr)
        profile_widget->deleteLater();
    profile_widget = new Widget(mainArea);
    profile_widget->setFixedWidth(mainArea_geometry.width());
    profile_widget->setMaximumHeight(1000000);
    profile_widget->setMovable_vertical(true);
    profile_widget->setMoveableBorder(0, 0, mainArea_geometry.width(), mainArea_geometry.height());
    profile_widget->move(-screen::geometry.width(), 0);

    if(message_widget != nullptr)
        message_widget->deleteLater();
    message_widget = new Widget(mainArea);
    message_widget->setFixedWidth(mainArea_geometry.width());
    message_widget->setMaximumHeight(1000000);
    message_widget->setMovable_vertical(true);
    message_widget->setMoveableBorder(0, 0, mainArea_geometry.width(), mainArea_geometry.height());
    message_widget->move(-screen::geometry.width(), 0);

    if(search_widget != nullptr)
        search_widget->deleteLater();
    search_widget = new Widget(mainArea);
    search_widget->setFixedWidth(mainArea_geometry.width());
    search_widget->setMaximumHeight(1000000);
    search_widget->setMovable_vertical(true);
    search_widget->setMoveableBorder(0, 0, mainArea_geometry.width(), mainArea_geometry.height());
    search_widget->move(-screen::geometry.width(), 0);

    GlobalData::database_Write();

    if(GlobalData::currentMode == GlobalData::Mode_Doctor)
    {
        create_profile_doctor(profile_widget);
        create_message(message_widget);
        message_button_Clicked();
    }
    if(GlobalData::currentMode == GlobalData::Mode_Patient)
    {
        create_profile_patient(profile_widget);
        create_message(message_widget);
        create_search_patient(search_widget);
        message_button_Clicked();
    }
    menuBar_Open();
}

void MainWidget::widgets_Swift(QWidget *widget_new, SwiftType _type, bool saveLast)
{
    using namespace GlobalData::interface;
    QPropertyAnimation* widget_new_animation_geometry;
    if(widget_new != nullptr)
        widget_new_animation_geometry = new QPropertyAnimation(widget_new, "geometry", serviceThread);

    QPropertyAnimation* widget_current_animation_geometry;
    if(currentWidget != nullptr)
        widget_current_animation_geometry = new QPropertyAnimation(currentWidget, "geometry", serviceThread);

    switch (_type)
    {
    case (Swift_Appear):
    {
        QParallelAnimationGroup* animation_group_parallel = new QParallelAnimationGroup();
        QSequentialAnimationGroup* animation_group_sequential = new QSequentialAnimationGroup();

        break;
    }
    case (Swift_toRight):
    case (Swift_toLeft):
    {
        QParallelAnimationGroup* animation_group_parallel = new QParallelAnimationGroup();

        widget_new->move(-widget_new->x(), -widget_new->y());
        widget_new->show();

        widget_new_animation_geometry->setDuration(GlobalData::interface::animation_duration);
        if(_type == Swift_toRight)
            widget_new_animation_geometry->setStartValue(QRect(screen.width(), 0, mainArea_geometry.width(), mainArea_geometry.height()));
        if(_type == Swift_toLeft)
            widget_new_animation_geometry->setStartValue(QRect(-screen.width(), 0, mainArea_geometry.width(), mainArea_geometry.height()));
        widget_new_animation_geometry->setEndValue(QRect(0, 0, mainArea_geometry.width(), mainArea_geometry.height()));
        widget_new_animation_geometry->setEasingCurve(animation_curve);

        if(currentWidget != nullptr)
        {
            widget_current_animation_geometry->setDuration(GlobalData::interface::animation_duration);
            widget_current_animation_geometry->setStartValue(QRect(0, 0, mainArea_geometry.width(), mainArea_geometry.height()));
            if(_type == Swift_toRight)
                widget_current_animation_geometry->setEndValue(QRect(-screen.width(), 0, mainArea_geometry.width(), mainArea_geometry.height()));
            if(_type == Swift_toLeft)
                widget_current_animation_geometry->setEndValue(QRect(screen.width(), 0, mainArea_geometry.width(), mainArea_geometry.height()));
            widget_current_animation_geometry->setEasingCurve(animation_curve);
        }

        animation_group_parallel->addAnimation(widget_new_animation_geometry);
        if(currentWidget != nullptr)
            animation_group_parallel->addAnimation(widget_current_animation_geometry);
        animation_group_parallel->start();

        connect(animation_group_parallel, &QSequentialAnimationGroup::finished, widget_new_animation_geometry, &QPropertyAnimation::deleteLater);
        if(currentWidget != nullptr)
            connect(animation_group_parallel, &QSequentialAnimationGroup::finished, widget_current_animation_geometry, &QPropertyAnimation::deleteLater);
        break;
    }
    case(Swift_toTop):
    {
        QParallelAnimationGroup* animation_group_parallel = new QParallelAnimationGroup();

        widget_new_animation_geometry->setDuration(GlobalData::interface::animation_duration);
        widget_new_animation_geometry->setStartValue(QRect(screen.width(), 0, mainArea_geometry.width(), mainArea_geometry.height()));
        widget_new_animation_geometry->setEndValue(QRect(0, 0, mainArea_geometry.width(), mainArea_geometry.height()));
        widget_new_animation_geometry->setEasingCurve(animation_curve);

        if(currentWidget != nullptr)
        {
            widget_current_animation_geometry->setDuration(GlobalData::interface::animation_duration);
            widget_current_animation_geometry->setStartValue(QRect(0, 0, mainArea_geometry.width(), mainArea_geometry.height()));
            widget_current_animation_geometry->setEndValue(QRect(-screen.width(), 0, mainArea_geometry.width(), mainArea_geometry.height()));
            widget_current_animation_geometry->setEasingCurve(animation_curve);
        }

        animation_group_parallel->addAnimation(widget_new_animation_geometry);
        if(currentWidget != nullptr)
            animation_group_parallel->addAnimation(widget_current_animation_geometry);
        animation_group_parallel->start();
        break;
    }
    case(Swift_toFullScreen):
    {
        QParallelAnimationGroup* animation_group_parallel = new QParallelAnimationGroup();

        widget_new_animation_geometry->setDuration(GlobalData::interface::animation_duration);
        widget_new_animation_geometry->setStartValue(QRect(0, -screen.height(), mainArea_geometry.width(), mainArea_geometry.height()));
        widget_new_animation_geometry->setEndValue(QRect(0, 0, mainArea_geometry.width(), mainArea_geometry.height()));
        widget_new_animation_geometry->setEasingCurve(animation_curve);

        if(currentWidget != nullptr)
        {
            widget_current_animation_geometry->setDuration(GlobalData::interface::animation_duration);
            widget_current_animation_geometry->setStartValue(QRect(0, 0, mainArea_geometry.width(), mainArea_geometry.height()));
            widget_current_animation_geometry->setEndValue(QRect(0, screen.height(), mainArea_geometry.width(), mainArea_geometry.height()));
            widget_current_animation_geometry->setEasingCurve(animation_curve);
        }

        animation_group_parallel->addAnimation(widget_new_animation_geometry);
        if(currentWidget != nullptr)
            animation_group_parallel->addAnimation(widget_current_animation_geometry);
        animation_group_parallel->start();

        menuBar_Close();
        break;
    }
    }

    if(saveLast){
        if(widget_new != profile_widget && widget_new != message_widget && widget_new != search_widget)
            lastWidgets << currentWidget;
        else
        {
            for(auto wgt : lastWidgets)
                delete wgt;
            lastWidgets.clear();
        }
    }
    currentWidget = widget_new;
}

void MainWidget::closeEvent(QCloseEvent *event)
{
    GlobalData::socket->disconnection();
}

void MainWidget::menuBar_Open()
{
    if(menuBar_opened)
        return;
    QPropertyAnimation* menuBar_animation_geometry = new QPropertyAnimation(menuBar, "geometry");
    menuBar_animation_geometry->setDuration(GlobalData::interface::animation_duration);
    menuBar_animation_geometry->setEasingCurve(GlobalData::interface::animation_curve);
    menuBar_animation_geometry->setStartValue(menuBar_geometry_closed);
    menuBar_animation_geometry->setEndValue(menuBar_geometry_opened);
    menuBar_animation_geometry->start();

    QPropertyAnimation* header_animation_geometry = new QPropertyAnimation(header, "geometry");
    header_animation_geometry->setDuration(GlobalData::interface::animation_duration);
    header_animation_geometry->setEasingCurve(GlobalData::interface::animation_curve);
    header_animation_geometry->setStartValue(header_geometry_closed);
    header_animation_geometry->setEndValue(header_geometry_opened);
    header_animation_geometry->start();
    menuBar_opened = true;
}

void MainWidget::menuBar_Close()
{
    if(!menuBar_opened)
        return;
    QPropertyAnimation* menuBar_animation_geometry = new QPropertyAnimation(menuBar, "geometry");
    menuBar_animation_geometry->setDuration(GlobalData::interface::animation_duration);
    menuBar_animation_geometry->setEasingCurve(GlobalData::interface::animation_curve);
    menuBar_animation_geometry->setStartValue(menuBar_geometry_opened);
    menuBar_animation_geometry->setEndValue(menuBar_geometry_closed);
    menuBar_animation_geometry->start();

    QPropertyAnimation* header_animation_geometry = new QPropertyAnimation(header, "geometry");
    header_animation_geometry->setDuration(GlobalData::interface::animation_duration);
    header_animation_geometry->setEasingCurve(GlobalData::interface::animation_curve);
    header_animation_geometry->setStartValue(header_geometry_opened);
    header_animation_geometry->setEndValue(header_geometry_closed);
    header_animation_geometry->start();
    menuBar_opened = false;
}

void MainWidget::menu_Open()
{
    contextMenu->exec(header_geometry_opened.bottomRight());
}

void MainWidget::menu_Clicked(QAction *action)
{
    if(action->text() == "Сменить режим")
    {
        if(GlobalData::currentMode == GlobalData::Mode_Doctor)
            GlobalData::currentMode = GlobalData::Mode_Patient;
        else
            GlobalData::currentMode = GlobalData::Mode_Doctor;
        prepareMainArea();
    }
    if(action->text() == "Выйти")
    {
        GlobalData::currentLogin = "";
        GlobalData::currentPassword = "";
        GlobalData::database_Write();
        menuBar_Close();
        Autorization* autorization = new Autorization(this);
        connect(autorization, &Autorization::confirmed, this, &MainWidget::prepareMainArea);
    }
    contextMenu->hide();
}

void MainWidget::returning()
{
    while(!lastWidgets.isEmpty())
    {
        QWidget *widget = lastWidgets.pop();
        if(widget != nullptr)
        {
            if((widget == profile_widget || widget == message_widget || widget == search_widget) && !menuBar_opened)
                menuBar_Open();
            widgets_Swift(widget, Swift_toTop, false);
            return;
        }
    }
}

void MainWidget::icons_Reload()
{
    using namespace GlobalData;
    if(currentWidget == nullptr)
        return;
    if(currentWidget == profile_widget)
        profile_button->setPixmap(QPixmap(directory::icon + "profile.png").scaled(interface::menuBar_height / 2, interface::menuBar_height / 2));
    if(currentWidget == message_widget)
        message_button->setPixmap(QPixmap(directory::icon + "messages.png").scaled(interface::menuBar_height / 2, interface::menuBar_height / 2));
    if(currentWidget == search_widget)
        message_button->setPixmap(QPixmap(directory::icon + "search.png").scaled(interface::menuBar_height / 2, interface::menuBar_height / 2));
}

void MainWidget::profile_button_Clicked()
{
    using namespace GlobalData;
    if(currentWidget == profile_widget || profile_widget == nullptr)
        return;

    icons_Reload();
    if(currentWidget != nullptr && (currentWidget == message_widget || currentWidget == search_widget))
    {
        widgets_Swift(profile_widget, Swift_toLeft);
    }
    else
    {
        widgets_Swift(profile_widget, Swift_toTop);
    }

    status->setText("Профиль");
    profile_button->setPixmap(QPixmap(directory::icon + "profile_active.png").scaled(interface::menuBar_height / 2, interface::menuBar_height / 2));
}

void MainWidget::message_button_Clicked()
{
    using namespace GlobalData;
    if(currentWidget == message_widget || message_widget == nullptr)
        return;

    icons_Reload();
    if(currentWidget != nullptr && currentWidget == search_widget)
    {
        widgets_Swift(message_widget, Swift_toLeft);
    }
    else if(currentWidget != nullptr && currentWidget == profile_widget)
    {
        widgets_Swift(message_widget, Swift_toRight);
    }
    else
    {
        widgets_Swift(message_widget, Swift_toTop);
    }

    status->setText("Консультации");
    message_button->setPixmap(QPixmap(directory::icon + "messages_active.png").scaled(interface::menuBar_height / 2, interface::menuBar_height / 2));
}

void MainWidget::search_button_Clicked()
{
    using namespace GlobalData;
    if(currentWidget == search_widget || search_widget == nullptr)
        return;

    icons_Reload();
    if(currentWidget != nullptr && (currentWidget == message_widget || currentWidget == profile_widget))
    {
        widgets_Swift(search_widget, Swift_toRight);
    }
    else
    {
        widgets_Swift(search_widget, Swift_toTop);
    }

    status->setText("Поиск");
    search_button->setPixmap(QPixmap(directory::icon + "search_active.png").scaled(interface::menuBar_height / 2, interface::menuBar_height / 2));
}

void MainWidget::profile_base_edit(BaseProfile* _object, BaseProfileData _data)
{
    BaseProfileEditor *editor = new BaseProfileEditor(_object, _data, GlobalData::currentMode);
}

void MainWidget::profile_doctor_edit(DoctorProfile* _object, DoctorProfileData _data, QList <SpecializationData> _specs)
{
    DoctorPackageList *editor = new DoctorPackageList(_object);
    editor->setDatas(_data);
    editor->setSpecializations(_specs);
}

void MainWidget::server_reply(QString header, QByteArray body)
{
    using namespace GlobalData::query;
    if(header == redirection_web)
    {
        QString url;
        Unpacker unpacker(body);
        unpacker >> url;
        unpacker >> url;
        unpacker >> url;
        Browser* browser = new Browser(url);
    }
    else if(header == payment_complete)
    {
        GlobalData::error_Show("PayPal", "Транзакция успешно выполнена.");
        profile_button_Clicked();
        if(!menuBar_opened)
            menuBar_Open();
    }
}

void MainWidget::server_waitForReply(QString reply)
{

}
