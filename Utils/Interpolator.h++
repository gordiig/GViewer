//
// Created by 17105727 on 18.10.2021.
//

#ifndef GVIEWER_INTERPOLATOR_H
#define GVIEWER_INTERPOLATOR_H

#include <utility>

#include "BaseObject.h++"
#include "Containers/Pair.h++"
#include "../Exceptions/Math.h++"


class Interpolator: public BaseObject {
protected:
    using PairDouble = Pair<double, double>;

    PairDouble baseline;
    PairDouble interpolateCorners;

public:
    Interpolator(PairDouble baseline, PairDouble interpolateCorners) noexcept :
        baseline(std::move(baseline)), interpolateCorners(std::move(interpolateCorners)) { }

    Interpolator(const Interpolator &copy) noexcept = default;
    Interpolator(Interpolator &&move) noexcept = default;

    Interpolator& operator = (const Interpolator &copy) noexcept = default;
    Interpolator& operator = (Interpolator &&move) noexcept = default;

    [[nodiscard]] double interpolate(const double baselineVal) const {
        if (baseline.first < baseline.second) {
            if (baseline.first > baselineVal || baselineVal > baseline.second) {
                throw InterpolationError(EXC_PARAMS);
            }
        } else {
            if (baseline.second < baselineVal || baselineVal > baseline.first) {
                throw InterpolationError(EXC_PARAMS);
            }
        }

        double t;
        if (doubleEq(baseline.first, baseline.second))
            t = 0.5;
        else
            t = (baselineVal - baseline.first) / (baseline.second - baseline.first);

        double ans = (1.0 - t) * interpolateCorners.first + t * interpolateCorners.second;
        return ans;
    }

    ~Interpolator() noexcept override = default;

    [[nodiscard]] std::string toString() const override { return "[Interpolator]"; }
};

#endif //GVIEWER_INTERPOLATOR_H
