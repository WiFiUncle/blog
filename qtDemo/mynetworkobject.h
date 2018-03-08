#ifndef MYNETWORKOBJECT_H
#define MYNETWORKOBJECT_H
#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QImageReader>
class MyNetworkObject : public QObject
{
    Q_OBJECT
public:
    explicit MyNetworkObject(QObject *parent = 0);
    void get(QUrl url);
    void printAttribute(QNetworkReply *reply, QNetworkRequest::Attribute code, QString codeStr);
    QString dataStr;
public slots:
    void finishedSlot(QNetworkReply *reply);
signals:
    void requestFailSignal(QString str); //请求失败时，发送这个信号
    void requestSuccessSignal(QString str); //请求成功时，发送这个信号

private:
    QNetworkAccessManager *networkAccessManager;
};
#endif // MYNETWORKOBJECT_H
