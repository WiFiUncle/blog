#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mynetworkobject.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    MyNetworkObject *networkObj;
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

public slots:
    void myClickEvent();
    void requestFail(QString str); //发送“失败信号”时，触发该方法
    void requestSuccess(QString str);//发送“成功信号”时，触发该方法
};

#endif // MAINWINDOW_H
