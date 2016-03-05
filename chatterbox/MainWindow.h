#include <QMainWindow>
#include <QTcpSocket>
#include "ui_MainWindow.h"//包含GUI的头文件

//MainWindow公有继承于QMainWindow
class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT  //Qt的元对象系统

    public:
       //构造函数
        MainWindow(QWidget *parent=0);
       ~MainWindow();//析构函数
    private slots:
        //私有槽函数
        void on_loginButton_clicked();
        void on_sayButton_clicked();
        void readyRead();
        void connected();

        void on_exitButton_clicked();

        void on_serverLineEdit_returnPressed();

        void on_pushButton_clicked();
private:
        //私有成员socket指针
        QTcpSocket *socket;
};
