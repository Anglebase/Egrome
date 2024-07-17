// TCP客户端

#include <iostream>
#include "net.h"

int main() {
    // 创建TCP客户端
    Client<TCP> client;

    // 连接到服务器
    client.connect("127.0.0.1", 8080);

    while (true) {
        int n;
        std::cin >> n;
        // 向服务器发送数据
        client << "Hello, world!" << n;
        
        if (n == 0) {
            break;
        }

        // 定义接收数据的变量
        std::string str;
        int a;

        // 从服务器接收数据
        client >> str >> a;

        // 输出接收到的数据
        std::cout << str << std::endl;
        std::cout << a << std::endl;
    }

    return 0;
}