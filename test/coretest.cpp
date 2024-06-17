#include <iostream>

#include "core/Point.h"
#include "core/Size.h"
#include "core/Rect.h"

int main()
{
    // 对于Point类的测试
    Point p1(1, 2);
    Point p2(3, 4);
    Point p3 = p1 + p2;
    std::cout << "p1: " << p1 << std::endl;
    std::cout << "p2: " << p2 << std::endl;
    std::cout << "p3: " << p3 << std::endl;

    // 对于Size类的测试
    Size s1(1, 2);
    Size s2(3, 4);
    Size s3 = s1 + s2;
    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
    std::cout << "s3: " << s3 << std::endl;

    // 对于Rect类的测试
    Rect r1(1, 2, 3, 4);
    Rect r2(5, 6, 7, 8);
    Rect r3(10, 20, 50, 60);
    std::cout << "r1: " << r1 << std::endl;
    std::cout << "r2: " << r2 << std::endl;
    std::cout << "r3&r2: " << r3.intersects(r2) << std::endl;
    std::cout << "point in r1: " << r1.contains(Point(2, 3)) << std::endl;
    std::cout << "point in r2: " << r2.contains(Point(6, 7)) << std::endl;

    return 0;
}