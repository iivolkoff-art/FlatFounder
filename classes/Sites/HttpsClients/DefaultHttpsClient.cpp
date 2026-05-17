#include "DefaultHttpsClient.h"
#include <QEventLoop>
#include <QNetworkReply>
#include <QCoreApplication>
#include <iostream>

DefaultHttpsClient::DefaultHttpsClient() {
    if (!QCoreApplication::instance()) {
        static int argc = 1;
        static char* argv[] = {(char*)"qt_network_client", nullptr};
        static QCoreApplication a(argc, argv);
    }

}


std::string DefaultHttpsClient::getInfo(const QUrl& url) {

    QNetworkAccessManager manager;
    QNetworkRequest request(url);
    request.setRawHeader("Accept", "application/json");
    request.setHeader(QNetworkRequest::UserAgentHeader,
                      "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36");

    QNetworkReply* reply = manager.get(request);
    if (!reply){
        std::cerr << "Error: Could not create QNetworkReply" << std::endl;
        return "";
    }

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    std::string result;
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        result = std::string(response.constData(), static_cast<size_t>(response.length()));
    } else {
        std::cerr << "Error: " + reply->errorString().toStdString() << std::endl;
        result = "";
    }

    reply->deleteLater();
    return result;
}
