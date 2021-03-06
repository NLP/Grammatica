TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
#CONFIG -= qt
CONFIG += c++11
QT += sql
SOURCES += main.cpp \
    parser.cpp \
    syntaxtree.cpp \
    syntaxword.cpp \
    ../../Parser/Tagger/word.cpp \
    ../../Parser/Tokenizer/token.cpp \
    ../grammar.cpp \
#    ../../Grammar Structure/Grammar-with-Map/cfgzero.cpp \
    ../cfgzero.cpp


HEADERS += \
    parser.h \
    syntaxtree.h \
    Tree.h \
    syntaxword.h \
    ../../Parser/Tagger/word.h \
    ../../Parser/Tokenizer/token.h \
    ../../CONFIG/config.h \
    ../grammar.h \
#    ../../Grammar Structure/Grammar-with-Map/cfgzero.h \
    ../cfgzero.h


