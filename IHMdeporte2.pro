#-------------------------------------------------
#
# Project created by QtCreator 2017-02-22T16:06:02
#
#-------------------------------------------------

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IHMdeporte2
TEMPLATE = app

QT += widgets
QT += gui
QT += core
#CONFIG += qwt
CONFIG += release


#CONFIG(debug, debug|release) {
    # Debug
   # QWTLIB = libqwtd
#}
#else {
    # Release
   # QWTLIB = libqwt
#}

#QWT_SRC = D:\Qwt\qwt-6.1.3\qwt-6.1.3
#QWT_BIN = D:\Qwt\qwt-6.1.3\build-qwt-Desktop_Qt_5_4_2_MinGW_32bit2-Debug
#INCLUDEPATH += $${QWT_SRC}\src
#LIBS += $${QWT_BIN}\lib\$${QWTLIB}.a
#DEFINES += QWT_DLL


#QWTBASE=C:\qwt-6.1.3
#export QT_PLUGIN_PATH=$QWTBASE/plugins
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$QWTBASE/lib
#export QMAKEFEATURES=$QWTBASE/features

#CONFIG += release

#INCLUDEPATH += C:\qwt-6.1.3\include\
#INCLUDEPATH += D:\Documents\Inge 3\Qt\build-IHMdeporte2-Android_for_armeabi_v7a_GCC_4_9_Qt_5_5_1-Release\android-build\include
#DEPENDPATH += D:\Documents\Inge 3\Qt\build-IHMdeporte2-Android_for_armeabi_v7a_GCC_4_9_Qt_5_5_1-Release\android-build\libs

#QTPLUGIN += qjpeg

#LIBS += D:\Qwt\qwt-6.1.3\qwt-6.1.3\lib

#debug {
  # LIBS += C:\qwt-6.1.3\lib -lqwtd
#} else {
 #  LIBS += C:\qwt-6.1.3\lib -lqwt
#}


#DEFINES += QWT_DLL

#QT_PLUGIN_PATH : C:\Qwt-6.0.1\plugins


SOURCES += main.cpp\
        ihmdeportee.cpp

HEADERS  += ihmdeportee.h

FORMS    += ihmdeportee.ui

CONFIG += mobility
MOBILITY =

OTHER_FILES += \
#android-build\libs\armeabi-v7a\libplugins_imageformats_libqjpeg.so
#D:\Documents\Inge 3\Qt\build-IHMdeporte2-Android_for_armeabi_v7a_GCC_4_9_Qt_5_5_1-Debug\dangerj.jpg

RESOURCES += \
    images.qrc







