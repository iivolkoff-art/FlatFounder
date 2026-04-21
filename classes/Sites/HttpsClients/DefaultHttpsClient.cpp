#include "DefaultHttpsClient.h"
#include <QEventLoop>
#include <QNetworkReply>

DefaultHttpsClient::DefaultHttpsClient() {
    manager = std::make_unique<QNetworkAccessManager>();
}


std::string DefaultHttpsClient::getInfo(const QUrl& url){
    QNetworkRequest request(url);

    request.setRawHeader("Accept", "application/json");

    request.setHeader(QNetworkRequest::UserAgentHeader,
                      "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36");

    QNetworkReply* reply = manager->get(request);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    std::string result;
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        result = response.toStdString();
    } else {
        result = "Error: " + reply->errorString().toStdString();
    }

    reply->deleteLater();
    return result;
}
