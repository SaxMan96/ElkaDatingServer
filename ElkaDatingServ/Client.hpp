#ifndef CLIENT_HPP
#define CLIENT_HPP

#include<stdio.h>
#include<iostream>

// unix things
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <unistd.h>

// cpp things
#include <unordered_map>
#include <queue>
#include "message.hpp"

#include "SingletonClientList.hpp"


const int MESSAGE_HEADER_SIZE = 16;


class Client
{
private:
    unsigned int clientID_;

    // thread things
    pthread_t readThread_;
    pthread_t logicThread_;
    bool isRegister_;

    // connection things
    int clientSockfd_;
    sockaddr client_addr_;
    socklen_t length_;

    // message queue
    std::queue<Message*> msgQueue_;
    sem_t consumerSem_;
    sem_t msgSem_;

    bool isStillRunning_;

    void sendMessage(Message *msg){

    }

public:
    Client(int clientSockfd, sockaddr client_addr, socklen_t length);
    void setID(unsigned int clientID);

    bool checkIfStillRunning() const;
    bool login();

    void setStillRunningFalse();
    void pushMessage(Message *msg);
    void clean();
    void messageHandler(Message *msg);
    pthread_t getReadThreadID() const;

    int getSocket() const;

    Message* getMessage();
    Message *readMessage();
};

#endif // CLIENT_HPP