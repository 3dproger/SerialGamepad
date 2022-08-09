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
