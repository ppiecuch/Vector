
#
# debug        - build debug version of application
# with_widgets - include widgets frameworks and modules
# with_xml     - include xml support for serialization
#

CONFIG += debug with_widgets

QT += openglextensions

CONFIG(with_widgets): QT += widgets
CONFIG(with_xml): QT += xml

SOURCES += $$PWD/main.cpp \
           $$PWD/application.cpp \
           $$PWD/openglconfig.cpp \
           $$PWD/openglrenderer.cpp \
           $$PWD/openglsurface.cpp \
           $$PWD/threadrenderer.cpp \
           $$PWD/qinputeventrecorder.cpp

HEADERS += $$PWD/application.h \
           $$PWD/openglconfig.h \
           $$PWD/openglrenderer.h \
           $$PWD/openglsurface.h \
           $$PWD/threadrenderer.h \
           $$PWD/qinputeventrecorder.h \
           $$PWD/qopenglerrorcheck.h \
           $$PWD/common.h \
           $$PWD/optionparser.h

RESOURCES += $$PWD/res.qrc           
ICONS += $$PWD/res/icons/icon.icns

INCLUDEPATH += $$PWD
