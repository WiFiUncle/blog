
### 1. include����ͷ�ļ��������,˫���źͼ����ŵ�����

#include <>��ʽ�����ñ�׼��ͷ�ļ����������ӱ�׼��Ŀ¼��ʼ����
#incluce ""��ʽ�����÷Ǳ�׼���ͷ�ļ������������û��Ĺ���Ŀ¼��ʼ����

### 2. ��UI�ؼ����¼�

```
    // 1. ��UI�мӸ�button�ؼ���������Ϊ��myBtn��
    
    // 2. ��demo.h����ӣ�
    public slots:
        void myClickEvent();
        
    // 3. ��demo.cpp�Ĺ��캯�������    
    connect(ui->myBtn,SIGNAL(clicked()),this,SLOT(myClickEvent())); 
    //SIGNAL�е�clicked������ϵͳ�Լ��ģ�
    
    // 4. ��demo.cpp��ʵ��
    void demo::myClickEvent()
    {
        qDebug() << "you clicked the button.";
        //��������:invalid use of incomplete type 'class QDebug'
        // ����:forward declaration of 'class QDebug'
        //�Ǿ���û��#include <QDebug> ���ͷ�ļ���
    }
```
### 3. �Կؼ�������ʾ/���أ��ı�������Ϣ

```
    ui->myBtn->setText("�������ң������");
    ui->myBtn->setVisible(true); //����false ����
```

---

### 4. ����http����

    
#### 4.1 ����mynetworkobject.cpp �� mynetworkobject.h ���㹤����

(ps: �������ļ��������ҵģ��������޸�)

#### 4.2 ��ͷ�ļ������ #include "mynetworkobject.h"


```
// ��������mainwindow.h �����(�������ر�˵�������Ա�demoΪ��)
#include "mynetworkobject.h"
```
#### 4.3 ��mainwindow.h����һ��networkObj����

```
//��public��
MyNetworkObject *networkObj;


```

#### 4.4  ��mainwindow.h���һ������ɹ���ʧ�ܵķ�����

```
public slots:
    void requestFail(QString str); //���͡�ʧ���źš�ʱ�������÷���
    void requestSuccess(QString str);//���͡��ɹ��źš�ʱ�������÷���
};
    
```

#### 4.5 ����mainwindow.cppʵ�ָ������ۺ���


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
#### 4.6 ��mainwindow.cpp �Ĺ��캯�������

```
    networkObj = new MyNetworkObject(); //�������������
    connect(networkObj,SIGNAL(requestSuccessSignal(QString)),this,SLOT(requestSuccess(QString))); //����ɹ��ź���������ɹ�����
    connect(networkObj,SIGNAL(requestFailSignal(QString)),this,SLOT(requestFail(QString)));     //ʧ��
    
    QUrl url("http://1.aosik.applinzi.com/demo/api/getUuid.php"); //�����ַ
    networkObj->get(url); //����get����
    
```

##### ע���������ź���mynetworkobject.hͷ�ļ��У��Լ�����ġ����ƿ��Ըģ����Ǽǵ������õ�����źŵĵط�ҲҪһ��Ĺ�

```
// ��������ź�
signals:
    void requestFailSignal(QString str); //����ʧ��ʱ����������ź�
    void requestSuccessSignal(QString str); //����ɹ�ʱ����������ź�
```

#### 4.7 �ڹ��̵�pro�ļ������ QT       += network 


```
QT       += network
```

#### 4.8 �ڹ��̵�pro�ļ��е�SOURCES���  mynetworkobject.cpp��HEADERS���mynetworkobject.h. (ps: �ǵ�����һ��ĺ���Ӹ���б��\Ŷ���м��мǣ�����������д��������)


```
SOURCES += main.cpp\
        mainwindow.cpp\
        mynetworkobject.cpp 

HEADERS  += mainwindow.h\
            mynetworkobject.h

FORMS    += mainwindow.ui
```
����һ�£����¹���������������û�й������������ļ���û�����ʾʧ���ˡ���ϸ����¡�

#### 4.9 ��һ��Ҫ����û�и���д���ź������Ͳ��øġ�
```
    if(reply->error() == QNetworkReply::NoError) {
        qDebug()<<"NoError";
        QByteArray buffer = reply->readAll();
        dataStr = QString::fromUtf8(buffer);
        emit requestSuccessSignal(dataStr); //�˴������ɹ��ź�
    } else {
        emit requestFailSignal(reply->errorString());  //�˴�����ʧ���ź�
    }
    reply->deleteLater();
```

����������һ�����һ��get����

������log��Ϣ��������
```
���Կ�ʼ
get   QUrl( "http://1.aosik.applinzi.com/demo/api/getUuid.php" )  
"HttpStatusCodeAttribute = 200" 
"HttpReasonPhraseAttribute = OK" 
NoError 
----------requestSuccess------------- 
"{"uuid":"123456789"}" 
```
�Ұε����߲�����



```
���Կ�ʼ
get   QUrl( "http://1.aosik.applinzi.com/demo/api/getUuid.php" )  
"HttpStatusCodeAttribute = " 
"HttpReasonPhraseAttribute = " 
----------requestFail------------- 
"Host 1.aosik.applinzi.com not found" 
```
���������Կ�~~~

�����Ǹ����Խӿڵ�php����

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





