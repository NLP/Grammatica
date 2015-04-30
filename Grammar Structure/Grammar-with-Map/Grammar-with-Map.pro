TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
#CONFIG -= qt
QT += sql
CONFIG += c++11
SOURCES += main.cpp \
    grammar.cpp \
    cfgzero.cpp \
    cfgq.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    grammar.h \
    cfgzero.h \
    cfgq.h

