QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
QT += sql
QT += network
QT += gui
QT += core5compat
QT += concurrent
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    adminui.cpp \
    batchimport.cpp \
    book.cpp \
    br_re_cp.cpp \
    captchabox/captchabox.cpp \
    changepassdialog.cpp \
    compensatedialog.cpp \
    deleteinfo.cpp \
    encryptpass.cpp \
    insertinfo.cpp \
    interactive_buttons/interactivebuttonbase.cpp \
    labeled_edit/bottomlineedit.cpp \
    labeled_edit/labelededit.cpp \
    login.cpp \
    main.cpp \
    reader.cpp \
    readerui.cpp \
    readonlydelegate.cpp \
    smtp/smtp.cpp \
    toast/toast.cpp

HEADERS += \
    admin.h \
    adminui.h \
    batchimport.h \
    book.h \
    br_re_cp.h \
    captchabox/captchabox.h \
    changepassdialog.h \
    compensatedialog.h \
    deleteinfo.h \
    encryptpass.h \
    insertinfo.h \
    interactive_buttons/interactivebuttonbase.h \
    labeled_edit/bottomlineedit.h \
    labeled_edit/labelededit.h \
    login.h \
    reader.h \
    readerui.h \
    readonlydelegate.h \
    smtp/smtp.h \
    toast/toast.h

FORMS += \
    adminui.ui \
    br_re_cp.ui \
    changepassdialog.ui \
    compensatedialog.ui \
    deleteinfo.ui \
    insertinfo.ui \
    login.ui \
    readerui.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=
