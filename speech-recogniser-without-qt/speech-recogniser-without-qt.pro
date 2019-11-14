TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    frame.cpp \
    wavdecoder.cpp \
    frameprocessor.cpp \
    wordsplitter.cpp \
    mfccprocessor.cpp

HEADERS += \
    frame.h \
    wavdecoder.h \
    frameprocessor.h \
    wordsplitter.h \
    mfccprocessor.h
