QT += core sql network
QT -= gui

CONFIG += c++11

TARGET = gauthd
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    AuthServer.cpp \
    Settings.cpp \
    AuthClient.cpp \
    Utils.cpp \
    Network/OctetsStream.cpp \
    Handle/AnnounceZoneid.cpp \
    Handle/MatrixPasswd.cpp \
    Database.cpp \
    Handle/UserLogin.cpp \
    Handle/AnnounceZoneid2.cpp \
    Handle/AnnounceZoneid3.cpp \
    Handle/UserLogout.cpp \
    Handle/QueryUserPrivilege.cpp \
    Handle/MatrixToken.cpp \
    Handle/GetAddCashSN.cpp

DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_LFLAGS += -static-libstdc++ -static-libgcc -static

HEADERS += \
    AuthServer.h \
    Settings.h \
    AuthClient.h \
    Network/RC4.h \
    Network/RC4EncDec.h \
    Utils.h \
    Network/OctetsStream.h \
    Handle/AnnounceZoneid.h \
    Handle/MatrixPasswd.h \
    Database.h \
    Network/Octets.h \
    Handle/UserLogin.h \
    Handle/AnnounceZoneid2.h \
    Handle/AnnounceZoneid3.h \
    Handle/UserLogout.h \
    Handle/QueryUserPrivilege.h \
    Handle/MatrixToken.h \
    Handle/GetAddCashSN.h

unix:!macx: LIBS += -L$$PWD/../../../../opt/Qt/mysql/x64/lib/ -lmysqlclient

INCLUDEPATH += $$PWD/../../../../opt/Qt/mysql/x64/include
DEPENDPATH += $$PWD/../../../../opt/Qt/mysql/x64/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../opt/Qt/mysql/x64/lib/libmysqlclient.a
