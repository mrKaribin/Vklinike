#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "globaldata.h"
#include "widget.h"
#include "button.h"
#include "tabwidget.h"
#include "DoctorProfile/doctorprofile.h"
#include "PatientProfile/patientprofile.h"
#include "Messages/messages.h"
#include "Search/search.h"
#include "socket.h"
#include "Autorization/autorization.h"

#include <QCloseEvent>
#include <QStack>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QScrollArea>
#include <QScrollBar>
#include <QAction>


class MainWidget : public Widget
{
    Q_OBJECT
public:
    MainWidget();

    enum SwiftType {Swift_toLeft = 0, Swift_toRight, Swift_toTop, Swift_toBottom, Swift_Appear, Swift_toFullScreen};
    enum MenuType {Menu_Profile = 0, Menu_Message, Menu_Search};

    void                            icons_Reload();

    static void                    create_profile_doctor(Widget* parent, QString login = GlobalData::currentLogin, GlobalData::OutputType type = GlobalData::Output_Owner);
    static void                    create_profile_patient(Widget* parent, QString login = GlobalData::currentLogin, GlobalData::OutputType type = GlobalData::Output_Owner);
    static void                    create_message(Widget* parent, GlobalData::OutputType type = GlobalData::Output_Owner);
    static void                    create_search_patient(Widget* parent, GlobalData::OutputType type = GlobalData::Output_Owner);

private:
    QTimer                         *repaintTimer;

    QThread                        *serviceThread;

    QStack <QWidget*>               lastWidgets;

    QWidget                        *currentWidget;

    Widget                         *profile_widget,
                                   *message_widget,
                                   *search_widget,
                                   *header,
                                   *mainArea,
                                   *menuBar;

    Button                         *preferences,
                                   *profile_button,
                                   *message_button,
                                   *search_button;

    QLabel                         *status;

    QMenu                          *contextMenu;

    QRect                           screen;
    QRect                           mainArea_geometry;
    QRect                           menuBar_geometry_closed;
    QRect                           menuBar_geometry_opened;
    QRect                           header_geometry_closed;
    QRect                           header_geometry_opened;

    bool                            menuBar_opened = false;

protected:
    void                            closeEvent(QCloseEvent* event);

public slots:
    void                            prepareMainArea();

    void                            menuBar_Open();
    void                            menuBar_Close();
    void                            widgets_Swift(QWidget* widget_new, SwiftType _type, bool saveLast = true);

    void                            menu_Open();
    void                            menu_Clicked(QAction* action);

    void                            returning();
    void                            profile_button_Clicked();
    void                            message_button_Clicked();
    void                            search_button_Clicked();

    void                            profile_base_edit(BaseProfile* _object, BaseProfileData _data);
    void                            profile_doctor_edit(DoctorProfile *_object, DoctorProfileData _data, QList <SpecializationData> _specs);

    void                            server_reply(QString header, QByteArray body);
    void                            server_waitForReply(QString);

signals:
    void                            server_request(QString header, QByteArray body);
    void                            profile_edit();
    void                            doctor_edit();

};

#endif // MAINWIDGET_H
