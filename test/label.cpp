#include "label.h"
#include "App.h"

int main()
{
    Block block{Rect{0, 0, 1000, 600}};
    Label label{
        Rect{
            100,
            100,
            200,
            50,
        },
        &block,
    };
    label.setText(L"古时候有个私塾先生教着几个学生，有个学生挺笨，念书时把“委蛇”念成weishe，先生打他一顿手板，告诉他记住了，这字要念yi，再念错还打你。");
    label.style.textColor = (Color{255, 0, 0});
    label.setPadding(5, 5, 5, 5);
    App app{&block};
    app.run();
    return 0;
}