//
// Created by 17105727 on 30.09.2021.
//

#ifndef GVIEWER_SHADINGCOEFFICIENTS_H
#define GVIEWER_SHADINGCOEFFICIENTS_H

#include <sstream>
#include "../../Utils/BaseObject.h++"

struct ShadingCoefficients: public BaseObject {
    double kd = 0;
    double ka = 0;

    explicit ShadingCoefficients(double kd = 0, double ka = 0) noexcept : kd(kd), ka(ka) {}

    ShadingCoefficients(const ShadingCoefficients &sc) noexcept {
        if (this == &sc)
            return;
        *this = sc;
    }
    ShadingCoefficients(ShadingCoefficients &&sc) noexcept { *this = sc; }

    ShadingCoefficients& operator = (const ShadingCoefficients &sc) noexcept {
        kd = sc.kd;
        ka = sc.ka;
        return *this;
    }
    ShadingCoefficients& operator = (ShadingCoefficients &&sc) noexcept {
        kd = sc.kd;
        ka = sc.ka;
        return *this;
    }

    ~ShadingCoefficients() noexcept override = default;

    bool operator == (const ShadingCoefficients &rhs) const { return kd == rhs.kd && ka == rhs.ka; }
    bool operator != (const ShadingCoefficients &rhs) const { return !(rhs == *this); }

    [[nodiscard]] std::string toString() const override {
        std::stringstream sst;
        sst << "[kd = " << kd << ", ka = " << ka << ']';
        return sst.str();
    }
};

#endif //GVIEWER_SHADINGCOEFFICIENTS_H
