TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
SOURCES += main.cpp \
    grammar.cpp

HEADERS += \
    grammar.h \
    Graph.h \
    LabelledGraph.h \
    ContexFreeGrammarZero.h

