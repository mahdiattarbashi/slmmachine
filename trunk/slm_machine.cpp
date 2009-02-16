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


void slm_machine::aboutQTPressed()
{
    aboutQt = new QDialog();
    ui_aboutQT = new Ui::aboutQTDialog();
    ui_aboutQT->setupUi(aboutQt);
    aboutQt->setWindowTitle(":: About QT ::");
    aboutQt->setFixedSize(350,350);

    connect(ui_aboutQT->aboutQT_OKButton, SIGNAL(clicked()), this, SLOT(closeAboutQtDialog()));

    aboutQt->show();
}

void slm_machine::aboutSLMPressed()
{
    aboutSLM = new QDialog();
    ui_aboutSLM = new Ui::aboutSLMDialog();
    ui_aboutSLM->setupUi(aboutSLM);
    aboutSLM->setWindowTitle(":: About SLM ::");
    aboutSLM->setFixedSize(400,380);

    connect(ui_aboutSLM->aboutSLM_OKButton, SIGNAL(clicked()), this, SLOT(closeAboutSLMDialog()));

    aboutSLM->show();
}


void slm_machine::closeAboutQtDialog()
{
    aboutQt->close();
}

void slm_machine::closeAboutSLMDialog()
{
    aboutSLM->close();
}
void slm_machine::closeEvent(QCloseEvent *closeEvent)
{
    closeEvent->type(); //dummy line for preventing compiler warnings
    this->closeApplication();
}

slm_machine::~slm_machine()
{
    delete ui;
}
