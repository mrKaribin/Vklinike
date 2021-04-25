
QT += gui core sql network

CONFIG += c++15
CONFIG -= app_bundle

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
        Datas/doctors.cpp \
        Datas/patients.cpp \
        Datas/users.cpp \
        client.cpp \
        global.cpp \
        main.cpp \
        server.cpp \
        tester.cpp


qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
        Datas/cards.h \
        Datas/comments.h \
        Datas/dialogs.h \
        Datas/doctors.h \
        Datas/messages.h \
        Datas/packages.h \
        Datas/patients.h \
        Datas/specializations.h \
        Datas/subscriptions.h \
        Datas/tariffs.h \
        Datas/users.h \
        client.h \
        global.h \
        packer.h \
        server.h \
        tester.h
