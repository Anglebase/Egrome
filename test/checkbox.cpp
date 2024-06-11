#include "checkbox.h"
#include "App.h"
// 复选框控件使用示例及测试代码

int main()
{
    Block block{
        Rect{
            0,
            0,
            1000,
            600,
        }};
    CheckBox checkbox{
        Rect{
            100,
            100,
            200,
            30,
        },
        &block,
    };
    checkbox.setText(L"复选框");
    checkbox.checkedChanged.connect([](bool checked)
                                    { std::cout << "CheckBox checked: " << checked << std::endl; });
    checkbox.style.boxSize = 20;
    App app{
        &block,
    };
    app.run();
    return 0;
}