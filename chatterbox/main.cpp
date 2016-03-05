#include "MainWindow.h"
#include <QApplication>
int main(int argc, char **argv)
{
    //GUI入口
    QApplication app(argc, argv);

    //主窗口
    MainWindow mainWindow;
    mainWindow.show();

    //进入消息循环
    return app.exec();
}
