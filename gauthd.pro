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
    Protocol/AnnounceZoneid.cpp \
    Protocol/MatrixPasswd.cpp \
    Database.cpp \
    Protocol/UserLogin.cpp \
    Protocol/AnnounceZoneid2.cpp \
    Protocol/AnnounceZoneid3.cpp \
    Protocol/UserLogout.cpp \
    Protocol/QueryUserPrivilege.cpp \
    Protocol/MatrixToken.cpp \
    Protocol/GetAddCashSN.cpp \
    Protocol/Game2AU.cpp

DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_LFLAGS += -static-libstdc++ -static-libgcc -static

HEADERS += \
    AuthServer.h \
    Settings.h \
    AuthClient.h \
    Utils.h \
    Network/OctetsStream.h \
    Protocol/AnnounceZoneid.h \
    Protocol/MatrixPasswd.h \
    Database.h \
    Network/Octets.h \
    Protocol/UserLogin.h \
    Protocol/AnnounceZoneid2.h \
    Protocol/AnnounceZoneid3.h \
    Protocol/UserLogout.h \
    Protocol/QueryUserPrivilege.h \
    Protocol/MatrixToken.h \
    Protocol/GetAddCashSN.h \
    Protocol/Game2AU.h

unix:!macx: LIBS += -L$$PWD/../../../../opt/Qt/mysql/x32/lib/ -lmysqlclient

INCLUDEPATH += $$PWD/../../../../opt/Qt/mysql/x32/include
DEPENDPATH += $$PWD/../../../../opt/Qt/mysql/x32/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../opt/Qt/mysql/x32/lib/libmysqlclient.a
