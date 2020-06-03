#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->myBtn,SIGNAL(clicked()),this,SLOT(myClickEvent())); //对myBtn绑定点击事件


    //http请求
    networkObj = new MyNetworkObject();
    connect(networkObj,SIGNAL(requestSuccessSignal(QString)),this,SLOT(requestSuccess(QString)));
    connect(networkObj,SIGNAL(requestFailSignal(QString)),this,SLOT(requestFail(QString)));

    QUrl url("http://1.aosik.applinzi.com/demo/api/getUuid.php");
    networkObj->get(url);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::myClickEvent()
  {
      qDebug() << "you clicked the button.";
      ui->myBtn->setText("你点击了我，真棒！");
      ui->myBtn->setVisible(true);
}

void MainWindow::requestFail(QString str)
{
    qDebug() << "----------requestFail-------------";
    qDebug() << str;
}

void MainWindow::requestSuccess(QString str)
{
    qDebug() << "----------requestSuccess-------------";
    qDebug() << str;
}


