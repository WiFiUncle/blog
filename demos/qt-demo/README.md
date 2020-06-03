
### 1. include包含头文件的语句中,双引号和尖括号的区别

#include <>格式：引用标准库头文件，编译器从标准库目录开始搜索
#incluce ""格式：引用非标准库的头文件，编译器从用户的工作目录开始搜索

### 2. 对UI控件绑定事件

```
    // 1. 在UI中加个button控件，并命名为“myBtn”
    
    // 2. 在demo.h中添加：
    public slots:
        void myClickEvent();
        
    // 3. 在demo.cpp的构造函数中添加    
    connect(ui->myBtn,SIGNAL(clicked()),this,SLOT(myClickEvent())); 
    //SIGNAL中的clicked方法是系统自己的，
    
    // 4. 在demo.cpp中实现
    void demo::myClickEvent()
    {
        qDebug() << "you clicked the button.";
        //若报错误:invalid use of incomplete type 'class QDebug'
        // 错误:forward declaration of 'class QDebug'
        //那就是没有#include <QDebug> 这个头文件哈
    }
```
### 3. 对控件设置显示/隐藏，改变文字信息

```
    ui->myBtn->setText("你点击了我，真棒！");
    ui->myBtn->setVisible(true); //参数false 隐藏
```

---

### 4. 发送http请求

    
#### 4.1 拷贝mynetworkobject.cpp 和 mynetworkobject.h 到你工程中

(ps: 这两个文件在网上找的，本人有修改)

#### 4.2 在头文件中添加 #include "mynetworkobject.h"


```
// 本人是在mainwindow.h 中添加(以下无特别说明，均以本demo为例)
#include "mynetworkobject.h"
```
#### 4.3 在mainwindow.h定义一个networkObj变量

```
//在public中
MyNetworkObject *networkObj;


```

#### 4.4  在mainwindow.h添加一个请求成功和失败的方法。

```
public slots:
    void requestFail(QString str); //发送“失败信号”时，触发该方法
    void requestSuccess(QString str);//发送“成功信号”时，触发该方法
};
    
```

#### 4.5 并在mainwindow.cpp实现该两个槽函数


```
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
```
#### 4.6 在mainwindow.cpp 的构造函数中添加

```
    networkObj = new MyNetworkObject(); //创建个网络对象
    connect(networkObj,SIGNAL(requestSuccessSignal(QString)),this,SLOT(requestSuccess(QString))); //请求成功信号连接请求成功方法
    connect(networkObj,SIGNAL(requestFailSignal(QString)),this,SLOT(requestFail(QString)));     //失败
    
    QUrl url("http://1.aosik.applinzi.com/demo/api/getUuid.php"); //请求地址
    networkObj->get(url); //发送get请求
    
```

##### 注：这两个信号在mynetworkobject.h头文件中，自己定义的。名称可以改，但是记得其他用到这个信号的地方也要一起改哈

```
// 添加两个信号
signals:
    void requestFailSignal(QString str); //请求失败时，发送这个信号
    void requestSuccessSignal(QString str); //请求成功时，发送这个信号
```

#### 4.7 在工程的pro文件中添加 QT       += network 


```
QT       += network
```

#### 4.8 在工程的pro文件中的SOURCES添加  mynetworkobject.cpp，HEADERS添加mynetworkobject.h. (ps: 记得在上一句的后面加个反斜杠\哦。切记切记，按照它的书写规则来。)


```
SOURCES += main.cpp\
        mainwindow.cpp\
        mynetworkobject.cpp 

HEADERS  += mainwindow.h\
            mynetworkobject.h

FORMS    += mainwindow.ui
```
测试一下，重新构建，看工程里有没有关联上这两个文件。没有则表示失败了。仔细检查下。

#### 4.9 这一步要是你没有改我写的信号名，就不用改。
```
    if(reply->error() == QNetworkReply::NoError) {
        qDebug()<<"NoError";
        QByteArray buffer = reply->readAll();
        dataStr = QString::fromUtf8(buffer);
        emit requestSuccessSignal(dataStr); //此处触发成功信号
    } else {
        emit requestFailSignal(reply->errorString());  //此处触发失败信号
    }
    reply->deleteLater();
```

接下来我们一起测试一下get请求

以下是log信息，完美！
```
调试开始
get   QUrl( "http://1.aosik.applinzi.com/demo/api/getUuid.php" )  
"HttpStatusCodeAttribute = 200" 
"HttpReasonPhraseAttribute = OK" 
NoError 
----------requestSuccess------------- 
"{"uuid":"123456789"}" 
```
我拔掉网线测试下



```
调试开始
get   QUrl( "http://1.aosik.applinzi.com/demo/api/getUuid.php" )  
"HttpStatusCodeAttribute = " 
"HttpReasonPhraseAttribute = " 
----------requestFail------------- 
"Host 1.aosik.applinzi.com not found" 
```
霍霍，可以咯~~~

附上那个测试接口的php代码

```
<?php
/**
 * User: WiFi
 * Date: 2018/03/05
 * Time: 09:23
 */
$data = array(
'uuid' => '123456789'
);
//$data = 123456789;
$data = json_encode($data); 
echo $data;

```





