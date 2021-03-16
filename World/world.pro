QT		+= core
QT		+= xml
TARGET		= world

INCLUDEPATH	 = inc ../Params/inc ../User/inc

include(../Params/params.pri)
include(../Params/generated/generated.pri)
include(../World/world.pri)

SOURCES		+= main.cpp

CONFIG		+= qt warn_on release
QMAKE_CXXFLAGS_RELEASE	= -std=gnu++0x
QMAKE_CXXFLAGS_RELEASE	+= -std=c++11
OBJECTS_DIR	= ../obj
