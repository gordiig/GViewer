//
// Created by 17105727 on 16.11.2021.
//

#ifndef GVIEWER_ILINEINTERPOLATORLINE_H
#define GVIEWER_ILINEINTERPOLATORLINE_H

#include "../../BaseObject.h++"
#include "../../Containers/Pair.h++"


class ILineInterpolatorLine: public BaseObject {
protected:
    using InterpolationLinePoint = Pair<double, double>;

public:
    [[nodiscard]] virtual InterpolationLinePoint getLineStart() const noexcept = 0;
    [[nodiscard]] virtual InterpolationLinePoint getLineEnd() const noexcept = 0;

    ~ILineInterpolatorLine() noexcept override = default;

    [[nodiscard]] std::string toString() const override {
        return "[ILineInterpolatorLine]";
    }
};


#endif //GVIEWER_ILINEINTERPOLATORLINE_H
