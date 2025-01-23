QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database.cpp \
    editpost.cpp \
    login_signup.cpp \
    main.cpp \
    mainwindow.cpp \
    post.cpp \
    requests.cpp \
    requestwidget.cpp \
    settings.cpp \
    suggestwidget.cpp \
    user.cpp

HEADERS += \
    database.h \
    editpost.h \
    login_signup.h \
    mainwindow.h \
    post.h \
    requests.h \
    requestwidget.h \
    settings.h \
    suggestwidget.h \
    user.h

FORMS += \
    editpost.ui \
    login_signup.ui \
    mainwindow.ui \
    requests.ui \
    settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Pictures.qrc
