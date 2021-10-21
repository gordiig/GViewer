//
// Created by 17105727 on 18.10.2021.
//

#ifndef GVIEWER_INTERPOLATOR_H
#define GVIEWER_INTERPOLATOR_H

#include "BaseObject.h++"
#include "Containers/Pair.h++"
#include "../Exceptions/Math.h++"


template<
        typename T1,
        typename T2,
        typename = std::enable_if_t<
                std::is_arithmetic_v<T1> && std::is_arithmetic_v<T2>
        >
>
class Interpolator: public BaseObject {
protected:
    Pair<T1, T1> baseline;
    Pair<T2, T2> interpolateCorners;

public:
    Interpolator(const Pair<T1, T1> &baseline, const Pair<T2, T2> &interpolateCorners) noexcept :
        baseline(baseline), interpolateCorners(interpolateCorners) { }

    Interpolator(const Interpolator<T1, T2> &copy) noexcept = default;
    Interpolator(Interpolator<T1, T2> &&move) noexcept = default;

    Interpolator& operator = (const Interpolator<T1, T2> &copy) noexcept = default;
    Interpolator& operator = (Interpolator<T1, T2> &&move) noexcept = default;

    T2 interpolate(const T1 &baselineVal) const {
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
        if (baseline.first == baseline.second)
            t = 0.5;
        else
            t = (baselineVal - baseline.first) / (baseline.second - baseline.first);

        T2 ans = (1 - t) * interpolateCorners.first + t * interpolateCorners.second;
        return ans;
    }

    ~Interpolator() noexcept override = default;

    [[nodiscard]] std::string toString() const override { return "[Interpolator]"; }
};

#endif //GVIEWER_INTERPOLATOR_H
