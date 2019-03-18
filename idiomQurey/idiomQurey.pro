#-------------------------------------------------
#
# Project created by QtCreator 2016-04-25T09:13:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = idiomQurey
TEMPLATE = app
#CONFIG  += qaxcontainer
#CONFIG += c++11

#DEFINES += ANDROID
#DEFINES += DEBUG
DEFINES += DESKTOP

QT +=sql

SOURCES += main.cpp\
        mainwindow.cpp \
    key.cpp \
    keyboard.cpp \
    tool.cpp \
    rootwidget.cpp \
    clicklabel.cpp \
    readexcel.cpp \
    idiom.cpp \
    resultlink.cpp \
    query.cpp \
    showarea.cpp

HEADERS  += mainwindow.h \
    key.h \
    keyboard.h \
    variable.h \
    tool.h \
    Singleton/call_once.h \
    Singleton/singleton.h \
    rootwidget.h \
    clicklabel.h \
    readexcel.h \
    idiom.h \
    type.h \
    resultlink.h \
    query.h \
    showarea.h \
    macro.h

if(contains(DEFINES,ANDROID)){
DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/assets/image/KeyBoard/16.png \
    android/assets/image/KeyBoard/17.png \
    android/assets/image/KeyBoard/18.png \
    android/assets/image/KeyBoard/19.png \
    android/assets/image/KeyBoard/20.png \
    android/assets/image/KeyBoard/21.png \
    android/assets/image/KeyBoard/22.png \
    android/assets/image/KeyBoard/23.png \
    android/assets/image/KeyBoard/24.png \
    android/assets/image/KeyBoard/a.png \
    android/assets/image/KeyBoard/b.png \
    android/assets/image/KeyBoard/backspace.png \
    android/assets/image/KeyBoard/c.png \
    android/assets/image/KeyBoard/d.png \
    android/assets/image/KeyBoard/e.png \
    android/assets/image/KeyBoard/enter.png \
    android/assets/image/KeyBoard/f.png \
    android/assets/image/KeyBoard/g.png \
    android/assets/image/KeyBoard/h.png \
    android/assets/image/KeyBoard/i.png \
    android/assets/image/KeyBoard/inputBox.png \
    android/assets/image/KeyBoard/j.png \
    android/assets/image/KeyBoard/k.png \
    android/assets/image/KeyBoard/l.png \
    android/assets/image/KeyBoard/m.png \
    android/assets/image/KeyBoard/mainKeyboard.png \
    android/assets/image/KeyBoard/n.png \
    android/assets/image/KeyBoard/o.png \
    android/assets/image/KeyBoard/spacebar.png \
    android/assets/resource/idiom.db \
    android/assets/image/icon.png

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
}
