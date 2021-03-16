QT		+= core
QT		+= xml
TARGET		= user

INCLUDEPATH	 = inc ../Params/inc ../World/inc

include(../Params/params.pri)
include(../World/world.pri)
include(../Params/generated/generated.pri)
include(user.pri)

SOURCES		+= main.cpp

CONFIG		+= qt warn_on release
QMAKE_CXXFLAGS_RELEASE	= -std=gnu++0x
QMAKE_CXXFLAGS_RELEASE	+= -std=c++11
OBJECTS_DIR	= ../obj
