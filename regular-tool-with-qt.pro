QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    main.cpp \
    mainwindow.cpp \
    regex_find.cpp \
    regex_match.cpp \
    regex_replacement.cpp \
    regular_file_search.cpp

HEADERS += \
    about.h \
    global.h \
    mainwindow.h \
    regex_find.h \
    regex_match.h \
    regex_replacement.h \
    regular_file_search.h

FORMS += \
    about.ui \
    mainwindow.ui \
    regex_find.ui \
    regex_match.ui \
    regex_replacement.ui \
    regular_file_search.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

RC_ICONS = "regular.ico"
