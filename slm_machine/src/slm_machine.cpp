#include "slm_machine.h"

slm_machine::slm_machine(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::slm_machineClass)
{
/************************** UI and Buddy Management *******************************/
    ui->setupUi(this);

    //Buddy Management
    buddies = new buddyManager();
    buddies->loadBuddiesAndIPs();
    buddyModel = new QStringListModel();
    buddyModel->setStringList(buddies->AliasBuddyList);

    ui->buddyList->setModel(buddyModel);
    ui->buddyList->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->setWindowTitle("SLM");

    //UI connections
    connect(ui->addBuddyButton, SIGNAL(clicked()),this, SLOT(addBuddyPressed()));
    connect(ui->removeBuddyButton, SIGNAL(clicked()), this, SLOT(removeBuddypressed()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(closeApplication()));
    connect(ui->buddyList, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(buddyPressed(QModelIndex)));
    connect(ui->actionAbout_Qt, SIGNAL(triggered()), this, SLOT(aboutQTPressed()));
    connect(ui->actionAbout_SLM, SIGNAL(triggered()), this, SLOT(aboutSLMPressed()));
    connect(ui->actionEncryption_Key, SIGNAL(triggered()), this, SLOT(encryptionKeyPressed()));

/************************************************************************************/

/************************** Message Server Management *******************************/
    messageServer = slm_server::getInstance();
    connect(messageServer, SIGNAL(sendtoUI(QByteArray,QHostAddress)),this,SLOT(messageHandler(QByteArray,QHostAddress)));
/************************************************************************************/

/***************************** File Server Management *******************************/
    FServer = new fileServer();

    //File Server Connections
    connect(FServer,SIGNAL(newDocumentArrived(QString,QString,quint32,quint8)),this,SLOT(incomingFileSlot(QString,QString,quint32,quint8)),Qt::QueuedConnection);
    connect(FServer,SIGNAL(transferCompleted(QString)),this,SLOT(incomingFileTransferCompleted(QString)),Qt::QueuedConnection);
    connect(FServer,SIGNAL(transferCanceled()),this,SLOT(transferIsCancelled()),Qt::QueuedConnection);
    connect(FServer,SIGNAL(ongoingTransfer()),this,SLOT(ongoingTransferExists()),Qt::QueuedConnection);
    connect(FServer,SIGNAL(receivingProgress(quint32)),this,SLOT(updateReceivingProgress(quint32)),Qt::QueuedConnection);

    //Start the File Server Thread
    FServer->start();
/***********************************************************************************/

/***************************** Buddy List Right Click *******************************/
    checkOnline = new QAction(tr("&Check Online"), this);
    checkOnline->setIcon(QIcon(":/icons/CheckOnline"));
    rightClickUserMenu = new QMenu();
    rightClickUserMenu->addAction(checkOnline);
    connect(checkOnline,SIGNAL(triggered()),this,SLOT(checkUserOnline()));
    ui->buddyList->installEventFilter(this);
/***********************************************************************************/

/***************************** Tray Icon Management ********************************/
    //Create tray icon and contex menu actions
    this->createActions();
    this->createTrayIcon();

    //Tray Icon Connections
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    connect(this, SIGNAL(signalPlaceToTray()),this, SLOT(slotPlaceToTray()),Qt::QueuedConnection);

    //Show application icon in the tray
    trayIcon->setIcon(QIcon(":/icons/SLM_Logo"));
    trayIcon->setToolTip("SLM (SMG Lan Messenger)");
    trayIcon->show();
/**********************************************************************************/
}
void slm_machine::checkUserOnline()
{
    QTcpSocket *checkUser = new QTcpSocket();
    checkUser->connectToHost(buddies->IPBuddyList[ui->buddyList->currentIndex().row()], 3333,QIODevice::ReadOnly);
    if(checkUser->waitForConnected(500))
    {
        QMessageBox::information(this,"SLM User Check","User is Online");
    }
    else
    {
        QMessageBox::warning(this,"SLM User Check", "User is offline");
    }
    checkUser->disconnectFromHost();
    checkUser->close();
    delete checkUser;
}
bool slm_machine::checkBuddyOnline(QString Buddy)
{
    QTcpSocket *checkUser = new QTcpSocket();
    checkUser->connectToHost(buddies->IPBuddyList[buddies->AliasBuddyList.indexOf(Buddy,0)], 3333,QIODevice::ReadOnly);
    if(checkUser->waitForConnected(500))
    {
        checkUser->disconnectFromHost();
        checkUser->close();
        delete checkUser;
        return 1;
    }
    else
    {
        checkUser->disconnectFromHost();
        checkUser->close();
        delete checkUser;
        return 0;
    }
}
bool slm_machine::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::ContextMenu)
    {
        rightClickUserMenu->exec(QCursor::pos());
        return true;
    }
    else
    {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}
/********************************************************************************************/
/*
* File Server Slots:
* ------------------
* 1- void incomingFileSlot(QString, QString, quint32);
* 2- void updateReceivingProgress(quint32);
* 3- void ongoingTransferExists();
* 4- void transferIsCancelled();
* 5- void incomingFileTransferCompleted();
* 6- void showTrayMessageFileSentCompleted();
*/
void slm_machine::incomingFileSlot(QString fileName, QString infoString, quint32 fileSize, quint8 isEnc)
{
    int gui_return_answer;
    
    switch(isEnc)
    {
        case 'E':
        encOrNot = 1;
        gui_return_answer = QMessageBox::question(this, "SLM File Transfer",
                                     tr("Incoming file with Encryption: %1 (%2). Do you want to save it?")
                                     .arg(fileName).arg(infoString),
                                     QMessageBox::Yes|QMessageBox::Default,
                                     QMessageBox::No|QMessageBox::Escape);
        break;
        
        
        case 'P':
        encOrNot = 0;
        gui_return_answer = QMessageBox::question(this, "SLM File Transfer",
                                     tr("Incoming file without Encryption: %1 (%2). Do you want to save it?")
                                     .arg(fileName).arg(infoString),
                                     QMessageBox::Yes|QMessageBox::Default,
                                     QMessageBox::No|QMessageBox::Escape);
        break;
        
               
        default:
        qDebug() << "Unknown Message";
        return;
    }

    FServer->answerSemaphore->acquire();

    FServer->userAnswered = 1;
    FServer->userAnswer = (gui_return_answer & QMessageBox::Yes);

    FServer->answerSemaphore->release();
    if((gui_return_answer & QMessageBox::Yes))
    {
        receivingFileSize = fileSize;
        progress = new QProgressDialog("Receiving File...", "Abort Copy", 0, fileSize, this);
        progress->setValue(0);
    }
}
void slm_machine::updateReceivingProgress(quint32 size)
{
    progress->setValue(size*2);
}
void slm_machine::ongoingTransferExists()
{
    QMessageBox::warning(this,QString("SLM File Transfer"),QString("There is an on-going Transfer!"));
}
void slm_machine::transferIsCancelled()
{
    QMessageBox::warning(this,QString("SLM File Transfer"),QString("File Transfer Cancelled"));
}
void slm_machine::incomingFileTransferCompleted(QString name)
{
    QString DownloadFolder;
    progress->setValue(receivingFileSize);
    if(encOrNot == 1)
    {
        trayIcon->showMessage("SLM File Transfer(Receiving)", "File Transfer Completed\nFile Decryption is started\nPlease wait until it finishes...",QSystemTrayIcon::Information,10000);

        //Start decryption of incoming file

        //give required information to the decryption object
        incomingFileName = name;

        decrypto = new fileCrypter();
        decrypto->key = 2;

        //Encrypted file name (file that will be decrypted)
        decrypto->InputFile = name;

        //real file name (Remove ".enc" from the end of the file name)
        name.chop(4);
        decrypto->OutputFile = name;

        connect(decrypto,SIGNAL(destroyed()),this,SLOT(decryptionFinished()));

        //Start decryption
        QThreadPool::globalInstance()->start(decrypto);
    }
    else
    {
#ifdef Q_WS_WIN32
        DownloadFolder = "C:/SLM_Downloads/";
#endif
#ifdef Q_WS_X11
        DownloadFolder = "/tmp/SLM_Downloads/";
#endif
#ifdef Q_WS_MAC
        DownloadFolder = "/tmp/SLM_Downloads/";
#endif
        trayIcon->showMessage("SLM File Transfer(Receiving)", tr("File Transfer Finished\nYou can access your file from the %1 folder").arg(DownloadFolder),QSystemTrayIcon::Information,10000);
    }
}
void slm_machine::decryptionFinished()
{
    //remove the encrypted file (temp)
    QFile::remove(incomingFileName);
    QString DownloadFolder;
#ifdef Q_WS_WIN32
    DownloadFolder = "C:/SLM_Downloads/";
#endif
#ifdef Q_WS_X11
    DownloadFolder = "/tmp/SLM_Downloads/";
#endif
#ifdef Q_WS_MAC
    DownloadFolder = "/tmp/SLM_Downloads/";
#endif
    //Inform User about process
    trayIcon->showMessage(tr("SLM File Decryption"), tr("File Decryption Finished\nYou can access your file from the %1 folder").arg(DownloadFolder),QSystemTrayIcon::Information,20000);
}
void slm_machine::showTrayMessageFileSentCompleted()
{
    trayIcon->showMessage("SLM File Transfer (Sending)", "File Transfer Completed",QSystemTrayIcon::Information,10000);
}
void slm_machine::showTrayMessageEncryptionStarted()
{
    trayIcon->showMessage("SLM File Encrytion", "File Encryption Started\nFile Transfer will start automatically after encryption process\nPlease Wait...",QSystemTrayIcon::Information,20000);
}
void slm_machine::showTrayMessageEncryptionFinished()
{
    trayIcon->showMessage("SLM File Encrytion", "File Encryption Finished\nFile Transfer is starting...\nWaiting for peer to accept file transfer",QSystemTrayIcon::Information,10000);
}
/********************************************************************************************/



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
	//check if the alias and hostname or ip address is entered
	if(ui_addBuddyScreen->L_buddyAliasLine->text().isEmpty())
	{
		QMessageBox::warning(this,QString("No Alias!"),QString("Please Enter an Alias For The Buddy!"));

	}
	else if(ui_addBuddyScreen->L_buddyIPAddressLine->text().isEmpty() && ui_addBuddyScreen->L_buddyHostNameLine->text().isEmpty())
	{
		QMessageBox::warning(this,QString("No Host Name or IP Address!"),QString("Please Enter a Host Name or IP Address For The Buddy!"));
	}
	else if(!ui_addBuddyScreen->L_buddyIPAddressLine->text().isEmpty())
	{
		//validate the IP address
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
	else if(ui_addBuddyScreen->L_buddyIPAddressLine->text().isEmpty() && !ui_addBuddyScreen->L_buddyHostNameLine->text().isEmpty())
	{
		QHostInfo info = QHostInfo::fromName(ui_addBuddyScreen->L_buddyHostNameLine->text());
                qDebug()<<info.addresses();

                //check if a valid host name is found
                if(info.addresses().isEmpty())
                {
                    QMessageBox::warning(this,QString("Host Error!"),QString("Host name cannot be found, you may try to enter buddy IP instead!"));
                }
                else
                {
                    buddies->AliasBuddyList.append(ui_addBuddyScreen->L_buddyAliasLine->text());
                    buddyModel->setStringList(buddies->AliasBuddyList);
                    ui->buddyList->setModel(buddyModel);

                    buddies->IPBuddyList.append(info.addresses().first().toString());

                    qDebug() << buddies->IPBuddyList;
                    qDebug() << buddies->AliasBuddyList;

                    addBuddyScreenDialog->close();
                }
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
    delete clientList.at(activeClientAliasList.indexOf(clientName,0));
    clientList.removeAt(activeClientAliasList.indexOf(clientName,0));
    activeClientAliasList.removeAt(activeClientAliasList.indexOf(clientName,0));
}

void slm_machine::clientCreation(int buddyIndex)
{
    if(!activeClientAliasList.contains(buddies->AliasBuddyList[buddyIndex],Qt::CaseInsensitive))
    {
        if(checkBuddyOnline(buddies->AliasBuddyList[buddyIndex]))
        {
            clientList.append(new slm_client());
            clientList.last()->setEncryptionKey(buddies->getKey());
            clientList.last()->show();
            clientList.last()->setGuiKey(1); // set the gui key to one to indicate it is opened
            clientList.last()->initiateClient(buddies->AliasBuddyList[buddyIndex], buddies->IPBuddyList[buddyIndex]);
            connect(clientList.last(), SIGNAL(destroyClient(QString)), this, SLOT(clearClientFromActiveList(QString)));
            connect(clientList.last(),SIGNAL(showTrayMessageTransferCompleted()),this,SLOT(showTrayMessageFileSentCompleted()));
            connect(clientList.last(),SIGNAL(encryptingStarted()),this,SLOT(showTrayMessageEncryptionStarted()));
            connect(clientList.last(),SIGNAL(encryptingFinished()),this,SLOT(showTrayMessageEncryptionFinished()));
            connect(clientList.last(),SIGNAL(informUserWaitForPeer()),this,SLOT(showTrayMessageWaitingForUsertoAccept()));
            activeClientAliasList.append(clientList.last()->getClientName());
        }
        else
        {
            QMessageBox::warning(this,QString("User Not Online"),QString(buddies->AliasBuddyList[buddyIndex] + " is not online! You cannot send messages while user is offline"));
        }
    }
    else
    {
        qDebug() << activeClientAliasList.indexOf(buddies->AliasBuddyList[buddyIndex],0);
        clientList[(activeClientAliasList.indexOf(buddies->AliasBuddyList[buddyIndex],0))]->setWindowState(clientList[(activeClientAliasList.indexOf(buddies->AliasBuddyList[buddyIndex],0))]->windowState() & ~Qt::WindowMinimized | Qt::WindowActive);
        clientList[(activeClientAliasList.indexOf(buddies->AliasBuddyList[buddyIndex],0))]->activateWindow();
    }
}
void slm_machine::showTrayMessageWaitingForUsertoAccept()
{
    trayIcon->showMessage("SLM File Transfer", "Waiting For Peer to Accept File Transfer",QSystemTrayIcon::Information,5000);
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
    QString AboutSLM = "SMG LAN MESSENGER\n\nSLM stands for SMG LAN Messenger developed for hobby purposes only.\n\nThis program is free software; you can redistribute it and-or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.\n\nThis program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.\n\nDevelopers\nAhmet KURUKOSE (ahmetkurukose@yahoo.com)\nFatih AKSEL\nBulent Dag\n\nConsultants\nUmut DENIZ\nCengiz YILMAZ";
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
    restoreAction->setIcon(QIcon(":/icons/restore"));
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    quitAction->setIcon(QIcon(":/icons/exit"));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(closeApplication()));
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
