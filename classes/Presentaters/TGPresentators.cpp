#include "TGPresentators.h"
#include <iostream>
#include <QTcpSocket>

SettingsStruct TGPresentators::settings;

TGPresentators::TGPresentators(){}

void TGPresentators::present(const std::vector<Result>& results) {
    if(settings.ip.empty()) {
        std::cerr << "TGPresentators is not init!" << std::endl;
        return;
    }

    QTcpSocket socket;
    socket.connectToHost("127.0.0.1", 2003);
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



void TGPresentators::setSettings(const SettingsStruct& settings_){
    settings = settings_;
}
