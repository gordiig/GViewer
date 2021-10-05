//
// Created by 17105727 on 30.09.2021.
//

#ifndef GVIEWER_POINT3_H
#define GVIEWER_POINT3_H

#include <ostream>
#include <sstream>
#include "../../Utils/BaseObject.h++"

template <
        typename X,
        typename Y,
        typename Z,
        typename = std::enable_if_t<
                std::is_arithmetic_v<X> && std::is_arithmetic_v<Y> && std::is_arithmetic_v<Z>
        >
>
struct Point3: public BaseObject {
    X x;
    Y y;
    Z z;

    Point3() noexcept = default;
    Point3(X x, Y y, Z z) noexcept: x(x), y(y), z(z) {}

    static Point3<X, Y, Z> zero() noexcept { return Point3(0, 0, 0); }
    static Point3<X, Y, Z> unit() noexcept { return Point3(1, 1, 1); }

    Point3(const Point3<X, Y, Z> &copy) noexcept {
        if (this == &copy)
            return;
        *this = copy;
    }
    Point3(Point3<X, Y, Z> &&move) noexcept { *this = move; }
    Point3<X, Y, Z>& operator = (const Point3<X, Y, Z> &copy) noexcept {
        x = copy.x;
        y = copy.y;
        z = copy.z;
        return *this;
    }
    Point3<X, Y, Z>& operator = (Point3<X, Y, Z> &&move) noexcept {
        x = move.x;
        y = move.y;
        z = move.z;
        return *this;
    }

    ~Point3() noexcept override = default;

    bool operator == (const Point3<X, Y, Z> &rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }
    bool operator != (const Point3<X, Y, Z> &rhs) const {
        return !(rhs == *this);
    }

    Point3<X, Y, Z> operator + (const Point3<X, Y, Z> &rhs) const noexcept {
        Point3<X, Y, Z> ans = Point3(x + rhs.x, y + rhs.y, z + rhs.z);
        return ans;
    }
    Point3<X, Y, Z> operator - (const Point3<X, Y, Z> &rhs) const noexcept {
        Point3<X, Y, Z> ans = Point3(x - rhs.x, y - rhs.y, z - rhs.z);
        return ans;
    }

    Point3<X, Y, Z>& operator += (const Point3<X, Y, Z> &rhs) noexcept {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }
    Point3<X, Y, Z>& operator -= (const Point3<X, Y, Z> &rhs) noexcept {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    Point3<X, Y, Z> operator - () noexcept {
        Point3<X, Y, Z> ans = Point3(-x, -y, -z);
        return ans;
    }

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "point3[" << x << ", " << y << ", " << z << ']';
        return sst.str();
    }
};


using Coordinate = Point3<double, double, double>;
using ScreenCoordinate = Point3<size_t , size_t , double>;

#endif //GVIEWER_POINT3_H
