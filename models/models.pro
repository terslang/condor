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
HEADERS += sqlobjects/ballotobject.h
HEADERS += objects/ballot.h
SOURCES += objects/ballot.cpp
HEADERS += ballotservice.h
SOURCES += ballotservice.cpp
HEADERS += sqlobjects/ballotchoiceobject.h
HEADERS += objects/ballotchoice.h
SOURCES += objects/ballotchoice.cpp
HEADERS += ballotchoiceservice.h
SOURCES += ballotchoiceservice.cpp
HEADERS += homeservice.h
SOURCES += homeservice.cpp
HEADERS += resultservice.h
SOURCES += resultservice.cpp
HEADERS += sqlobjects/pairwisecontestobject.h
HEADERS += objects/pairwisecontest.h
SOURCES += objects/pairwisecontest.cpp
HEADERS += pairwisecontestservice.h
SOURCES += pairwisecontestservice.cpp
