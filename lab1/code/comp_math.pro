TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    lagrange.cpp \
    quanc8.cpp \
    SPLINES.CPP \
    old.cpp

HEADERS += \
    lagrange.h \
    quanc8.h \
    SPLINES.H \
    main.h