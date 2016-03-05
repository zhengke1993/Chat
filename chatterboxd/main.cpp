#include "ChatterBoxServer.h"
#include <QCoreApplication>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    ChatterBoxServer *server = new ChatterBoxServer();
    bool success = server->listen(QHostAddress::Any, 12345);
    if(!success)
    {
        qFatal("不能够成功监听12345端口");
    }
    qDebug() << "服务器开启，等待客户端连接......";
    return app.exec();
}
