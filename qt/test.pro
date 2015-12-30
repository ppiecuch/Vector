TEMPLATE = app
QT += \
  gui openglextensions \  # for library
  widgets                 # for demo application
CONFIG += debug
CONFIG -= app_bundle

SOURCES += \
	../test/VectorTestImpl.c \
	VectorTest.cpp
HEADERS += \
	../test/VectorTestImpl.h \
	VectorTest.cpp

include("vector.pri")
include("qtgl/qtgl.pri")
include("common.pri")
