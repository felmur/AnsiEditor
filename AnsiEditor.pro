TARGET=ansieditor

QT       += core gui core5compat

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ansiwidget.cpp \
    gliphform.cpp \
    main.cpp \
    mainwindow.cpp \
    palette.cpp \
    qcodepage437codec.cpp \
    sauceform.cpp \
    toolbox.cpp

HEADERS += \
    ansiwidget.h \
    common.h \
    gliphform.h \
    mainwindow.h \
    palette.h \
    qcodepage437codec.h \
    sauce.h \
    sauceform.h \
    toolbox.h

FORMS += \
    gliphform.ui \
    mainwindow.ui \
    palette.ui \
    sauceform.ui \
    toolbox.ui

# Default rules for deployment.
 unix:!android:
    target.path = /usr/bin/
    desktop.path = /usr/share/applications/
    desktop.files = AnsiEditor.desktop
    icon.path = /usr/share/icons/
    icon.files = image/AnsiEditor.png
!isEmpty(target.path): INSTALLS += target desktop icon

RESOURCES += \
    resource.qrc
