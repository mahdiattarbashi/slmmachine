#ifndef SLM_MACHINE_H
#define SLM_MACHINE_H

#include <QtGui/QMainWindow>
#include <QtGui/QDialog>
#include <QtGui/qevent.h>
#include <QHostAddress>
#include <QStringListModel>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QProgressDialog>
#include "slm_client.h"
#include "ui_slm_machine.h"
#include "ui_encryptionKeyDialog.h"
#include "ui_addBuddy.h"
#include "buddymanager.h"
#include "fileServerThread/fileserver.h"


namespace Ui
{
    class slm_machineClass;
}

class slm_machine : public QMainWindow
{
    Q_OBJECT

public:
    slm_machine(QWidget *parent = 0);
    ~slm_machine();
    QDialog *addBuddyScreenDialog;
    QDialog *encryptionKeyWindow;
    QStringListModel *buddyModel;
    QProgressDialog *progress;
    quint32 receivingFileSize;

    QList<slm_client *> clientList;
    QStringList activeClientAliasList;

    buddyManager *buddies;
    slm_client *newClient;

    void closeEvent( QCloseEvent *closeEvent );
    void changeEvent(QEvent *event); // to catch minimize event and send the application to the Tray

public slots:
    void addBuddyPressed();
    void removeBuddypressed();
    void messageHandler(QByteArray,QHostAddress);
    void L_addBuddyButtonPressed();
    void L_cancelAddBuddyButtonPressed();
    void closeApplication();
    void buddyPressed(QModelIndex);
    void clearClientFromActiveList(QString);
    void aboutQTPressed();
    void aboutSLMPressed();
    void encryptionKeyPressed();
    void setEncryptionKey();
    void cancelEncryptionKey();
    void iconActivated(QSystemTrayIcon::ActivationReason);
    void slotPlaceToTray();
    void incomingFileSlot(QString,QString,quint32);
    void incomingFileTransferCompleted();
    void transferIsCancelled();
    void ongoingTransferExists();
    void updateReceivingProgress(quint32);
    void showTrayMessageFileSentCompleted();

private:
    Ui::slm_machineClass *ui;
    Ui::addBuddyScreen *ui_addBuddyScreen;
    Ui::encryptionKeyDialog * ui_encryption;

    bool IPAddressValidator(QString);
    void clientCreation(int);

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    QAction *restoreAction;
    QAction *quitAction;
    fileServer *FServer;
    void createTrayIcon();
    void createActions();

signals:
    void signalPlaceToTray();
};

#endif // SLM_MACHINE_H