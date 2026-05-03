#include "TGPresentators.h"
#include <iostream>
#include <QTcpSocket>
#include <Settings/SettingsSingltons.h>


TGPresentators::TGPresentators(){}

void TGPresentators::present(const std::vector<Result>& results) {
    QTcpSocket socket;
    socket.connectToHost(QString::fromStdString(SettingsSingltons::instance().getSettings().ip),
                        SettingsSingltons::instance().getSettings().port);
    if (socket.waitForConnected(3000)) {
        for(const auto& x : results) {
            std::string data_to_send = x.link + "\n";
            socket.write(data_to_send.data(), data_to_send.size());
            socket.waitForBytesWritten(1000);
        }
        socket.disconnectFromHost();
        if (socket.state() != QAbstractSocket::UnconnectedState) {
            socket.waitForDisconnected(1000);
        }
    } else {
        std::cout << "Connection to TGBot is failed! " << socket.errorString().toStdString() << std::endl;
    }
}
