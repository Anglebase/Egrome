// UDP客户端

#include <iostream>
#include "net.h"

int main() {
    // 创建UDP客户端
    Client<UDP> client;

    while (true) {
        char str[] = "Hello, world!";
        int a;
        std::cout << "Enter a number: ";
        std::cin >> a;


        // 发送数据
        Data data(40);
        data.write<0>(str);
        data.write<32>(a);

        client.sendto(data, { "127.0.0.1",5000 });
        std::cout << "Sent data to 127.0.0.1:5000" << std::endl;

        // 接收数据
        auto res = client.recvfrom(data);
        std::cout << "Received data from " << std::get<IP>(res) << ":" << std::get<Port>(res) << std::endl;

        a = data.read<int>(32);
        std::string str1 = data.read(0, 32);

        std::cout << "Received message: " << str1 << " " << a << std::endl;

    }
    return 0;
}

