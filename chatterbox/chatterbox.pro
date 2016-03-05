TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .
QT += network
QT +=sql
QT += widgets
RESOURCES += images.qrc
RC_FILE  +=chat.rc
FORMS   += MainWindow.ui 

HEADERS += MainWindow.h 

SOURCES += MainWindow.cpp \
           main.cpp

