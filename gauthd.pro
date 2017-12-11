QT += core sql network
QT -= gui

TARGET = gauthd
CONFIG += console 64bit
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
    Protocol/Game2AU.cpp \
    Protocol/GetAddCashSN.cpp

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
    Protocol/Game2AU.h \
    Protocol/GetAddCashSN.h

QMAKE_LFLAGS += -static-libstdc++ -static-libgcc -static

CONFIG(32bit) {
    LIBS += -L$$PWD/../../../../opt/Qt/mysql/x32/lib/libmysqlclient.a
}
CONFIG(64bit) {
    LIBS += -L$$PWD/../../../../opt/Qt/mysql/x64/lib/libmysqlclient.a
}
