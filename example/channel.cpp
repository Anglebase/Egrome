// 通道使用示例

#include <iostream>
#include "Channel.hpp"
#include <thread>
using namespace std::chrono_literals;

int main() {
    // 创建一个channel
    Channel<int> channel;

    std::thread producer([&]() {
        for (int i = 0; i < 10; i++) {
            // 两种方式写入数据
            channel << i * 2;
            (i + 1) >> channel;
            std::this_thread::sleep_for(500ms);
        }
        // 通知channel生产结束，关闭channel
        channel.close();
        });


    std::thread consumer([&]() {
        int value;
        // 从channel读取数据，直到channel关闭
        while (channel >> value) {
            // 读取到数据后打印出来
            std::cout << value << std::endl;
        }
        });

    // 等待线程结束
    producer.join();
    consumer.join();

    return 0;
}