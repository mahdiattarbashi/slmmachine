#include "slm_machine.h"
#include "slm_server.h"
#include <QDebug>
#include <QMessageBox>


slm_machine::slm_machine(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::slm_machineClass)
{
    ui->setupUi(this);

    //Buddy Management
    buddies = new buddyManager();
    buddies->loadBuddiesAndIPs();
    buddyModel = new QStringListModel();
    buddyModel->setStringList(buddies->AliasBuddyList);

    // Buddy List UI Management
    ui->buddyList->setModel(buddyModel);
    ui->buddyList->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Server Management
    slm_server *ahmet = slm_server::getInstance();
    connect(ahmet, SIGNAL(sendtoUI(QByteArray,QHostAddress)),this,SLOT(messageHandler(QByteArray,QHostAddress)));

    //UI connections
    connect(ui->addBuddyButton, SIGNAL(clicked()),this, SLOT(addBuddyPressed()));
    connect(ui->removeBuddyButton, SIGNAL(clicked()), this, SLOT(removeBuddypressed()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(closeApplication()));
    connect(ui->buddyList, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(buddyPressed(QModelIndex)));
    connect(ui->actionAbout_Qt, SIGNAL(triggered()), this, SLOT(aboutQTPressed()));
    connect(ui->actionAbout_SLM, SIGNAL(triggered()), this, SLOT(aboutSLMPressed()));
    connect(ui->actionEncryption_Key, SIGNAL(triggered()), this, SLOT(encryptionKeyPressed()));

    //Tray Icon
    this->createActions();
    this->createTrayIcon();

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    connect(this, SIGNAL(signalPlaceToTray()),this, SLOT(slotPlaceToTray()),Qt::QueuedConnection);
    trayIcon->setIcon(QIcon(":/icons/SLM_Logo"));

    trayIcon->show();

}

void slm_machine::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::WindowStateChange)
     {
         if (isMinimized())
         {
             emit signalPlaceToTray();
             event->ignore();
             return;
         }
     }
    QMainWindow::changeEvent(event);
}

void slm_machine::addBuddyPressed()
{
    addBuddyScreenDialog = new QDialog();
    ui_addBuddyScreen = new Ui::addBuddyScreen();
    ui_addBuddyScreen->setupUi(addBuddyScreenDialog);

    connect(ui_addBuddyScreen->L_addBuddyButton, SIGNAL(clicked()), this, SLOT(L_addBuddyButtonPressed()));
    connect(ui_addBuddyScreen->L_cancelAddBuddyButton, SIGNAL(clicked()), this, SLOT(L_cancelAddBuddyButtonPressed()));

    addBuddyScreenDialog->show();
}

void slm_machine::slotPlaceToTray()
{
     this->hide();
}
void slm_machine::L_addBuddyButtonPressed()
{

    if(!ui_addBuddyScreen->L_buddyAliasLine->text().isEmpty() && !ui_addBuddyScreen->L_buddyIPAddressLine->text().isEmpty())
    {
        if(!(this->IPAddressValidator(ui_addBuddyScreen->L_buddyIPAddressLine->text())))
        {
            QMessageBox::warning(this,QString("Wrong IP Address!"),QString("IP Address is not Valid!"));
        }
        else
        {
            buddies->AliasBuddyList.append(ui_addBuddyScreen->L_buddyAliasLine->text());
            buddyModel->setStringList(buddies->AliasBuddyList);
            ui->buddyList->setModel(buddyModel);

            buddies->IPBuddyList.append(ui_addBuddyScreen->L_buddyIPAddressLine->text());

            qDebug() << buddies->IPBuddyList;
            qDebug() << buddies->AliasBuddyList;

            addBuddyScreenDialog->close();
        }
    }
    else
    {
        QMessageBox::warning(this,QString("Empty Field!"),QString("Please Fill the Form completely!"));
    }
}

void slm_machine::L_cancelAddBuddyButtonPressed()
{
    addBuddyScreenDialog->close();
}

void slm_machine::removeBuddypressed()
{
    int a = ui->buddyList->currentIndex().row();

    buddies->AliasBuddyList.removeAt(a);
    buddies->IPBuddyList.removeAt(a);

    buddyModel->setStringList(buddies->AliasBuddyList);
    ui->buddyList->setModel(buddyModel);
}

void slm_machine::messageHandler(QByteArray incomingMessage, QHostAddress peerAddress)
{
    QString incoming(incomingMessage);
    QString correspondingAlias;
    if(buddies->IPBuddyList.contains(peerAddress.toString(), Qt::CaseInsensitive))
    {
        correspondingAlias = buddies->AliasBuddyList[buddies->IPBuddyList.indexOf(peerAddress.toString(),0)];
        this->clientCreation(buddies->IPBuddyList.indexOf(peerAddress.toString(),0));
        clientList[(activeClientAliasList.indexOf(buddies->AliasBuddyList[buddies->IPBuddyList.indexOf(peerAddress.toString(),0)]))]->readMessagefromBuddy(incoming,peerAddress);
    }
    else
    {
        QMessageBox::warning(this,QString("UnKnown Buddy"),QString("An unknown Buddy sent a message from IP address " + peerAddress.toString()));
    }
}

void slm_machine::closeApplication()
{
    // Store the Latest Contact List
    buddies->storeBuddies();
    QApplication::quit();
}

void slm_machine::buddyPressed(QModelIndex buddy)
{
    this->clientCreation(buddy.row());
}

void slm_machine::clearClientFromActiveList(QString clientName)
{
    clientList.removeAt(activeClientAliasList.indexOf(clientName,0));
    activeClientAliasList.removeAt(activeClientAliasList.indexOf(clientName,0));
}

void slm_machine::clientCreation(int buddyIndex)
{
    if(!activeClientAliasList.contains(buddies->AliasBuddyList[buddyIndex],Qt::CaseInsensitive))
    {
        newClient = new slm_client();
        newClient->setEncryptionKey(buddies->getKey());
        clientList << newClient;
        clientList.last()->show();
        clientList.last()->setGuiKey(1); // set the gui key to one to indicate it is opened
        clientList.last()->initiateClient(buddies->AliasBuddyList[buddyIndex], buddies->IPBuddyList[buddyIndex]);
        connect(clientList.last(), SIGNAL(destroyClient(QString)), this, SLOT(clearClientFromActiveList(QString)));
        activeClientAliasList.append(clientList.last()->slmclientName);
    }
    else
    {
        qDebug() << activeClientAliasList.indexOf(buddies->AliasBuddyList[buddyIndex],0);
        clientList[(activeClientAliasList.indexOf(buddies->AliasBuddyList[buddyIndex],0))]->setWindowState(clientList[(activeClientAliasList.indexOf(buddies->AliasBuddyList[buddyIndex],0))]->windowState() & ~Qt::WindowMinimized | Qt::WindowActive);
        clientList[(activeClientAliasList.indexOf(buddies->AliasBuddyList[buddyIndex],0))]->activateWindow();
    }
}
// TODO
// Write more intelligent IP validating Code using RegExp!!
bool slm_machine::IPAddressValidator(QString IPtobeValidated)
{
    QStringList ipBlocks = IPtobeValidated.split(".");
    int a=0;
    int loop_variable = 0;
    bool return_value = 1;

    if(!(IPtobeValidated.compare("0.0.0.0")) ||
       !(IPtobeValidated.compare("255.255.255.255")))
    {
        return_value = 0;
    }

    if(ipBlocks.size() == 4 && return_value != 0 )
    {
        for(loop_variable=0;loop_variable<4;loop_variable++)
        {
            a = ipBlocks.at(loop_variable).toInt();

            if(loop_variable == 0 && a == 0)
            {
                return_value = 0;
                break;
            }

            if(a > 255 || a < 0)
            {
                return_value = 0;
                break;
            }
        }
    }
    else
    {
        return_value = 0;
    }
    return return_value;
}

void slm_machine::encryptionKeyPressed()
{
    encryptionKeyWindow = new QDialog();
    ui_encryption = new Ui::encryptionKeyDialog();
    ui_encryption->setupUi(encryptionKeyWindow);
    encryptionKeyWindow->setWindowTitle("Enter Encryption Key");

    connect(ui_encryption->encryptionKeyButtons, SIGNAL(accepted()),this, SLOT(setEncryptionKey()));
    connect(ui_encryption->encryptionKeyButtons, SIGNAL(rejected()), this, SLOT(cancelEncryptionKey()));

    ui_encryption->encryptionKeyLine->setText(buddies->getKey());

    encryptionKeyWindow->show();
}

void slm_machine::setEncryptionKey()
{
    if(ui_encryption->encryptionKeyLine->text().isEmpty())
    {
        QMessageBox::warning(this,QString("Empty Encryption Field!"),QString("Encryption Key Field cannot be empty!"));
    }
    else
    {
        buddies->setKey(ui_encryption->encryptionKeyLine->text());
    }
}

void slm_machine::cancelEncryptionKey()
{
    encryptionKeyWindow->close();
}

void slm_machine::aboutQTPressed()
{
    QMessageBox::aboutQt(this, QString(":: SMG LAN Messenger ::"));
}

void slm_machine::aboutSLMPressed()
{
    QString AboutSLM = "SMG LAN MESSENGER\n\nSLM stands for SMG LAN Messenger developed for hobby purposes only.\n\nThis program is free software; you can redistribute it and-or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.\n\nThis program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.\n\nDevelopers\nAhmet KURUKOSE (ahmetkurukose@yahoo.com)\nFatih AKSEL\n\nConsultants\nUmut DENIZ\nCengiz YILMAZ";
    QMessageBox::about(this, QString(":: SMG LAN Messenger ::"), AboutSLM);
}

void slm_machine::closeEvent(QCloseEvent *closeEvent)
{
    closeEvent->type(); //dummy line for preventing compiler warnings
    this->closeApplication();
}

void slm_machine::createActions()
{
    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void slm_machine::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}

void slm_machine::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
        case QSystemTrayIcon::DoubleClick:
                                            showNormal();
                                            this->activateWindow();
                                            break;
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::MiddleClick:
        default:
         break;
     }
}

slm_machine::~slm_machine()
{
    delete ui;
}
