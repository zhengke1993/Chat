#include "ChatterBoxServer.h"
#include <QTcpSocket>
#include <QRegExp>

ChatterBoxServer::ChatterBoxServer(QObject *parent) : QTcpServer(parent)
{
    //构造函数
}

void ChatterBoxServer::incomingConnection(int socketfd)//当客户端建立新连接时
{
    QTcpSocket *client = new QTcpSocket(this);
    client->setSocketDescriptor(socketfd);
    clients.insert(client);

    qDebug() << "来自:" << client->peerAddress().toString()<<"的客户端连接成功";

    connect(client, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void ChatterBoxServer::readyRead()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    while(client->canReadLine())
    {
        QString line = QString::fromUtf8(client->readLine()).trimmed();
        qDebug() << "消息:" << line;
        QRegExp meRegex("^/me:(.*)$");//正则表达式通过^/me:匹配后面的字符串
        if(meRegex.indexIn(line) != -1)
        {
            QString user = meRegex.cap(1);
            users[client] = user;
            foreach(QTcpSocket *client, clients)
                client->write(QString("服务器:" + user + " 进入了聊天室\n").toUtf8());
            sendUserList();
        }
        else if(users.contains(client))
        {
            QString message = line;
            QString user = users[client];
            qDebug() << "用户:" << user;
            qDebug() << "信息:" << message;

            foreach(QTcpSocket *otherClient, clients)
                otherClient->write(QString(user + ":" + message + "\n").toUtf8());
        }
        else
        {
            qWarning() << "来自客户端错误的连接:" << client->peerAddress().toString() << line;
        }
    }
}

void ChatterBoxServer::disconnected()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    qDebug() << "断开连接:" << client->peerAddress().toString();

    clients.remove(client);

    QString user = users[client];
    users.remove(client);

    sendUserList();
    foreach(QTcpSocket *client, clients)
        client->write(QString("服务器:" + user + " 离开了聊天室\n").toUtf8());
}

void ChatterBoxServer::sendUserList()//向客户端发送用户列表
{
    QStringList userList;
    foreach(QString user, users.values())
        userList << user;

    foreach(QTcpSocket *client, clients)
        client->write(QString("/users:" + userList.join(",") + "\n").toUtf8());
}
