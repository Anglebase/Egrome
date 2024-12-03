#pragma once

#include <string>

/**
 * @brief 客户端类
 * @note 该类基于套接字的TCP/IP协议实现，并提供了发送和接收数据的接口
 */
class Client
{
private:
    void* socket_;
    void* server_addr_;

public:
    /**
     * @brief 构造函数
     * @param ip 服务端IP地址
     * @param port 服务端端口号
     */
    Client(const char* ip, int port) noexcept;
    /**
     * @brief 析构函数
     */
    ~Client() noexcept;

    /**
     * @brief 连接到服务端
     * @throws 连接失败时抛出 ConnectFailed 异常
     */
    void connect();
    /**
     * @brief 向服务端发送二进制数据
     * @param data 二进制数据指针
     * @param size 二进制数据大小(以字节大小计)
     */
    void send(const void* data, int size);
    /**
     * @brief 向服务端发送字符串数据
     * @param data 字符串数据
     */
    void send(const std::string& data);
    /**
     * @brief 向服务端发送宽字符字符串数据
     * @param data 宽字符字符串数据
     * @note 通常情况下，应使用此函数
     */
    void send(const std::wstring& data);

    /**
     * @brief 从服务端接收二进制数据
     * @param data 接收缓冲区指针
     * @param size 接收缓冲区大小(以字节大小计)
     */
    void receive(void* data, int size);
    /**
     * @brief 从服务端接收字符串数据
     * @param data 接收字符串数据
     */
    void receive(std::string& data);
    /**
     * @brief 从服务端接收宽字符字符串数据
     * @param data 接收宽字符字符串数据
     * @note 通常情况下，应使用此函数
     */
    void receive(std::wstring& data);

    /**
     * @brief 关闭连接
     */
    void close();
};