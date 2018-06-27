#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QHash>
#include <QDebug>

class clientSocket : public QObject
{
    Q_OBJECT
public:
    explicit clientSocket(QObject *parent = 0);
    ~clientSocket();

    void connectSocket(QString address, int port);
    bool getMsg(std::string& message);
    bool getStatus();
    bool *my_flag_socket;
    bool *msgSuccess;

private:
    QTcpSocket *client;
    QString connectionStatus;
    QString msg;
    QHash<QString,int> hash;
//    bool *my_flag_socket;
//    bool *msgSuccess;

signals:

public slots:

private slots:
    void showConnection();
    void parseMsg();
};

#endif // CLIENTSOCKET_H
