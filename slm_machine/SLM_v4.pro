# -------------------------------------------------
# Project created by QtCreator 2009-02-08T14:00:41
# -------------------------------------------------
QT += network
TARGET = SLM_v4
TEMPLATE = app
SOURCES += main.cpp \
    slm_machine.cpp \
    slm_server.cpp \
    slm_socketmanager.cpp \
    buddymanager.cpp \
    slm_client.cpp \
    securestring.cpp \
    fileCrypto/filecrypter.cpp \
    dosyasunucusu.cpp \
    fileSenderThread/filesender.cpp
HEADERS += slm_machine.h \
    slm_server.h \
    slm_socketmanager.h \
    buddymanager.h \
    slm_client.h \
    securestring.h \
    fileCrypto/filecrypter.h \
    dosyasunucusu.h \
    fileSenderThread/filesender.h
FORMS += slm_machine.ui \
    addBuddy.ui \
    slm_client.ui \
    encryptionKeyDialog.ui
RESOURCES += resources/slm_resources.qrc
