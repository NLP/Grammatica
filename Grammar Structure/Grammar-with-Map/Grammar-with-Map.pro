TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
SOURCES += main.cpp \
    grammar.cpp \
    cfgzero.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    grammar.h \
    cfgzero.h

