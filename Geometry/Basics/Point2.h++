//
// Created by 17105727 on 30.09.2021.
//

#ifndef GVIEWER_POINT2_H
#define GVIEWER_POINT2_H

#include <ostream>
#include <sstream>
#include <type_traits>
#include "../../Utils/BaseObject.h++"


template <
        typename X,
        typename Y,
        typename = std::enable_if_t<
                std::is_arithmetic_v<X> && std::is_arithmetic_v<Y>
        >
>
struct Point2: public BaseObject {
    X x;
    Y y;

    Point2() noexcept = default;
    Point2(X x, Y y) noexcept : x(x), y(y) {}

    Point2(const Point2<X, Y> &copy) noexcept {
        if (this == &copy)
            return;
        *this = copy;
    }
    Point2(Point2<X, Y> &&copy) noexcept { *this = copy; }
    Point2<X, Y>& operator = (const Point2<X, Y> &copy) noexcept {
        x = copy.x;
        y = copy.y;
        return *this;
    }
    Point2<X, Y>& operator = (Point2<X, Y> &&copy) noexcept {
        x = copy.x;
        y = copy.y;
        return *this;
    }

    ~Point2() noexcept override = default;

    bool operator==(const Point2<X, Y> &rhs) const {
        return x == rhs.x && y == rhs.y;
    }
    bool operator!=(const Point2<X, Y> &rhs) const {
        return !(rhs == *this);
    }

    Point2<X, Y> operator + (const Point2<X, Y> &rhs) noexcept {
        Point2<X, Y> ans = Point2(x + rhs.x, y + rhs.y);
        return ans;
    }
    Point2<X, Y> operator - (const Point2<X, Y> &rhs) noexcept {
        Point2<X, Y> ans = Point2(x - rhs.x, y - rhs.y);
        return ans;
    }

    Point2<X, Y>& operator += (const Point2<X, Y> &rhs) noexcept {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    Point2<X, Y>& operator -= (const Point2<X, Y> &rhs) noexcept {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Point2<X, Y> operator - () noexcept {
        Point2<X, Y> ans = Point2(-x, -y);
        return ans;
    }

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "point2[" << x << ", " << y << ']';
        return sst.str();
    }
};

using TextureCoordinate = Point2<double, double>;

#endif //GVIEWER_POINT2_H
