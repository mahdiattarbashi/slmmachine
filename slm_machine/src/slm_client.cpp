#include "slm_client.h"
#include "slm_Globals.h"

using namespace SLM_Global::UserInterface;

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
    connect(m_ui->saveConversationButton,SIGNAL(clicked()),this,SLOT(saveConversation()));
    connect(m_ui->encSendFileButton,SIGNAL(clicked()),this,SLOT(sendEncFileToBuddy()));
    m_ui->slm_client_outgoingTextArea->setFocus();
    encOrNot = 0;
    isCleared = 0;
}
void slm_client::saveConversation()
{
    QFile conservation;
    QString fileName = QFileDialog::getSaveFileName(this);

    if (fileName == "")
        return;

    conservation.setFileName(fileName);

    if (!conservation.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,tr("SLM"),tr("File cannot be saved!"));
        return;
    }

    QTextStream out(&conservation);
    out << m_ui->slm_clientIncomingTextArea->toPlainText();

    conservation.close();
    QMessageBox::information(this,tr("SLM"),tr("Conversation Saved!"));
}
void slm_client::initiateClient(QString clientName, QString clientIPAddress)
{
    m_slmclientName = clientName;
    m_isLastMessageSendByMe = false;
    isFirstMessage = 1;
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
    isCleared = 1;
}
    //Socket Connection Error Slot
void slm_client::displayError(QAbstractSocket::SocketError socketError)
 {
    int answer;
     switch (socketError)
     {
         case QAbstractSocket::RemoteHostClosedError:
                QMessageBox::warning(this,tr("SLM"),tr("Client closed the application"));
                answer = QMessageBox::question(this, "SLM Save Conversation",
                                     tr("Do you want to save the conversation?"),
                                     QMessageBox::Yes|QMessageBox::Default,
                                     QMessageBox::No|QMessageBox::Escape);
                if(answer & QMessageBox::Yes)
                {
                    this->saveConversation();
                }
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
    if(m_ui->slm_client_outgoingTextArea->text() != "")
    {
        QDateTime currentTime;
        QString shownMessage;

        outGoingTextString = m_ui->slm_client_outgoingTextArea->text();

        qDebug() << "Unencrypted Text :: " << outGoingTextString;
        if(!m_isLastMessageSendByMe)
        {
             shownMessage += "(" + currentTime.currentDateTime().toString(DATE_FORMAT) + ") " + MY_NAME + ":";
             echo(HEADER,shownMessage);
        }

        echo(MESSAGE,outGoingTextString);

        m_isLastMessageSendByMe = true;

        outGoingTextString = encryptionObject.dencrypt(outGoingTextString, this->EncryptionKey);

        qDebug() << "Ecrypted Text" << "::" << outGoingTextString;

        outGoingTextArray = outGoingTextString.toUtf8();
        outgoingSocket->write(outGoingTextArray);

        //clear the text field after writing the text
        m_ui->slm_client_outgoingTextArea->clear();
    }
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
        isFirstMessage = 1;
    }
    else
    {
        this->activateWindow();// if it is already opened, activate it before writing the message
    }

    //show the message to the by formatting
    if(m_isLastMessageSendByMe || (isFirstMessage == 1) || (isCleared == 1))
    {
         shownMessage += "(" + currentTime.currentDateTime().toString(DATE_FORMAT) + ") " + m_slmclientName + ":";
         echo(HEADER,shownMessage);
         isFirstMessage = 0;
         isCleared = 0;
    }
    echo(MESSAGE,incomingMessage);

    m_isLastMessageSendByMe = false;
}

void slm_client::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->setGuiKey(0); // set the gui key to zero to indicate it is closed
    outgoingSocket->disconnectFromHost();
    emit destroyClient(m_slmclientName);
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

void slm_client::sendEncFileToBuddy()
{
    this->encOrNot = 1;
    sendFileToBuddy();
}
void slm_client::sendFileToBuddy()
{
    filepathString = "";
    filepathString = QFileDialog::getOpenFileName(this, "Choose a file");
    if(filepathString != "")
    {
        if(this->encOrNot == 1)
        {
            //Encrypt the file first
            encryptedFileName = filepathString + ".enc";

            crypto = new fileCrypter();

            crypto->InputFile = filepathString;
            crypto->OutputFile = encryptedFileName;
            crypto->key = 1;

            connect(crypto,SIGNAL(destroyed()),this,SLOT(transfer()));

            emit encryptingStarted();
            QThreadPool::globalInstance()->start(crypto);
        }
        else
        {
            transfer();
        }
    }
    else
    {
        QMessageBox::warning(this,QString("SLM File Transfer"),QString("Please Choose a File!"));
    }
}
void slm_client::transfer()
{
    if(encOrNot == 1)
    {
        emit encryptingFinished();
    }
    fileSenderThread =new fileSender();
    connect(fileSenderThread,SIGNAL(transferFinished()),this,SLOT(fileSentCompleted()),Qt::QueuedConnection);
    connect(fileSenderThread,SIGNAL(unknownMessageReceived()),this,SLOT(unknownMessage()),Qt::QueuedConnection);
    connect(fileSenderThread,SIGNAL(peerConnectionClosed()),this,SLOT(connectionBroken()),Qt::QueuedConnection);
    connect(fileSenderThread,SIGNAL(sendingStarted(quint32)),this,SLOT(createFileProgress(quint32)),Qt::BlockingQueuedConnection);
    connect(fileSenderThread,SIGNAL(sendingCondition(quint32)),this,SLOT(updateFileProgress(quint32)),Qt::BlockingQueuedConnection);

    if(encOrNot == 1)
    {
        fileSenderThread->filePathOfOutgoingFile = encryptedFileName;
        fileSenderThread->encOrNot = 1;
    }
    else
    {
        fileSenderThread->filePathOfOutgoingFile = filepathString;
        fileSenderThread->encOrNot = 0;
    }
    fileSenderThread->peerIP = this->slmclientIPAddress;
    fileSenderThread->start();
}
void slm_client::createFileProgress(quint32 fileSize)
{
    qDebug() << "File Size: " <<fileSize;
    file_size_ = fileSize;
    progress = new QProgressDialog("Sending File...", "Abort Copy", 0, (int)fileSize, this);
    progress->setValue(0);
}
void slm_client::updateFileProgress(quint32 writtenBytes)
{
    progress->setValue(((int)writtenBytes * 2));
}
void slm_client::connectionBroken()
{
   //TODO
   //Handle this situation (connection Broken in the middle)
   // QMessageBox::warning(this,QString("SLM File Transfer"),QString("Connection is closed, Transfer is canceled!"));
}
void slm_client::fileSentCompleted()
{
    progress->setValue(file_size_);
    if(encOrNot == 1)
    {
        QFile::remove(encryptedFileName);
    }
    emit showTrayMessageTransferCompleted();
    encOrNot = 0;
}
void slm_client::unknownMessage()
{
    QMessageBox::warning(this,QString("SLM File Transfer"),QString("An unknown message is received from the Buddy, Transfer is canceled!"));
}
slm_client::~slm_client()
{
    delete m_ui;
    outgoingSocket->disconnectFromHost();
    outgoingSocket->close();
    delete outgoingSocket;
}
//Getters & Setters
void slm_client::setClientName(QString clientName)
{
    m_slmclientName = clientName;
}
QString slm_client::getClientName() const
{
    return m_slmclientName;
}
//generic method for writing to QTextEdit area
void slm_client::echo(EchoType type, QString message)
{
    QString messagePrefix;
    switch(type)
    {
        case ERROR:
            m_ui->slm_clientIncomingTextArea->setTextBackgroundColor(QColor(Qt::darkRed));
            m_ui->slm_clientIncomingTextArea->setTextColor(QColor(Qt::white));
            messagePrefix.append(tr("ERROR : "));
        case WARNING:
            m_ui->slm_clientIncomingTextArea->setTextBackgroundColor(QColor(Qt::yellow));
            m_ui->slm_clientIncomingTextArea->setTextColor(QColor(Qt::black));
            messagePrefix.append(tr("WARNING : "));
        case INFO:
            m_ui->slm_clientIncomingTextArea->setTextBackgroundColor(QColor(Qt::green));
            m_ui->slm_clientIncomingTextArea->setTextColor(QColor(Qt::black));
            messagePrefix.append(tr("INFO : "));
        case HEADER:
            m_ui->slm_clientIncomingTextArea->setTextBackgroundColor(QColor(Qt::white));
            m_ui->slm_clientIncomingTextArea->setTextColor(QColor(Qt::blue));
            m_ui->slm_clientIncomingTextArea->setFontItalic(1);
            m_ui->slm_clientIncomingTextArea->setFontWeight(QFont::Bold);
            break;
        case MESSAGE:
            m_ui->slm_clientIncomingTextArea->setTextBackgroundColor(QColor(Qt::white));
            m_ui->slm_clientIncomingTextArea->setTextColor(QColor(Qt::black));
            m_ui->slm_clientIncomingTextArea->setFontItalic(0);
            m_ui->slm_clientIncomingTextArea->setFontWeight(QFont::Bold);
            break;
        default:
            break;
    }

    messagePrefix.append(message);

    m_ui->slm_clientIncomingTextArea->append(messagePrefix);

    //make the ui more responsive by processing pending events
    QCoreApplication::processEvents(QEventLoop::AllEvents);
}
