CONFIG += console debug_and_release
CONFIG -= app_bundle
QT -= core gui
TEMPLATE = app

CONFIG(release, debug|release) {
  DEFINES += NDEBUG
}

include(distancer.pri)
SOURCES += \
    test_helper.cpp \
    test_do_simulation.cpp \
    test_bpp.cpp \
    main_test.cpp

# Must use g++-4.8 and C++11 due to compatibility with R
QMAKE_CXX = g++-4.8
QMAKE_LINK = g++-4.8
QMAKE_CC = gcc-4.8
QMAKE_CXXFLAGS += -Wall -Wextra -Weffc++ -Werror -std=c++11

# Boost.Test
LIBS += -lboost_unit_test_framework

# Bio++
LIBS += -lbpp-core -lbpp-seq -lbpp-phyl -lbpp-popgen -lbpp-qt -lbpp-raa
