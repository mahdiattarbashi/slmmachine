#include "slm_client.h"
#include <QCloseEvent>
#include <QMessageBox>

slm_client::slm_client(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::slm_clientWindow)
{
    m_ui->setupUi(this);
    connect(m_ui->slm_client_outgoingTextArea, SIGNAL(returnPressed()), this, SLOT(sendMessagetoBuddy()));
    this->setGuiKey(0);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);
}

void slm_client::initiateClient(QString clientName, QString clientIPAddress)
{
    slmclientName = clientName;

    slmclientIPAddress = clientIPAddress;
    this->setWindowTitle(clientName+ " @ " + clientIPAddress);

    outgoingSocket = new QTcpSocket();
    outgoingSocket->connectToHost(clientIPAddress, 29999,QIODevice::WriteOnly);

    //Socket Connection Check
    connect(outgoingSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
}

//Socket Connection Error Slot
void slm_client::displayError(QAbstractSocket::SocketError socketError)
 {
     switch (socketError)
     {
         case QAbstractSocket::RemoteHostClosedError:
                break;
         case QAbstractSocket::HostNotFoundError:
                QMessageBox::information(this, tr("SLM"),tr("The host was not found. Please check the host name."));
                break;
         case QAbstractSocket::ConnectionRefusedError:
                QMessageBox::information(this, tr("SLM"), tr("The connection was refused by the peer. Make sure the other client is running, and check that the host name is correct."));
                break;
         default:
                QMessageBox::information(this, tr("SLM"), tr("The following error occurred: %1.").arg(outgoingSocket->errorString()));
     }
 }
void slm_client::sendMessagetoBuddy()
{
    QDateTime currentTime;
    QString shownMessage;

    outGoingTextString = m_ui->slm_client_outgoingTextArea->text();

    qDebug() << "Unencrypted Text :: " << outGoingTextString;

    shownMessage =  currentTime.currentDateTime().toString() + " Outgoing Message:" + "\n" + "\n" + outGoingTextString + "\n";
    m_ui->slm_clientIncomingTextArea->append(shownMessage);

    outGoingTextString = encryptionObject.dencrypt(outGoingTextString, this->EncryptionKey);

    qDebug() << "Ecrypted Text" << "::" << outGoingTextString;

    outGoingTextArray = outGoingTextString.toUtf8();
    outgoingSocket->write(outGoingTextArray);

    //clear the text field after writing the text
    m_ui->slm_client_outgoingTextArea->clear();
}

void slm_client::readMessagefromBuddy(QString incomingMessage, QHostAddress peerAddress)
{
    QDateTime currentTime;
    QString shownMessage;

    //decrypt the message
    incomingMessage = encryptionObject.dencrypt(incomingMessage, this->EncryptionKey);

    qDebug() << "Decrypted Text :: " << incomingMessage;

    // check if the message gui is open or not and open if it is not.
    if(this->getGuiKey() == 0)
    {
        this->show();
        this->setGuiKey(1);// set the gui key to one to indicate it is opened
    }
    else
    {
        this->activateWindow();// if it is already opened, activate it before writing the message
    }
    //show the message to the user by adding current data and time
    shownMessage =  currentTime.currentDateTime().toString() + " Incoming Message From " + peerAddress.toString() + ": " + "\n" + "\n" + incomingMessage + "\n";
    m_ui->slm_clientIncomingTextArea->append(shownMessage);
}

void slm_client::closeEvent(QCloseEvent *event)
{
    event->type();
    this->setGuiKey(0); // set the gui key to zero to indicate it is closed
    outgoingSocket->disconnectFromHost();
    emit destroyClient(slmclientName);
}

void slm_client::setGuiKey(bool key)
{
    guiKey = key;
}

bool slm_client::getGuiKey()
{
    return guiKey;
}

void slm_client::setEncryptionKey(QString Key)
{
    EncryptionKey = Key;
}

slm_client::~slm_client()
{
    delete m_ui;
}
