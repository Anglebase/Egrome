// 数据库性能测试

#include<iostream>
#include"Database.hpp"

using Line = std::tuple<std::size_t, int, long, long long, float, double, long double>;

class Database :public Table<Line> {
protected:
    void readLine(const void* ptr, Line& line) override {
        std::get<0>(line) = *(std::size_t*)ptr;
        std::get<1>(line) = *(int*)((char*)ptr);
        std::get<2>(line) = *(long*)((char*)ptr + sizeof(int));
        std::get<3>(line) = *(long long*)((char*)ptr + sizeof(int) + sizeof(long));
        std::get<4>(line) = *(float*)((char*)ptr + sizeof(int) + sizeof(long) + sizeof(long long));
        std::get<5>(line) = *(double*)((char*)ptr + sizeof(int) + sizeof(long) + sizeof(long long) + sizeof(float));
        std::get<6>(line) = *(long double*)((char*)ptr + sizeof(int) + sizeof(long) + sizeof(long long) + sizeof(float) + sizeof(double));
    }
    void writeLine(void* ptr, const Line& line) override {
        *static_cast<std::size_t*>(ptr) = std::get<0>(line);
        *static_cast<int*>(ptr) = std::get<1>(line);
        *(long*)((char*)ptr + sizeof(int)) = std::get<2>(line);
        *(long long*)((char*)ptr + sizeof(int) + sizeof(long)) = std::get<3>(line);
        *(float*)((char*)ptr + sizeof(int) + sizeof(long) + sizeof(long long)) = std::get<4>(line);
        *(double*)((char*)ptr + sizeof(int) + sizeof(long) + sizeof(long long) + sizeof(float)) = std::get<5>(line);
        *(long double*)((char*)ptr + sizeof(int) + sizeof(long) + sizeof(long long) + sizeof(float) + sizeof(double)) = std::get<6>(line);
    }
    void printLine(const Line& line) const override {
        std::cout << std::get<0>(line) << " " << std::get<1>(line) << " " << std::get<2>(line) << " " << std::get<3>(line) << " " << std::get<4>(line) << " " << std::get<5>(line) << std::endl;
    }
};


int main() {
    Database db;

    for (std::size_t i = 0; i < 10000000; ++i)
        db.append({
            i,
            rand() % 100,
            rand() % 10000000000,
            rand() % 1000000000000000000,
            static_cast<float>(rand()) / RAND_MAX,
            static_cast<double>(rand()) / RAND_MAX,
            static_cast<long double>(rand()) / RAND_MAX
            });

    db.print();

    // db.saveDatabase("data.db");

    time_t t = time(nullptr);
    
    auto res = db.find_if<1>([](int k) {return k > 50;});

    std::cout << "Time elapsed: " << difftime(time(nullptr), t) << " seconds" << std::endl;
    std::cout << "Found " << res.size() << " lines with value greater than 50" << std::endl;

    int count = 0;
    for (auto& line_ : res)
    {
        count++;
        if (count > 10) break;
        auto line = *line_;
        std::cout << std::get<0>(line) << " " << std::get<1>(line) << " " << std::get<2>(line) << " " << std::get<3>(line) << " " << std::get<4>(line) << " " << std::get<5>(line) << std::endl;
    }
    std::cout << "Printed first 10 lines" << std::endl;
    count = db.revoke_if<2>([](int k) {return k % 13 == 0;});
    std::cout << "Revoke " << count << " lines with value divisible by 13" << std::endl;
    db.saveDatabase("data.db");
    return 0;
}