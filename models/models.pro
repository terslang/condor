TARGET = model
TEMPLATE = lib
CONFIG += shared x86_64
QT += sql qml
QT -= gui
DEFINES += TF_DLL
DESTDIR = ../lib
INCLUDEPATH += ../helpers
DEPENDPATH  += ../helpers
LIBS += -L../lib -lhelper
MOC_DIR = .obj/
OBJECTS_DIR = .obj/

include(../appbase.pri)
HEADERS += sqlobjects/electionobject.h
HEADERS += objects/election.h
SOURCES += objects/election.cpp
HEADERS += electionservice.h
SOURCES += electionservice.cpp
HEADERS += sqlobjects/optionobject.h
HEADERS += objects/option.h
SOURCES += objects/option.cpp
HEADERS += optionservice.h
SOURCES += optionservice.cpp
