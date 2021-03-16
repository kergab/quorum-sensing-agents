QT		+= core
QT		+= xml
TARGET		= generate

INCLUDEPATH	 = inc

include(params.pri)

SOURCES		+= main.cpp

CONFIG		+= qt warn_on release
QMAKE_CXXFLAGS_RELEASE	= -std=gnu++0x
QMAKE_CXXFLAGS_RELEASE	+= -std=c++11
OBJECTS_DIR	= ../obj
