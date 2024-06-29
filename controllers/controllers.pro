TARGET = controller
TEMPLATE = lib
CONFIG += shared x86_64
QT += network sql xml qml
QT -= gui
DEFINES += TF_DLL
DESTDIR = ../lib
INCLUDEPATH += ../helpers ../models
DEPENDPATH  += ../helpers ../models
LIBS += -L../lib -lhelper -lmodel
MOC_DIR = .obj/
OBJECTS_DIR = .obj/

include(../appbase.pri)

HEADERS += applicationcontroller.h
SOURCES += applicationcontroller.cpp
HEADERS += electioncontroller.h
SOURCES += electioncontroller.cpp
HEADERS += optioncontroller.h
SOURCES += optioncontroller.cpp
HEADERS += ballotcontroller.h
SOURCES += ballotcontroller.cpp
HEADERS += homecontroller.h
SOURCES += homecontroller.cpp
