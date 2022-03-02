//
// Created by 17105727 on 18.10.2021.
//

#ifndef GVIEWER_INTERPOLATOR_H
#define GVIEWER_INTERPOLATOR_H

#include <utility>

#include "../BaseObject.h++"
#include "../Containers/Pair.h++"
#include "../../Exceptions/Math.h++"


class Interpolator: public BaseObject {
protected:
    using PairDouble = Pair<double, double>;

    PairDouble originalScale;
    PairDouble interpolationScale;

public:
    Interpolator(PairDouble originalScale, PairDouble interpolationScale) noexcept :
            originalScale(std::move(originalScale)), interpolationScale(std::move(interpolationScale)) {

    }

    Interpolator(const Interpolator &copy) noexcept = default;
    Interpolator(Interpolator &&move) noexcept = default;

    Interpolator& operator = (const Interpolator &copy) noexcept = default;
    Interpolator& operator = (Interpolator &&move) noexcept = default;

    [[nodiscard]] double interpolate(const double originalScaleVal) const {
        // If some sort of extrapolation — return corner
        if (originalScale.first < originalScale.second) {
            if (originalScaleVal < originalScale.first)
                return interpolationScale.first;
            else if (originalScaleVal > originalScale.second)
                return interpolationScale.second;
        } else {
            if (originalScaleVal > originalScale.first)
                return interpolationScale.first;
            else if (originalScaleVal < originalScale.second)
                return interpolationScale.second;
        }

        // Calculating interpolation multiplier
        double t;
        if (doubleEq(originalScale.first, originalScale.second))
            t = 0.5;
        else
            t = (originalScaleVal - originalScale.first) / (originalScale.second - originalScale.first);

        // Calculating result value
        double ans = (1.0 - t) * interpolationScale.first + t * interpolationScale.second;
        return ans;
    }

    ~Interpolator() noexcept override = default;

    [[nodiscard]] std::string toString() const override { return "[Interpolator]"; }
};

#endif //GVIEWER_INTERPOLATOR_H
