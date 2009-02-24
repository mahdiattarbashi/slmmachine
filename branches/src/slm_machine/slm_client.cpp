#include "slm_client.h"

slm_client::slm_client(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::slm_clientWindow)
{
    m_ui->setupUi(this);
    connect(m_ui->slm_client_outgoingTextArea, SIGNAL(returnPressed()), this, SLOT(sendMessagetoBuddy()));
    this->setGuiKey(0);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);
    connect(m_ui->clearButton,SIGNAL(clicked()),this,SLOT(clearTextArea()));
    connect(m_ui->sendFileButton,SIGNAL(clicked()),this,SLOT(sendFileToBuddy()));
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
void slm_client::clearTextArea()
{
    m_ui->slm_clientIncomingTextArea->clear();
    m_ui->slm_client_outgoingTextArea->setFocus();
}
    //Socket Connection Error Slot
void slm_client::displayError(QAbstractSocket::SocketError socketError)
 {
     switch (socketError)
     {
         case QAbstractSocket::RemoteHostClosedError:
                QMessageBox::warning(this,tr("SLM"),tr("Client closed the application"));
                this->close();
                break;
         case QAbstractSocket::HostNotFoundError:
                QMessageBox::information(this, tr("SLM"),tr("The host was not found. Please check the host name."));
                this->close();
                break;
         case QAbstractSocket::ConnectionRefusedError:
                QMessageBox::information(this, tr("SLM"), tr("The connection was refused by the peer. Make sure the other client is running, and check that the host name is correct."));
                this->close();
                break;
         default:
                QMessageBox::information(this, tr("SLM"), tr("The following error occurred: %1.").arg(outgoingSocket->errorString()));
                this->close();
                break;
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
    event->ignore();
    this->setGuiKey(0); // set the gui key to zero to indicate it is closed
    outgoingSocket->disconnectFromHost();
    emit destroyClient(slmclientName);
    this->hide();
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

void slm_client::sendFileToBuddy()
{
    //crypto.startEnc("C:/slmLogo.png","C:/denemeEncryted.png");
    //QTimer::singleShot(10000,this,SLOT(startDecoding()));
    QString filepathString;
    filepathString = QFileDialog::getOpenFileName(this, "Choose a file");
    if(filepathString != "")
    {
        fileSenderThread =new fileSender();
        fileSenderThread->filePathOfOutgoingFile = filepathString;
        fileSenderThread->peerIP = this->slmclientIPAddress;
        fileSenderThread->start();
    }
    else
    {
        QMessageBox::warning(this,QString("SLM File Transfer"),QString("Please Choose a File!"));
    }
}

//TODO
//Following Code is only for test purposes and will be discarded after real implementation.
void slm_client::startDecoding()
{
    crypto.startDec("C:/denemeEncryted.png","C:/deneme2.png");
}
//
slm_client::~slm_client()
{
    delete m_ui;
}
