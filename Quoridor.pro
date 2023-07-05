QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    App/exitcommand.cpp \
    App/initcommand.cpp \
    Common/commands.cpp \
    ViewModel/executeCommand.cpp \
    ViewModel/state/abstractStateNode.cpp \
    ViewModel/state/activePlayerStateNode.cpp \
    ViewModel/state/atomicExecuteStateNode.cpp \
    ViewModel/state/operationStateNode.cpp \
    ViewModel/stateTransitionCommand.cpp \
    ViewModel/statemachine.cpp \
    ViewModel/viewModel.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    App/exitcommand.h \
    App/initcommand.h \
    Common/commands.h \
    Common/common.h \
    ViewModel/executeCommand.h \
    ViewModel/state/abstractStateNode.h \
    ViewModel/state/activePlayerStateNode.h \
    ViewModel/state/atomicExecuteStateNode.h \
    ViewModel/state/operationStateNode.h \
    ViewModel/stateTransitionCommand.h \
    ViewModel/statemachine.h \
    ViewModel/viewModel.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
