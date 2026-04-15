#ifndef ISITES_H
#define ISITES_H
#endif // ISITES_H
#pragma once


class ISites{
public:
    virtual void generateRequest() = 0;
    virtual void sendRequest() = 0;
    virtual void receiveRequest() = 0;
};
