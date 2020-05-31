QT += quick
CONFIG += c++11 warn_on
SOURCES += demo.cpp
SOURCES += PrefixTickLabelsModel.cpp
RESOURCES += demo.qrc

HEADERS += PrefixTickLabelsModel.h

LIBS += -L$${OUT_PWD}/../src
include(../src/PrefixTickLabels.pri)
