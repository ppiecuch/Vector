TEMPLATE = app
QT += widgets

CONFIG += debug
CONFIG -= app_bundle

SOURCES += \
	main.cpp \
	../test/VectorTestImpl.c \
	../test/VectorDemoImpl.c \
	VectorTest.cpp
HEADERS += \
	stb_easy_font.h \
	../test/VectorTestImpl.h \
	VectorTest.cpp

include("vector.pri")
include("common.pri")
