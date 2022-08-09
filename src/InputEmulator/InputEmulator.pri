INCLUDEPATH += $$PWD
SOURCES += $$PWD/inputemulator.cpp

HEADERS += $$PWD/abstractplatforminputemulator.h \
	$$PWD/inputemulator.h \
        $$PWD/inputemulatortypes.h

win32 {
SOURCES += \
    $$PWD/winapiinputemulator.cpp

HEADERS += \
    $$PWD/targetver.h \
    $$PWD/winapiinputemulator.h
}

linux: {
SOURCES += \
    $$PWD/x11inputemulator.cpp

HEADERS += \
    $$PWD/x11inputemulator.h

LIBS += -L/usr/X11/lib -L/usr/local/lib -lX11 -lXtst
}
