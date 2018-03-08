#include "mynetworkobject.h"

MyNetworkObject::MyNetworkObject(QObject *parent) : QObject(parent) {
    networkAccessManager = new QNetworkAccessManager(this);
    dataStr="";
    QObject::connect(networkAccessManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(finishedSlot(QNetworkReply *)));
}
void MyNetworkObject::get(QUrl url) {
    qDebug()<<"get "<<url;
    QNetworkRequest request = QNetworkRequest(url);
    //这里可以加入chrome的请求头部，使其更接近浏览器
    request.setHeader(QNetworkRequest::UserAgentHeader, \
                      QVariant("Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/46.0.2490.76 Mobile Safari/537.36"));
    networkAccessManager->get(request);
}
void MyNetworkObject::finishedSlot(QNetworkReply *reply) {
    printAttribute(reply, QNetworkRequest::HttpStatusCodeAttribute, "HttpStatusCodeAttribute");
    printAttribute(reply, QNetworkRequest::HttpReasonPhraseAttribute, "HttpReasonPhraseAttribute");
//    printAttribute(reply, QNetworkRequest::RedirectionTargetAttribute, "RedirectionTargetAttribute");
//    printAttribute(reply, QNetworkRequest::ConnectionEncryptedAttribute, "ConnectionEncryptedAttribute");
//    printAttribute(reply, QNetworkRequest::CacheLoadControlAttribute, "CacheLoadControlAttribute");
//    printAttribute(reply, QNetworkRequest::CacheSaveControlAttribute, "CacheSaveControlAttribute");
//    printAttribute(reply, QNetworkRequest::SourceIsFromCacheAttribute, "SourceIsFromCacheAttribute");
//    printAttribute(reply, QNetworkRequest::DoNotBufferUploadDataAttribute, "DoNotBufferUploadDataAttribute");
//    printAttribute(reply, QNetworkRequest::HttpPipeliningAllowedAttribute, "HttpPipeliningAllowedAttribute");
//    printAttribute(reply, QNetworkRequest::HttpPipeliningWasUsedAttribute, "HttpPipeliningWasUsedAttribute");
//    printAttribute(reply, QNetworkRequest::CustomVerbAttribute, "CustomVerbAttribute");
//    printAttribute(reply, QNetworkRequest::CookieLoadControlAttribute, "CookieLoadControlAttribute");
//    printAttribute(reply, QNetworkRequest::AuthenticationReuseAttribute, "AuthenticationReuseAttribute");
//    printAttribute(reply, QNetworkRequest::CookieSaveControlAttribute, "CookieSaveControlAttribute");
//    printAttribute(reply, QNetworkRequest::MaximumDownloadBufferSizeAttribute, "MaximumDownloadBufferSizeAttribute");
//    printAttribute(reply, QNetworkRequest::DownloadBufferAttribute, "DownloadBufferAttribute");
//    printAttribute(reply, QNetworkRequest::SynchronousRequestAttribute, "SynchronousRequestAttribute");
//    printAttribute(reply, QNetworkRequest::BackgroundRequestAttribute, "BackgroundRequestAttribute");
//   printAttribute(reply, QNetworkRequest::User, "User");
//    printAttribute(reply, QNetworkRequest::UserMax, "UserMax");
    if(reply->error() == QNetworkReply::NoError) {
        qDebug()<<"NoError";
        QByteArray buffer = reply->readAll();
        dataStr = QString::fromUtf8(buffer);
        emit requestSuccessSignal(dataStr);
    } else {
        emit requestFailSignal(reply->errorString());
    }
    reply->deleteLater();
}
void MyNetworkObject::printAttribute(QNetworkReply *reply, QNetworkRequest::Attribute code, QString codeStr) {
    QVariant attributeVarient = reply->attribute(code);
    QString result = QString("%1 = %2").arg(codeStr).arg(attributeVarient.toString());
    qDebug()<<result;
}
