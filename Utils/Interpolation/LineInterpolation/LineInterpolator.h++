//
// Created by 17105727 on 18.10.2021.
//

#ifndef GVIEWER_LINEINTERPOLATOR_H
#define GVIEWER_LINEINTERPOLATOR_H

#include <utility>

#include "../../BaseObject.h++"
#include "../../Containers/Pair.h++"
#include "../../../Exceptions/Math.h++"
#include "../../../Geometry/Basics/Point2.h++"


class LineInterpolator: public BaseObject {
protected:
    using Point2Double = Point2<double, double>;
    using Line1 = Pair<Point2Double, Point2Double>;
    using Line2 = Pair<Point2Double, Point2Double>;

    Line1 baseline;
    Line2 interpolateCorners;

public:
    LineInterpolator(Line1 baseline, Line2 interpolateCorners) noexcept :
            baseline(std::move(baseline)), interpolateCorners(std::move(interpolateCorners)) { }

    LineInterpolator(const LineInterpolator &copy) noexcept = default;
    LineInterpolator(LineInterpolator &&move) noexcept = default;

    LineInterpolator& operator = (const LineInterpolator &copy) noexcept = default;
    LineInterpolator& operator = (LineInterpolator &&move) noexcept = default;

    [[nodiscard]] double interpolateX(const Point2Double& pt) const {
        // Checking for extrapolated value
        if (baseline.first.x < baseline.second.x) {
            if (baseline.first.x > pt.x || pt.x > baseline.second.x) {
                throw InterpolationError(EXC_PARAMS);
            }
        } else {
            if (baseline.second.x > pt.x || pt.x > baseline.first.x) {
                throw InterpolationError(EXC_PARAMS);
            }
        }

        // Calculating interpolation coefficient
        double t;
        if (doubleEq(baseline.first.x, baseline.second.x))
            // If originalScale ends are equal,
            // setting coefficient for taking average from interpolation corners
            t = 0.5;
        else
            t = (pt.x - baseline.first.x) / (baseline.second.x - baseline.first.x);

        // Calculating interpolated value
        double ans = (1 - t) * interpolateCorners.first.x + t * interpolateCorners.second.x;
        return ans;
    }
    [[nodiscard]] double interpolateY(const Point2Double &pt) const {
        // Checking for extrapolated value
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
        if (doubleEq(baseline.first.y, baseline.second.y))
            // If originalScale ends are equal,
            // setting coefficient for taking average from interpolation corners
            t = 0.5;
        else
            t = (pt.y - baseline.first.y) / (baseline.second.y - baseline.first.y);

        // Calculating interpolated value
        double ans = (1 - t) * interpolateCorners.first.y + t * interpolateCorners.second.y;
        return ans;
    }
    [[nodiscard]] Point2Double interpolate(const Point2Double &pt) const {
        double interpolatedX = interpolateX(pt);
        double interpolatedY = interpolateY(pt);
        return {interpolatedX, interpolatedY};
    }

    ~LineInterpolator() noexcept override = default;

    [[nodiscard]] std::string toString() const override { return "[LineInterpolator]"; }
};

#endif //GVIEWER_LINEINTERPOLATOR_H
