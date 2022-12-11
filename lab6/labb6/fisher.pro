TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES = Event.cpp Fish.cpp main.cpp Simulation.cpp
#SOURCES = test-harness-myvector.cpp
#SOURCES = test-harness-myprio.cpp
HEADERS = $$files(*.h,true)

DISTFILES += \
    answers.txt
