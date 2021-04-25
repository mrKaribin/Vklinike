QT       += core gui sql network quick webview quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG -= app_bundle


unix::android: QMAKE_LFLAGS += -nostdlib++

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    Autorization/autorazationwidget.cpp \
    Autorization/autorization.cpp \
    BaseProfile/baseprofile.cpp \
    BaseProfile/baseprofiledata.cpp \
    BaseProfile/baseprofileeditor.cpp \
    BaseProfile/baseprofilewidget.cpp \
    Cards/cardeditor.cpp \
    Cards/cards.cpp \
    Cards/cardslist.cpp \
    Dialog/dialog.cpp \
    Dialog/dialogwidget.cpp \
    DoctorProfile/doctorpackageedit.cpp \
    DoctorProfile/doctorprofile.cpp \
    DoctorProfile/doctorprofiledata.cpp \
    DoctorProfile/doctorprofilewidget.cpp \
    Messages/messages.cpp \
    Messages/messagesdata.cpp \
    Messages/messageswidget.cpp \
    PatientProfile/patientprofile.cpp \
    PatientProfile/patientprofiledata.cpp \
    PatientProfile/patientprofilewidget.cpp \
    Search/patientsearchwidget.cpp \
    Search/search.cpp \
    Search/searchdata.cpp \
    browser.cpp \
    button.cpp \
    globaldata.cpp \
    main.cpp \
    mainwidget.cpp \
    object.cpp \
    order.cpp \
    socket.cpp \
    tabwidget.cpp \
    updater.cpp \
    viewer.cpp \
    widget.cpp

HEADERS += \
    Autorization/autorazationwidget.h \
    Autorization/autorization.h \
    BaseProfile/baseprofile.h \
    BaseProfile/baseprofiledata.h \
    BaseProfile/baseprofileeditor.h \
    BaseProfile/baseprofilewidget.h \
    Cards/cardeditor.h \
    Cards/cards.h \
    Cards/cardsdata.h \
    Cards/cardslist.h \
    Dialog/dialog.h \
    Dialog/dialogdata.h \
    Dialog/dialogwidget.h \
    DoctorProfile/doctorpackageedit.h \
    DoctorProfile/doctorprofile.h \
    DoctorProfile/doctorprofiledata.h \
    DoctorProfile/doctorprofilewidget.h \
    Messages/messages.h \
    Messages/messagesdata.h \
    Messages/messageswidget.h \
    PatientProfile/patientprofile.h \
    PatientProfile/patientprofiledata.h \
    PatientProfile/patientprofilewidget.h \
    Search/patientsearchwidget.h \
    Search/search.h \
    Search/searchdata.h \
    browser.h \
    button.h \
    globaldata.h \
    mainwidget.h \
    messages.h \
    object.h \
    order.h \
    packer.h \
    socket.h \
    tabwidget.h \
    updater.h \
    viewer.h \
    widget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    webview.qml

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}
