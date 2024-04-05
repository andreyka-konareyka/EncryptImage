TARGET = EncrtyptImage
TEMPLATE = app
VERSION = 0.0.1

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DESTDIR = bin
OBJECTS_DIR = .build
UI_DIR = .build
RCC_DIR = .build
MOC_DIR = .build

SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp

HEADERS += \
    src/MainWindow.h

FORMS += \
    src/MainWindow.ui

RESOURCES += \
    EncryptImageResources.qrc

