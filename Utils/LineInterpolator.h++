//
// Created by 17105727 on 18.10.2021.
//

#ifndef GVIEWER_LINEINTERPOLATOR_H
#define GVIEWER_LINEINTERPOLATOR_H

#include "BaseObject.h++"
#include "Containers/Pair.h++"
#include "../Exceptions/Math.h++"
#include "../Geometry/Basics/Point2.h++"


template<
        typename T1,
        typename T2,
        typename = std::enable_if_t<
            std::is_arithmetic_v<T1> && std::is_arithmetic_v<T2>
        >
>
class LineInterpolator: public BaseObject {
protected:
    using Line1 = Pair<Point2<T1, T1>, Point2<T1, T1>>;
    using Line2 = Pair<Point2<T2, T2>, Point2<T2, T2>>;

    Line1 baseline;
    Line2 interpolateCorners;

public:
    LineInterpolator(const Line1 &baseline, const Line2 &interpolateCorners) noexcept :
            baseline(baseline), interpolateCorners(interpolateCorners) { }

    LineInterpolator(const LineInterpolator<T1, T2> &copy) noexcept = default;
    LineInterpolator(LineInterpolator<T1, T2> &&move) noexcept = default;

    LineInterpolator& operator = (const LineInterpolator<T1, T2> &copy) noexcept = default;
    LineInterpolator& operator = (LineInterpolator<T1, T2> &&move) noexcept = default;

    T2 interpolateX(const Point2<T1, T1>& pt) const {
        if (baseline.first.x < baseline.second.x) {
            if (baseline.first.x > pt.x || pt.x > baseline.second.x) {
                throw InterpolationError(EXC_PARAMS);
            }
        } else {
            if (baseline.second.x > pt.x || pt.x > baseline.first.x) {
                throw InterpolationError(EXC_PARAMS);
            }
        }

        double t;
        if (baseline.first.x == baseline.second.x)
            t = 0.5;
        else
            t = (pt.x - baseline.first.x) / (baseline.second.x - baseline.first.x);

        T2 ans = (1 - t) * interpolateCorners.first.x + t * interpolateCorners.second.x;
        return ans;
    }
    T2 interpolateY(const Point2<T1, T1> &pt) const {
        if (baseline.first.y < baseline.second.y) {
            if (baseline.first.y > pt.y || pt.y > baseline.second.y) {
                throw InterpolationError(EXC_PARAMS);
            }
        } else {
            if (baseline.second.y > pt.y || pt.y > baseline.first.y) {
                throw InterpolationError(EXC_PARAMS);
            }
        }

        double t;
        if (baseline.first.y == baseline.second.y)
            t = 0.5;
        else
            t = (pt.y - baseline.first.y) / (baseline.second.y - baseline.first.y);

        T2 ans = (1 - t) * interpolateCorners.first.y + t * interpolateCorners.second.y;
        return ans;
    }
    Point2<T2, T2> interpolate(const Point2<T1, T1> &pt) const {
        T2 interpolatedX = interpolateX(pt);
        T2 interpolatedY = interpolateY(pt);
        return {interpolatedX, interpolatedY};
    }

    ~LineInterpolator() noexcept override = default;

    [[nodiscard]] std::string toString() const override { return "[Interpolator]"; }
};

#endif //GVIEWER_LINEINTERPOLATOR_H
