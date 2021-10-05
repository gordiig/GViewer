//
// Created by 17105727 on 30.09.2021.
//

#ifndef GVIEWER_SCALEFACTOR_H
#define GVIEWER_SCALEFACTOR_H

#include <sstream>
#include "../../Utils/BaseObject.h++"


struct ScaleFactor: public BaseObject {
    double x = 1;
    double y = 1;
    double z = 1;

    explicit ScaleFactor(double x = 1, double y = 1, double z = 1) noexcept : x(x), y(y), z(z) {}

    ScaleFactor(const ScaleFactor &copy) noexcept {
        if (this == &copy)
            return;
        *this = copy;
    }
    ScaleFactor(ScaleFactor &&move) noexcept { *this = move; }

    ScaleFactor& operator = (const ScaleFactor &copy) noexcept {
        x = copy.x;
        y = copy.y;
        z = copy.z;
        return *this;
    }
    ScaleFactor& operator = (ScaleFactor &&move) noexcept {
        x = move.x;
        y = move.y;
        z = move.z;
        return *this;
    }

    ~ScaleFactor() noexcept override = default;

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "sf[" << x << ", " << y << ", " << z << ']';
        return sst.str();
    }
};

#endif //GVIEWER_SCALEFACTOR_H
