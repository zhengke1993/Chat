#include "MainWindow.h"
#include <QRegExp>//添加正则表达式的类
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include<QMessageBox>
//主窗口的构造函数
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    //必须有的
    setupUi(this);
    //把登陆页面设置为当前窗口
    //stackWidget为一个窗口容器
    stackedWidget->setCurrentWidget(loginPage);
    //new一个套接字
    socket = new QTcpSocket(this);//
    //关联信号与槽函数
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    label_7->setOpenExternalLinks(true);
    label_7->setText(tr("<a href=\"http://www.qt.io\">Qt官网"));
    label_7->show();
}
void MainWindow::on_loginButton_clicked()//登陆按钮被点击时，触发槽函数
{
    //与数据库的用户名，密码，进行匹配，如果返回true,进行连接
    //否则，弹出错误对话框
   //调用连接到主机的12345端口
    QString username=usernameLineEdit->text();
    QString userpassword=userpasswordLineEdit->text();
    QString servername=serverLineEdit->text();
    QSqlDatabase db;
    if (QSqlDatabase::contains(username))
        db=QSqlDatabase::database(username);
    else
        db=QSqlDatabase::addDatabase("QMYSQL",username);
    db.setHostName(servername);//设置主机地址
    db.setPort(3306);//设置端口号
    db.setUserName("user");//连接数据库的用户名
    db.setPassword("134679852zk");//连接数据库的密码
    db.setDatabaseName("test");//连接的数据库名称
    if (!db.open())//如果没有连接到数据库
        {
            QMessageBox::warning(this,"数据库连接失败！",tr("错误原因：%0").arg(db.lastError().text()));
            return ;
        }
    else
    {
        QSqlQuery query("select * from information ",db);//遍历所有人
        while (query.next())
        {
            QString un=query.value(0).toString();
            QString up=query.value(1).toString();
            if (un==username&&up==userpassword)
            {
                 socket->connectToHost(servername, 12345);
                 stackedWidget->setCurrentWidget(chatPage);
                 return;
           }
         }
          QMessageBox::information(this,tr("来自数据库的消息"),tr("用户名或密码错误！！"));
         //输入错误时，清除密码框
          //输入错误的时候，保留用户输入框的用户名
          //usernameLineEdit->clear();
          userpasswordLineEdit->clear();
          return;
    }
}
void MainWindow::on_sayButton_clicked()//发送按钮被点击时，触发的槽函数
{
    QString message = sayLineEdit->text().trimmed();
    if(!message.isEmpty())//如果发送的信息非空
    {
        //往套接字缓存中写入数据并发送
        socket->write(QString(message + "\n").toUtf8());
    }

    //清除输入框中的信息，以便能再次发送信息
    sayLineEdit->clear();
    sayLineEdit->setFocus();
}

//接受来自服务器的信息
void MainWindow::readyRead()
{
    //循环遍历来自服务器的消息
    while(socket->canReadLine())
    {
        //line储存来自服务器的字符串，并以UTF-8的编码方式进行转换
        QString line = QString::fromUtf8(socket->readLine()).trimmed();

        //这两个正则表达式来匹配服务器发送的信息
        //  所有的信息像这样：“username:信息”
        QRegExp messageRegex("^([^:]+):(.*)$");

        // 所有像这样"/users:" 是服务器发送给我们的用户列表，显示在客户端
        //的用户列表中
        QRegExp usersRegex("^/users:(.*)$");

        // 如果是一个用户的信息
        if(usersRegex.indexIn(line) != -1)
        {
            // 那么，更新用户列表
            QStringList users = usersRegex.cap(1).split(",");
            userListWidget->clear();
            foreach(QString user, users)
                //给用户添加图片
                new QListWidgetItem(QPixmap(":/user.png"), user, userListWidget);
        }
        // 如果是一条聊天信息
        else if(messageRegex.indexIn(line) != -1)
        {
            // 那么，把信息追加到聊天对话框中
            QString user = messageRegex.cap(1);
            QString message = messageRegex.cap(2);
            roomTextEdit->append("<b>" + user + "</b>: " + message);
        }
    }
}

//成功连接到服务器的槽函数
void MainWindow::connected()
{
    //跳转至聊天页面
    stackedWidget->setCurrentWidget(chatPage);
    //并且把用户名发送到服务器
    socket->write(QString("/me:" + usernameLineEdit->text() + "\n").toUtf8());
}
MainWindow::~MainWindow()
{
    //析构函数，释放内存
}

void MainWindow::on_exitButton_clicked()
{
    this->close();
}

void MainWindow::on_serverLineEdit_returnPressed()//回车登陆
{
    on_loginButton_clicked();
}
void MainWindow::on_pushButton_clicked()
{
    roomTextEdit->clear();
}
