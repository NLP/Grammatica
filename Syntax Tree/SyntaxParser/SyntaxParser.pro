TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
#CONFIG -= qt
CONFIG += c++11
QT += sql
SOURCES += main.cpp \
    parser.cpp \
    syntaxtree.cpp

HEADERS += \
    parser.h \
    syntaxtree.h \
    Tree.h

