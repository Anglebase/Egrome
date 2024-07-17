// TCP服务端

#include<iostream>
#include"net.h"

int main() {
    // 创建TCP服务端
    Server<TCP> server;

    std::cout << "Server started on port 8080" << std::endl;
    // 绑定端口
    server.bind(8080);
    std::cout << "Waiting for clients..." << std::endl;
    // 启用监听，半连接池长度为5
    server.listen(5);

    int a = 5;
    while (true) {
        // 从半连接池中接受一个连接
        auto client = server.accept();
        // 打印客户端信息
        std::cout << "Client connected:" << client << std::endl;

        std::string message = "Welcome to the server!";

        // 定义接受信息的变量
        std::string str;
        int k = 1;
        while (k) {
            try {
                // 接收客户端发送的消息
                client >> str >> k;
                // 打印接收到的消息
                std::cout << "Received message: " << str << " and " << k << std::endl;
                // 返回给客户端一个消息
                client << message << a++;
                // 关闭与客户端的连接
            }
            catch (std::runtime_error& e) {
                std::cout << e.what() << std::endl;
                break;
            }
        }
        std::cout << "Client disconnected:" << client << std::endl;
        client.close();
    }

    // 关闭服务端
    server.close();
    return 0;
}