QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG += c++11
CONFIG -= app_bundle

LIBS += -L$${OUT_PWD}/../../src
include(../../src/PrefixTickLabels.pri)

TEMPLATE = app

SOURCES +=  tst_tickgenerationtest.cpp
