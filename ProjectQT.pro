QT       += core gui sql
QT += sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Database.cpp \
    aidetection.cpp \
    choose.cpp \
    codeupload.cpp \
    dashboard.cpp \
    detection.cpp \
    filesDatabase.cpp \
    main.cpp \
    mainwindow.cpp \
    plagirism.cpp \
    plg.cpp \
    signup.cpp \
    upload.cpp

HEADERS += \
    Database.h \
    aidetection.h \
    choose.h \
    codeupload.h \
    dashboard.h \
    detection.h \
    filesDatabase.h \
    mainwindow.h \
    plagirism.h \
    plg.h \
    signup.h \
    upload.h

FORMS += \
    aidetection.ui \
    choose.ui \
    codeupload.ui \
    dashboard.ui \
    detection.ui \
    mainwindow.ui \
    signup.ui \
    upload.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

