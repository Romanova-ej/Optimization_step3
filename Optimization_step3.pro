#-------------------------------------------------
#
# Project created by QtCreator 2017-11-18T17:24:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Optimization_step3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Area.cpp \
    Criterion.cpp \
    Function.cpp \
    Optimization.cpp \
    other.cpp \
    stdafx.cpp \
    QMethodDlg.cpp \
    QFuncDlg.cpp \
    qcustomplot.cpp \
    RSOptions.cpp

HEADERS  += mainwindow.h \
    HArea.h \
    HCriterion.h \
    HFunction.h \
    HOptimization.h \
    Hother.h \
    stdafx.h \
    targetver.h \
    QMethodDlg.h \
    QFuncDlg.h \
    qcustomplot.h \
    RSOptions.h

FORMS    += mainwindow.ui \
    QMethodDlg.ui \
    QFuncDlg.ui \
    RSOptions.ui

RESOURCES += \
    fun.qrc \
    Image/image.qrc

DISTFILES += \
    Image/cub.png \
    Image/cub1.png \
    Image/funct.png \
    Image/function.png \
    Image/man.png \
    Image/sin.png
