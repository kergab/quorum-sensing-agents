QT		+= core
QT		+= widgets
QT		+= gui
QT		+= xml
TARGET		= world

INCLUDEPATH	 = inc ../Params/inc ../User/inc ../World/inc

include(../Params/params.pri)
include(../Params/generated/generated.pri)
include(../World/world.pri)

HEADERS		+= inc/WorldWidget.hpp
HEADERS		+= inc/Gui.hpp

SOURCES		+= src/Gui.cpp
SOURCES		+= main.cpp

CONFIG		+= qt warn_on release
QMAKE_CXXFLAGS_RELEASE	= -std=gnu++0x
QMAKE_CXXFLAGS_RELEASE	+= -std=c++11
OBJECTS_DIR	= ../obj
MOC_DIR	= ../obj
