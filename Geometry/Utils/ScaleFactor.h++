//
// Created by 17105727 on 30.09.2021.
//

#ifndef GVIEWER_SCALEFACTOR_H
#define GVIEWER_SCALEFACTOR_H

#include "../../Utils/BaseObject.h++"


struct ScaleFactor: public BaseObject {
    double x = 1;
    double y = 1;
    double z = 1;

    explicit ScaleFactor(double x = 1, double y = 1, double z = 1) noexcept : x(x), y(y), z(z) {}

    ScaleFactor(const ScaleFactor &copy) noexcept = default;
    ScaleFactor(ScaleFactor &&move) noexcept = default;

    ScaleFactor& operator = (const ScaleFactor &copy) noexcept = default;
    ScaleFactor& operator = (ScaleFactor &&move) noexcept = default;

    ~ScaleFactor() noexcept override = default;

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "sf[" << x << ", " << y << ", " << z << ']';
        return sst.str();
    }
};

#endif //GVIEWER_SCALEFACTOR_H
