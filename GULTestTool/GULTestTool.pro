QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CGNSSJsonFile.cpp \
    CGNSSTextFile.cpp \
    RtkLib/ephemeris.c \
    RtkLib/preceph.c \
    RtkLib/qzslex.c \
    RtkLib/rtcm.c \
    RtkLib/rtcm2.c \
    RtkLib/rtcm3.c \
    RtkLib/rtcm3e.c \
    RtkLib/rtkcmn.c \
    RtkLib/sbas.c \
    TestFunc.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CGNSSJsonFile.h \
    CGNSSTextFile.h \
    ConstantDef.h \
    GULLib/GNSSCommonStruct.h \
    GULLib/GNSSMathInterface.h \
    GULLib/GNSSUtilityInterface.h \
    RtkLib/rtklib.h \
    TestFunc.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

#CONFIG(debug, debug|release):LIBS += -LE:/Projects/GNSSUtilityLib/GNSSUtilityLibrary/GULTestTool/GULTestTool/RtkLib/debug \
#        -lRTKLIB
#CONFIG(release, debug|release):LIBS += -LE:/Projects/GNSSUtilityLib/GNSSUtilityLibrary/GULTestTool/GULTestTool/RtkLib/release \
#        -lRTKLIB

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
