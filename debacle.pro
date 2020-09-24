QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Debacle
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
        file_manager/file_manager.cpp \
        lang/lang.cpp \
        main.cpp \
        main_window/main_window.cpp \
        test/test.cpp \
        test_layout/test_layout.cpp

HEADERS += \
        file_manager/file_manager.h \
        lang/lang.h \
        main_window/main_window.h \
        env.h \
        test/test.h \
        test_layout/test_layout.h
