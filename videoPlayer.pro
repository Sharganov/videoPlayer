TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += console c++11

LIBS += -lboost_system
LIBS += -pthread

LIBS += -L/usr/local/lib \
-lopencv_core \
-lopencv_imgproc \
-lopencv_highgui \
-lopencv_ml \
-lopencv_video \
-lopencv_features2d \
-lopencv_calib3d \
-lopencv_objdetect \
-lopencv_flann


SOURCES += main.cpp \
    videoreader.cpp \
    videoeditor.cpp \
    buffer.cpp

HEADERS += \
    buffer.h \
    videoreader.h \
    videoeditor.h

