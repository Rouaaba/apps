QT += core gui widgets testlib

CONFIG += console
CONFIG -= app_bundle

SOURCES += test_interactive_app.cpp
INCLUDEPATH += /usr/include/x86_64-linux-gnu/qt5
LIBS += -L/usr/lib/x86_64-linux-gnu/qt5
