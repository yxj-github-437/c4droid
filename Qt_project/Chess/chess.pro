QT += widgets

HEADERS       = Stone.h\
                Board.h
SOURCES       = main.cpp \
                Stone.cpp\
                Board.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/application
INSTALLS += target

simulator: warning(This example might not fully work on Simulator platform)
