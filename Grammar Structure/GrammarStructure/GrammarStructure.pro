TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
SOURCES += main.cpp \
    grammar.cpp \
    cfgzero.cpp

HEADERS += \
    Graph.h \
    LabeledGraph.h \
    grammar.h \
    cfgzero.h \
    VectorContainer.h

