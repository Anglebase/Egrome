#pragma once

#include <winsock2.h>
#include <thread>
#include <string>

class AtomicServer
{
};

/**
 * @brief 低并发服务器类
 */
class Server
{
private:
    SOCKET socket_;
    std::thread *thread_;
    bool running_;

public:
    Server(const std::string &ip, int port);
    ~Server();

    void start();
    void stop();
};