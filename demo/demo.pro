QT += quick
CONFIG += c++11
SOURCES += demo.cpp
SOURCES += PrefixTickLabelsModel.cpp
RESOURCES += demo.qrc

HEADERS += PrefixTickLabelsModel.h

LIBS += -L$${OUT_PWD}/../src
include(../src/PrefixTickLabels.pri)
