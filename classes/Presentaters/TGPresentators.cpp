#include "TGPresentators.h"
#include <iostream>
#include <QTcpSocket>
#include <Settings/SettingsSingltons.h>


TGPresentators::TGPresentators(std::unique_ptr<IConverter<QJsonDocument, std::vector<Result>>> toJsonConverter_) : toJsonConverter(std::move(toJsonConverter_)) {}

void TGPresentators::present(const std::vector<Result>& results) {
    QTcpSocket socket;
    socket.connectToHost(QString::fromStdString(SettingsSingltons::instance().getSettings().ip),
                        SettingsSingltons::instance().getSettings().port);

    QByteArray jsonData = toJsonConverter->convert(results).toJson(QJsonDocument::Compact);

    if (socket.waitForConnected(100)) {
        jsonData.append('\n');

        socket.write(jsonData);
        socket.waitForBytesWritten(100);

        socket.disconnectFromHost();
        if (socket.state() != QAbstractSocket::UnconnectedState) {
            socket.waitForDisconnected(100);
        }
    } else {
        std::cout << "Connection to TGBot is failed! " << socket.errorString().toStdString() << std::endl;
    }
}
