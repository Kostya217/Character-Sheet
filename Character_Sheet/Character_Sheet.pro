QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    damageoutput.cpp \
    heal.cpp \
    impactforce.cpp \
    main.cpp \
    charactersheet.cpp

HEADERS += \
    charactersheet.h \
    damageoutput.h \
    heal.h \
    impactforce.h

FORMS += \
    charactersheet.ui \
    damageoutput.ui \
    heal.ui \
    impactforce.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    resource_image/GURPS_Logo.jpg \
    resource_image/GURPS_Logo.png \
    resource_image/Swing_dmg.jpg \
    resource_image/Thrust_dmg.jpg \
    resourec/GURPS_Logo.jpg
