#include "fileserver.h"

static quint32 const PAYLOADSIZE = 65536;

fileServer::fileServer(QObject *parent):QThread(parent)
{

}
void fileServer::initializeVariables()
{
    answerSemaphore = new QSemaphore(1);
    block_size = 0;
    IncomingFileSize = 0;
    serverState = 0;
    userAnswer = 0;
    userAnswered = 0;
    bytesWritten = 0;
    fileContents.clear();
}
void fileServer::run()
{
    server = new QTcpServer();

    // start listen for incoming connections
    if(!server->listen(QHostAddress::Any, 3333))
    {
        qDebug()<<"Error: File Server cannot be Initialized";
    }
    else
    {
        qDebug()<<"File Server Initialized: Listening on port 3333";
        QObject::connect(server,SIGNAL(newConnection()),this,SLOT(peerConnection()),Qt::DirectConnection);
    }

    //Initialize Variables
    initializeVariables();

    QThread::exec();
}
void fileServer::peerConnection()
{
    if(serverState == 0)
    {
        serverState = 1;
        socket = new QTcpSocket();
        socket = server->nextPendingConnection();
        QObject::connect(socket,SIGNAL(readyRead()),this,SLOT(readMessage()),Qt::DirectConnection );
        QObject::connect(socket,SIGNAL(disconnected()),this,SLOT(destroySocket()),Qt::DirectConnection );
    }
    else
    {
        emit ongoingTransfer();
    }
}
void fileServer::readMessage()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_0);

    if(block_size == 0)
    {
        in >> block_size;
    }

    quint8 messageType;
    QString incomingFileName;
    QString fileDescriptorString;

    in >> messageType;

    if(messageType == 'I')
    {
        in >> incomingFileName >> IncomingFileSize;

        if(IncomingFileSize < 1024)
        {
            fileDescriptorString = tr("%1 Byte").arg(IncomingFileSize);
        }
        else if(IncomingFileSize < 1048576)
        {
            fileDescriptorString = tr("%1 KB").arg(static_cast<double>(IncomingFileSize) / 1024, 0, 'f', 2);
        }
        else if(IncomingFileSize < 1073741824)
        {
           fileDescriptorString = tr("%1 MB").arg(static_cast<double>(IncomingFileSize) / 1048576, 0, 'f', 2);
        }
        else
        {
            fileDescriptorString = tr("%1 GB").arg(static_cast<double>(IncomingFileSize) / 1073741824, 0, 'f', 2);
        }

        //Inform GUI Thread about incoming file
        emit newDocumentArrived(incomingFileName, fileDescriptorString, (static_cast<double>(IncomingFileSize)));


        //TODO
        //Add Timeout condition

        //Construct the necessary directory
        QDir defaultSaveDirectoryObject;

#ifdef Q_WS_WIN32
        defaultSaveDirectoryObject.mkpath("C:/SLM_Downloads");
        defaultSaveDirectory = "C:/SLM_Downloads/";
#endif
#ifdef Q_WS_X11
        defaultSaveDirectoryObject.mkpath("/tmp/SLM_Downloads");
        defaultSaveDirectory = "/tmp/SLM_Downloads/";
#endif
#ifdef Q_WS_MAC
		defaultSaveDirectoryObject.mkpath("/tmp/SLM_Downloads");
        defaultSaveDirectory = "/tmp/SLM_Downloads/";
#endif
        //Wait For user input whether accepted or rejected!
        while(1)
        {
            answerSemaphore->acquire();
            if(userAnswer == 1 && userAnswered==1)
            {
                getUserAnswer(1,(defaultSaveDirectory + incomingFileName));
                break;
            }
            else if(userAnswer == 0 && userAnswered == 1)
            {
                QObject::disconnect(socket, SIGNAL(readyRead()), 0, 0);
                QObject::connect(socket,SIGNAL(readyRead()),this, SLOT(readMessage()),Qt::DirectConnection );
                initializeVariables();
                emit transferCanceled();
                break;
            }
            answerSemaphore->release();
        }

    }
    else
    {
        emit unknownMessageArrived();
    }

}
void fileServer::getUserAnswer(bool cevap, QString DosyaYeri)
{
    if(cevap == 1 && DosyaYeri != "")
    {
        newDocument = new QFile(DosyaYeri);

        if(!newDocument->open(QIODevice::WriteOnly))
        {
            //TODO
            //Inform GUI Thread that file cannot be written and quit transfer
            initializeVariables();
        }

        sendAcceptMessage();

        fileContents.resize(PAYLOADSIZE);
        QObject::disconnect(socket, SIGNAL(readyRead()), 0, 0);
        QObject::connect(socket,SIGNAL(readyRead()),this, SLOT(finishDocument()),Qt::DirectConnection );
    }
    else
    {
        QObject::disconnect(socket, SIGNAL(readyRead()), 0, 0);
        QObject::connect(socket,SIGNAL(readyRead()),this, SLOT(readMessage()),Qt::DirectConnection );
        initializeVariables();
        emit transferCanceled();
    }
}
void fileServer::sendAcceptMessage()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16)0;
    out << (quint8)'A';
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    socket->write(block);
}
void fileServer::finishDocument()
{
      bytesWritten += (int)socket->bytesAvailable();
      fileContents.clear();
      fileContents.resize(PAYLOADSIZE);
      fileContents = socket->readAll();

      newDocument->write(fileContents);
      emit receivingProgress(bytesWritten);

      if(bytesWritten == IncomingFileSize)
      {

        QObject::disconnect(socket, SIGNAL(readyRead()), 0, 0);
        QObject::connect(socket,SIGNAL(readyRead()),this, SLOT(readMessage()),Qt::DirectConnection );
        emit transferCompleted(newDocument->fileName());
        newDocument->close();
        newDocument->flush();
        socket->close();
        delete socket;
        delete answerSemaphore;
        initializeVariables();
      }
}
void fileServer::destroySocket()
{
    //delete socket;
}
