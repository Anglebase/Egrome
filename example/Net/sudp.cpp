// UDP服务端

#include <iostream>
#include "net.h"

int main() {
    // 创建UDP服务端
    Server<UDP> server;

    // 绑定端口
    server.bind(5000);

    while (true) {
        Data data;
        // 接收数据
        auto client = server.recvfrom(data);
        // 打印客户端信息
        std::cout << "Received data from " << std::get<IP>(client) << ":" << std::get<Port>(client) << std::endl;
        // 解析数据
        int a = data.read<int>(32);
        // 处理数据
        a++;
        // 发送数据
        data.write<32>(a);
        server.sendto(data, client);
    }
    return 0;
}
