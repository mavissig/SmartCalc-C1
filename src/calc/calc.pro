QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../functions/parser.c \
    ../functions/stack.c \
    ../functions/validation.c \
    ../functions/notation.c \
    ../functions/calc.c \
    main.cpp \
    qcustomplot.cpp \
    calcwindow.cpp
    

HEADERS += \
    ../headers/lexem_t.h \
    ../headers/parser.h \
    ../headers/stack.h \
    ../headers/stack_t.h \
    ../headers/validation.h \
    ../headers/notation.h \
    ../headers/calc.h \
    qcustomplot.h \
    calcwindow.h

FORMS += \
    calcwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
