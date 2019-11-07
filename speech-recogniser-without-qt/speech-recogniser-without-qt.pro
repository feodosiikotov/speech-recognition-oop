TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    frame.cpp \
    wavdecoder.cpp

HEADERS += \
    frame.h \
    wavdecoder.h
