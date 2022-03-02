//
// Created by 17105727 on 30.09.2021.
//

#ifndef GVIEWER_POINT3_H
#define GVIEWER_POINT3_H

#include "../../Utils/BaseObject.h++"
#include "../../Exceptions/Math.h++"

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

    Point3(const Point3<X, Y, Z> &copy) noexcept = default;
    Point3(Point3<X, Y, Z> &&move) noexcept = default;

    Point3& operator = (const Point3<X, Y, Z> &copy) noexcept = default;
    Point3& operator = (Point3<X, Y, Z> &&move) noexcept = default;

    ~Point3() noexcept override = default;

    bool operator == (const Point3<X, Y, Z> &rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }
    bool operator != (const Point3<X, Y, Z> &rhs) const {
        return !(rhs == *this);
    }

    virtual Point3<X, Y, Z> operator + (const Point3<X, Y, Z> &rhs) const noexcept {
        Point3<X, Y, Z> ans = Point3(x + rhs.x, y + rhs.y, z + rhs.z);
        return ans;
    }
    virtual Point3<X, Y, Z> operator - (const Point3<X, Y, Z> &rhs) const noexcept {
        Point3<X, Y, Z> ans = Point3(x - rhs.x, y - rhs.y, z - rhs.z);
        return ans;
    }

    virtual Point3<X, Y, Z>& operator += (const Point3<X, Y, Z> &rhs) noexcept {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }
    virtual Point3<X, Y, Z>& operator -= (const Point3<X, Y, Z> &rhs) noexcept {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    virtual Point3<X, Y, Z> operator * (double rhs) const noexcept {
        Point3 ans(*this);
        ans.x *= rhs;
        ans.y *= rhs;
        ans.z *= rhs;
        return ans;
    }
    virtual Point3<X, Y, Z> operator / (double rhs) const {
        if (doubleEq(rhs, 0))
            throw DivideByZeroError(EXC_PARAMS);
        return *this * (1/rhs);
    }

    virtual Point3<X, Y, Z>& operator *= (double rhs) noexcept {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }
    virtual Point3<X, Y, Z>& operator /= (double rhs) {
        if (doubleEq(rhs, 0))
            throw DivideByZeroError(EXC_PARAMS);
        return *this *= (1/rhs);
    }

    virtual Point3<X, Y, Z> operator - () const noexcept {
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
