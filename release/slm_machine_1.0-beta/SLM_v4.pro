# -------------------------------------------------
# Project created by QtCreator 2009-02-08T14:00:41
# -------------------------------------------------
QT += network
TARGET = SLM_v4
TEMPLATE = app
INCLUDEPATH += include \
               src \
               fileCrypto \
               fileSenderThread \
               fileServerThread
SOURCES += src/main.cpp \
    src/slm_client.cpp \
    src/slm_machine.cpp \
    src/slm_server.cpp \
    src/slm_socketmanager.cpp \
    src/securestring.cpp \
    src/buddymanager.cpp \
    fileCrypto/filecrypter.cpp \
    fileSenderThread/filesender.cpp \
    fileServerThread/fileserver.cpp
HEADERS += include/*.h \
    fileCrypto/filecrypter.h \
    fileSenderThread/filesender.h \
    fileServerThread/fileserver.h
FORMS += ui/slm_machine.ui \
    ui/slm_client.ui \
    ui/encryptionKeyDialog.ui \
    ui/addBuddy.ui
RESOURCES += resources/slm_resources.qrc
