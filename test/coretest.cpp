#include <iostream>

#include "core/Point.h"
#include "core/PointF.h"
#include "core/Size.h"
#include "core/SizeF.h"
#include "core/Rect.h"
#include "core/RectF.h"

int main()
{
    // 对于Point类的测试
    Point p1(1, 2);
    Point p2(3, 4);
    Point p3 = p1 + p2;
    std::cout << "p1: " << p1 << std::endl;
    std::cout << "p2: " << p2 << std::endl;
    std::cout << "p3: " << p3 << std::endl;

    // 对于PointF类的测试
    PointF pf1(1.1f, 2.2f);
    PointF pf2(3.3f, 4.4f);
    PointF pf3 = pf1 + pf2;
    std::cout << "pf1: " << pf1 << std::endl;
    std::cout << "pf2: " << pf2 << std::endl;
    std::cout << "pf3: " << pf3 << std::endl;

    // 对于Size类的测试
    Size s1(1, 2);
    Size s2(3, 4);
    Size s3 = s1 + s2;
    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
    std::cout << "s3: " << s3 << std::endl;

    // 对于SizeF类的测试
    SizeF sf1(1.1f, 2.2f);
    SizeF sf2(3.3f, 4.4f);
    SizeF sf3 = sf1 + sf2;
    std::cout << "sf1: " << sf1 << std::endl;
    std::cout << "sf2: " << sf2 << std::endl;
    std::cout << "sf3: " << sf3 << std::endl;

    // 对于Rect类的测试
    Rect r1(1, 2, 3, 4);
    Rect r2(5, 6, 7, 8);
    Rect r3(10, 20, 50, 60);
    std::cout << "r1: " << r1 << std::endl;
    std::cout << "r2: " << r2 << std::endl;
    std::cout << "r3&r2: " << r3.intersects(r2) << std::endl;
    std::cout << "point in r1: " << r1.contains(Point(2, 3)) << std::endl;
    std::cout << "point in r2: " << r2.contains(Point(6, 7)) << std::endl;

    // 对于RectF类的测试
    RectF rf1(1.1f, 2.2f, 3.3f, 4.4f);
    RectF rf2(5.5f, 6.6f, 7.7f, 8.8f);
    RectF rf3(1.1f, 2.2f, 5.5f, 6.6f);
    std::cout << "rf1: " << rf1 << std::endl;
    std::cout << "rf2: " << rf2 << std::endl;
    std::cout << "rf3&rf2: " << rf3.intersects(rf2) << std::endl;
    std::cout << "point in rf1: " << rf1.contains(PointF(2.2f, 3.3f)) << std::endl;
    std::cout << "point in rf2: " << rf2.contains(PointF(6.6f, 7.7f)) << std::endl;

    return 0;
}