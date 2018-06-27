#include "clientSocket.h"

clientSocket::clientSocket(QObject *parent) : QObject(parent)
{
    client = new QTcpSocket(this);
    my_flag_socket = new bool(false);
    msgSuccess = new bool (false);

    connect(client, SIGNAL(connected()),
            this, SLOT(showConnection()));
    connect(client,SIGNAL(readyRead()),
            this, SLOT(parseMsg()));
}

clientSocket::~clientSocket()
{
    client->close();
}

void clientSocket::parseMsg()
{
    char buffer[1024] = {0};
    client->read(buffer, client->bytesAvailable());
    QString line = buffer;
    QStringList line_split = line.split(",");
    msg = QString("Gaze X:%1,Gaze Y:%2,Gaze Z:%3")
                  .arg(line_split.at(0)).arg(line_split.at(1)).arg(line_split.at(2));

    *msgSuccess = true;
    hash.insert("Gaze X", line_split.at(0).toInt());
    hash.insert("Gaze Y", line_split.at(1).toInt());
    hash.insert("Gaze Z", line_split.at(2).toInt());
//    clientBrowser->append(hash);
}

void clientSocket::connectSocket(QString address, int port)
{
    //connect to server at address and port
    QHostAddress addr(address);
    client->connectToHost(addr, port);

//    if (client->waitForConnected(3000)){
//        qDebug() << "Connected";
//        *my_flag_socket = true;
//    }
}

bool clientSocket::getMsg(std::string& message)
{
    if (my_flag_socket && msg!="") {
        message = msg.toLocal8Bit().constData();
        return *msgSuccess;
    }
    return false;
}

void clientSocket::showConnection()
{
    *my_flag_socket = true;
    qDebug() << "Socket is connected!!!!!!";

}

bool clientSocket::getStatus()
{
    return *my_flag_socket;
}
