// 本地数据的使用示例

#include<iostream>
#include"Database.hpp"

using Line = std::tuple<std::string, std::string, int>;
enum { name, tel, age };    // 使用枚举类型来表示数据库表的列索引

// 自定义数据库类，继承自Table<Line>模板类，自定义读写格式化函数
class MyDatabase : public Table<Line> {
    const std::size_t name_lenth = 10;
    const std::size_t tel_lenth = 15;
    const unsigned char pwdkey = 0x85; // 异或加密密钥
protected:
    // 重写父类中的读写格式化函数，数据是否加密，采用什么加密方式，数据如何序列化和反序列化，均可以通过这两个函数进行自定义
    void readLine(const void* input, Line& data) override {
        // decrypt data
        // for (int i = 0; i < this->lenth; i++) ((char*)input)[i] ^= pwdkey; // 简单的异或加密，可以避免直接暴露明文
        // parse data
        char name_buf[name_lenth + 1];
        char tel_buf[tel_lenth + 1];
        std::memcpy(name_buf, (char*)input, name_lenth);
        name_buf[name_lenth] = '\0';
        std::memcpy(tel_buf, (char*)input + name_lenth, tel_lenth);
        tel_buf[tel_lenth] = '\0';
        std::get<name>(data) = std::string(name_buf);
        std::get<tel>(data) = std::string(tel_buf);
        std::get<age>(data) = *(int*)((char*)input + name_lenth + tel_lenth);
    }
    void writeLine(void* output, const Line& data) override {
        // parse data
        std::memcpy(output, std::get<name>(data).c_str(), name_lenth);
        std::memcpy((char*)output + name_lenth, std::get<tel>(data).c_str(), tel_lenth);
        *(int*)((char*)output + name_lenth + tel_lenth) = std::get<age>(data);
        // encrypt data
        // for (int i = 0; i < this->lenth; i++) ((char*)output)[i] ^= pwdkey; // 简单的异或加密，可以避免直接暴露明文
    }
    void printLine(const Line& data) const override {
        std::cout << std::get<name>(data) << " " << std::get<tel>(data) << " " << std::get<age>(data) << std::endl;
    }
public:
    MyDatabase() {
        this->lenth = name_lenth + tel_lenth + sizeof(int);  // 设置数据长度
        // 如果数据中存在复杂类型(例如：std::string)，则必须指定lenth的值，否则会导致内存分配错误
    }
};

int main() {
    MyDatabase db;  // 实例化数据库对象
    // 向数据库中插入数据
    db.append({ "Alice", "13700987656", 20 });
    db.append({ "Bob", "13700987657", 22 });
    db.append({ "Charlie", "13700987658", 22 });
    db.append({ "David", "13700987659", 45 });
    db.append({ "Eve", "13700987660", 34 });
    db.append({ "Frank", "13700987661", 26 });
    db.append({ "Grace", "13700987662", 31 });
    db.append({ "Henry", "13700987663", 17 });
    db.append({ "Isabelle", "13700987664", 35 });
    db.append({ "张三", "13700987665", 38 });
    db.append({ "王五", "13700987667", 34 });
    db.append({ "李四","13723087665",31 });

    std::cout << "数据库内容" << std::endl;
    db.print();
    db.saveDatabase("mydatabase.db");  // 保存数据库到文件

    db.clear();

    MyDatabase db2;  // 实例化另一个数据库对象
    db2.loadDatabase("mydatabase.db");  // 从文件加载上面保存的数据库
    std::cout << std::string(40, '-') << std::endl;
    db2.print();  // 打印数据库内容

    // 查找年龄大于30岁的用户，并将他们的姓名和电话号码打印出来
    auto res = db2.find_index_if<age>([](int age)->bool { return age > 30; });
    std::cout << std::string(40, '-') << std::endl;
    std::cout << "年龄大于30岁的用户：" << std::endl;
    for (auto& line_ : res) {
        auto& line = *line_.first;
        std::cout << std::get<name>(line) << " " << std::get<tel>(line) << std::endl;
    }

    // 查找所有年龄大于35岁的用户，并将它们从数据库中删除
    unsigned long long res2 = db2.revoke_if<age>([](int age)->bool { return age > 35; });
    std::cout << "删除年龄大于35岁的用户个数：" << res2 << std::endl;

    std::cout << std::string(40, '-') << std::endl;
    std::cout << "删除年龄大于35岁的用户后：" << std::endl;
    db2.print();  // 打印数据库内容

    db2.saveDatabase("mydatabase.db");  // 保存数据库到文件

    // db2.clear();  // 这行并不是必须的，每次离开数据库名所在作用域时，它们会被自动释放 
                     // 但若要加载多个数据库，未使用的应及时释放
    return 0;
}